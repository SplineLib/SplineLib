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

#ifndef PYTHON_SOURCES_B_SPLINE_BINDING_HPP_
#define PYTHON_SOURCES_B_SPLINE_BINDING_HPP_

#include <functional>
#include <utility>

#include "Sources/Splines/b_spline.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Python/Sources/spline_binding.hpp"
#include "Python/Sources/vector_space_binding.hpp"

namespace splinelib::python::sources {

template<int parametric_dimensionality, int dimensionality>
class BSpline : public Spline<parametric_dimensionality, dimensionality>,
                public splinelib::sources::splines::BSpline<parametric_dimensionality, dimensionality> {
 private:
  using VectorSpace_ = VectorSpace<dimensionality>;

 public:
  using Base_ = splinelib::sources::splines::BSpline<parametric_dimensionality, dimensionality>;
  using Coordinates_ = typename VectorSpace_::Coordinates_;
  using Spline_ = Spline<parametric_dimensionality, dimensionality>;

 private:
  using typename Spline_::BufferInfo_, typename Base_::Coordinate_, typename Base_::Derivative_,
        typename Spline_::Handle_, typename Base_::ParametricCoordinate_, typename Spline_::ScalarCoordinate_;

 public:
  using typename Spline_::CoordinatePython_, typename Spline_::CoordinatesPython_, typename Spline_::DegreesPython_,
      typename Spline_::DerivativePython_, typename Spline_::DimensionPython_, typename Spline_::KnotsPython_,
      typename Spline_::KnotVectorPython_, typename Spline_::KnotVectorsPython_, typename Spline_::MultiplicityPython_,
      typename Spline_::NumberOfParametricCoordinatesPython_, typename Base_::OutputInformation_,
      typename Spline_::ParametricCoordinatesPython_, typename Spline_::Tolerance_;

  Coordinates_ const *coordinates_;

  BSpline();
  BSpline(KnotVectorsPython_ const &knot_vectors, DegreesPython_ const &degrees, CoordinatesPython_ const &coordinates);
  BSpline(BSpline const &other) = delete;
  BSpline(BSpline &&other) noexcept = default;
  BSpline & operator=(BSpline const &rhs) = delete;
  BSpline & operator=(BSpline &&rhs) noexcept = default;
  ~BSpline() final = default;

  CoordinatesPython_ Evaluate(ParametricCoordinatesPython_ const &parametric_coordinates) const;
  CoordinatesPython_ Derivative(ParametricCoordinatesPython_ const &parametric_coordinates,
                                DerivativePython_ const &derivative) const;
  void RefineKnots(DimensionPython_ const &dimension, KnotsPython_ const &knots) const;
  MultiplicityPython_ CoarsenKnots(DimensionPython_ const &dimension, KnotsPython_ const &knots,
                                   Tolerance_ const &tolerance) const;
  void ElevateDegree(DimensionPython_ const &dimension) const;
  bool ReduceDegree(DimensionPython_ const &dimension, Tolerance_ const &tolerance) const;

  CoordinatesPython_ Sample(NumberOfParametricCoordinatesPython_ const &number_of_parametric_coordinates) const;
  OutputInformation_ Write() const;
};

#include "Python/Sources/b_spline_binding.inc"

}  // namespace splinelib::python::sources

#endif  // PYTHON_SOURCES_B_SPLINE_BINDING_HPP_
