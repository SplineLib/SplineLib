/* Copyright (c) 2018–2021 SplineLib

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef PYTHON_SOURCES_SPLINE_BINDING_HPP_
#define PYTHON_SOURCES_SPLINE_BINDING_HPP_

#include <functional>
#include <type_traits>
#include <utility>

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include "Sources/Splines/spline.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Python/Sources/parameter_space_binding.hpp"

namespace splinelib::python::sources {

template<int parametric_dimensionality, int dimensionality>
class Spline {
 private:
  using ParameterSpace_ = ParameterSpace<parametric_dimensionality>;

 public:
  using Degrees_ = typename ParameterSpace_::Degrees_;
  using KnotVectors_ = typename ParameterSpace_::KnotVectors_;

 private:
  template<typename ...Types>
  using Function_ = std::function<Types...>;
  using Implementation_ = splinelib::sources::splines::Spline<parametric_dimensionality, dimensionality>;
  using Knots_ = std::remove_const_t<std::remove_pointer_t<typename ParameterSpace_::KnotVectors_::value_type>>;
  using NumberOfParametricCoordinates_ = typename ParameterSpace_::NumberOfParametricCoordinates_;
  using ScalarNumberOfParametricCoordinates_ = typename NumberOfParametricCoordinates_::value_type;
  using Coordinate_ = typename Implementation_::Coordinate_;
  using Coordinates_ = typename Implementation_::Coordinates_;
  using Degree_ = typename Degrees_::value_type;
  using Derivative_ = typename Implementation_::Derivative_;
  using ParametricCoordinate_ = typename Implementation_::ParametricCoordinate_;
  using DegreePython_ = typename Degree_::Type_;

  template<typename Type>
  using Array_ = pybind11::array_t<Type>;

 protected:
  using BufferInfo_ = pybind11::buffer_info;
  using Handle_ = pybind11::handle;
  using List_ = pybind11::list;
  using ScalarCoordinate_ = typename Coordinate_::value_type;
  using Tolerance_ = splinelib::sources::splines::Tolerance;

  using Coarsening_ = Function_<Multiplicity(Dimension const &, Knots_ const &, Multiplicity const &,
                                             Tolerance_ const &)>;
  using Differentiation_ = Function_<Coordinate_(ParametricCoordinate_ const &, Derivative_ const &,
                                                 Tolerance_ const &)>;
  using Elevation_ = Function_<void(Dimension const &, Multiplicity const &, Tolerance_ const &)>;
  using Evaluation_ = Function_<Coordinate_(ParametricCoordinate_ const &, Tolerance_ const &)>;
  using Reduction_ = Function_<bool(Dimension const &, Multiplicity const &, Tolerance_ const &)>;
  using Refinement_ = Function_<void(Dimension const &, Knots_, Multiplicity const &, Tolerance_ const &)>;
  using Sampling_ = Function_<Coordinates_(NumberOfParametricCoordinates_ const &, Tolerance_ const &)>;

 public:
  using CoordinatesPython_ = List_;
  using DegreesPython_ = Array_<DegreePython_>;
  using DerivativePython_ = Array_<typename Derivative_::value_type::Type_>;
  using DimensionPython_ = typename Dimension::Type_;
  using KnotPython_ = typename Knots_::value_type::Type_;
  using KnotsPython_ = List_;
  using KnotVectorPython_ = List_;
  using KnotVectorsPython_ = List_;  // Array_<List_> is not supported.
  using MultiplicityPython_ = Multiplicity::Type_;
  using ParametricCoordinatesPython_ = List_;
  using ScalarCoordinatePython_ = typename ScalarCoordinate_::Type_;
  using CoordinatePython_ = Array_<ScalarCoordinatePython_>;
  using NumberOfParametricCoordinatesPython_ = Array_<typename ScalarNumberOfParametricCoordinates_::Type_>;

  KnotVectors_ knot_vectors_;
  Degrees_ const *degrees_;

  virtual ~Spline() = default;

 protected:
  // Attention: moved from within derived spline constructors!
  Coordinates_ coordinates_cpp_;
  SharedPointer<ParameterSpace_> parameter_space_;

  Spline(bool is_rational, Implementation_ * const spline);
  Spline(KnotVectorsPython_ const &knot_vectors, DegreesPython_ const &degrees, CoordinatesPython_ const &coordinates,
         bool is_rational, Implementation_ * const spline);
  Spline(Spline const &other) = delete;
  Spline(Spline &&other) noexcept = default;
  Spline & operator=(Spline const &rhs) = delete;
  Spline & operator=(Spline &&rhs) noexcept = default;

  CoordinatesPython_ Evaluate(Evaluation_ const &Evaluate, ParametricCoordinatesPython_ const &parametric_coordinates)
      const;
  CoordinatesPython_ Derivative(Differentiation_ const &Derivative,
      ParametricCoordinatesPython_ const &parametric_coordinates, DerivativePython_ const &derivative) const;
  void RefineKnots(Refinement_ const &RefineKnots, DimensionPython_ const &dimension, KnotsPython_ const &knots) const;
  MultiplicityPython_ CoarsenKnots(Coarsening_ const &CoarsenKnots, DimensionPython_ const &dimension,
                                   KnotsPython_ const &knots) const;
  void ElevateDegree(Elevation_ const &ElevateDegree, DimensionPython_ const &dimension) const;
  bool ReduceDegree(Reduction_ const &ReduceDegree, DimensionPython_ const &dimension) const;

  CoordinatesPython_ Sample(Sampling_ const &Sample,
                            NumberOfParametricCoordinatesPython_ const &number_of_parametric_coordinates) const;

 private:
  using KnotVector_ = typename ParameterSpace_::KnotVector_;
  using ScalarDerivative_ = typename Derivative_::value_type;
  using ScalarParametricCoordinate_ = typename ParametricCoordinate_::value_type;
  using Vectorizable_ = Function_<Coordinate_(ParametricCoordinate_ const &, Tolerance_ const &)>;

  constexpr inline static Tolerance_ const &kEpsilon_ = splinelib::sources::splines::kEpsilon;
  constexpr inline static Multiplicity const &kMultiplicity_ = splinelib::sources::splines::kMultiplicity;

  CoordinatesPython_ VectorizeEvaluation(Vectorizable_ const &Evaluate,
                                         ParametricCoordinatesPython_ const &parametric_coordinates) const;
  CoordinatePython_ ConvertCoordinate(Coordinate_ const &coordinate_cpp) const;
  Knots_ ConvertKnots(KnotsPython_ const &knots) const;
};

#include "Python/Sources/spline_binding.inc"

}  // namespace splinelib::python::sources

#endif  // PYTHON_SOURCES_SPLINE_BINDING_HPP_
