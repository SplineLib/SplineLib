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

#include <functional>
#include <type_traits>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Python/Sources/b_spline_binding.hpp"
#include "Python/Sources/nurbs_binding.hpp"
#include "Sources/Utilities/std_container_operations.hpp"

template<int parametric_dimensionality, int dimensionality>
using BSpline = splinelib::python::sources::BSpline<parametric_dimensionality, dimensionality>;
template<int parametric_dimensionality, int dimensionality>
using Nurbs = splinelib::python::sources::Nurbs<parametric_dimensionality, dimensionality>;
template<typename Spline>
using SplineBase = typename Spline::Base_;
template<typename Spline>
using ParameterSpace = typename SplineBase<Spline>::ParameterSpace_;
template<typename Spline>
using VectorSpace = typename SplineBase<Spline>::VectorSpace_;
template<typename Spline>
using Coordinate = typename VectorSpace<Spline>::Coordinate_;
template<typename Spline>
using Coordinates = typename VectorSpace<Spline>::Coordinates_;
template<typename Spline>
using Degrees = typename ParameterSpace<Spline>::Degrees_;
template<typename Spline>
using KnotVectors = typename Spline::KnotVectors_;

using BSpline1d1d = BSpline<1, 1>; using Nurbs1d1d = Nurbs<1, 1>;
using BSpline1d2d = BSpline<1, 2>; using Nurbs1d2d = Nurbs<1, 2>;
using BSpline1d3d = BSpline<1, 3>; using Nurbs1d3d = Nurbs<1, 3>;
using BSpline2d1d = BSpline<2, 1>; using Nurbs2d1d = Nurbs<2, 1>;
using BSpline2d2d = BSpline<2, 2>; using Nurbs2d2d = Nurbs<2, 2>;
using BSpline2d3d = BSpline<2, 3>; using Nurbs2d3d = Nurbs<2, 3>;
using BSpline3d1d = BSpline<3, 1>; using Nurbs3d1d = Nurbs<3, 1>;
using BSpline3d3d = BSpline<3, 3>; using Nurbs3d3d = Nurbs<3, 3>;
using BSpline4d1d = BSpline<4, 1>; using Nurbs4d1d = Nurbs<4, 1>;
using BSpline4d3d = BSpline<4, 3>; using Nurbs4d3d = Nurbs<4, 3>;

using Coordinate1d = Coordinate<BSpline1d1d>;
using Coordinate2d = Coordinate<BSpline2d2d>;
using Coordinate3d = Coordinate<BSpline3d3d>;
using Coordinate4dHomogeneous = Nurbs4d3d::Base_::WeightedVectorSpace_::HomogeneousCoordinate_;
using Coordinates1d = Coordinates<BSpline1d1d>;
using Coordinates2d = Coordinates<BSpline2d2d>;
using Coordinates3d = Coordinates<BSpline3d3d>;
using Coordinates4dHomogeneous = Nurbs4d3d::HomogeneousCoordinates_;
using Degrees1d = Degrees<BSpline1d1d>;
using Degrees2d = Degrees<BSpline2d2d>;
using Degrees3d = Degrees<BSpline3d3d>;
using Degrees4d = Degrees<BSpline4d3d>;
using KnotVectors1d = KnotVectors<BSpline1d1d>;
using KnotVectors2d = KnotVectors<BSpline2d2d>;
using KnotVectors3d = KnotVectors<BSpline3d3d>;
using KnotVectors4d = KnotVectors<BSpline4d3d>;
using Knots = std::remove_const_t<std::remove_pointer_t<KnotVectors1d::value_type>>;

PYBIND11_MAKE_OPAQUE(Coordinate1d);
PYBIND11_MAKE_OPAQUE(Coordinate2d);
PYBIND11_MAKE_OPAQUE(Coordinate3d);
PYBIND11_MAKE_OPAQUE(Coordinate4dHomogeneous);
PYBIND11_MAKE_OPAQUE(Coordinates1d);
PYBIND11_MAKE_OPAQUE(Coordinates2d);
PYBIND11_MAKE_OPAQUE(Coordinates3d);
PYBIND11_MAKE_OPAQUE(Coordinates4dHomogeneous);
PYBIND11_MAKE_OPAQUE(Degrees1d);
PYBIND11_MAKE_OPAQUE(Degrees2d);
PYBIND11_MAKE_OPAQUE(Degrees3d);
PYBIND11_MAKE_OPAQUE(Degrees4d);
PYBIND11_MAKE_OPAQUE(Knots);
PYBIND11_MAKE_OPAQUE(KnotVectors1d);
PYBIND11_MAKE_OPAQUE(KnotVectors2d);
PYBIND11_MAKE_OPAQUE(KnotVectors3d);
PYBIND11_MAKE_OPAQUE(KnotVectors4d);

namespace splinelib::python::sources {

namespace {

template<typename ClassCpp>
using Class = pybind11::class_<ClassCpp>;
using Degree = Degrees1d::value_type::Type_;
using IndexPython = Index::Type_;
using Knot = Knots::value_type::Type_;
using ScalarCoordinate = Coordinate1d::value_type::Type_;
using std::function;

template<typename Coordinate>
function<ScalarCoordinate(Coordinate const &, IndexPython const &)> const &get_coordinate =
    [] (Coordinate const &coordinate, IndexPython const &index) { return coordinate[index].Get(); };
template<typename Coordinates>
function<typename Coordinates::value_type(Coordinates const &, IndexPython const &)> const &get_coordinates =
    [] (Coordinates const &coordinates, IndexPython const &index) { return coordinates[index]; };
template<typename Degrees>
function<Degree(Degrees const &, IndexPython const &)> const &get_degree =
    [] (Degrees const &degrees, IndexPython const &index) { return degrees[index].Get(); };
template<typename KnotVectors>
function<Knots(KnotVectors const &, IndexPython const &)> const &get_knots =
    [] (KnotVectors const &knot_vectors, IndexPython const &index) { return *knot_vectors[index]; };

}  // namespace

PYBIND11_MODULE(splinelyp, module) {
  using pybind11::arg, pybind11::init, pybind11::return_value_policy;

  module.doc() = "splinelyp: SplineLib's python bindings";

  Class<Coordinate1d>(module, "Coordinate1d").def("__getitem__", get_coordinate<Coordinate1d>);
  Class<Coordinate2d>(module, "Coordinate2d").def("__getitem__", get_coordinate<Coordinate2d>);
  Class<Coordinate3d>(module, "Coordinate3d").def("__getitem__", get_coordinate<Coordinate3d>);
  Class<Coordinate4dHomogeneous>(module, "Coordinate4dHomogeneous").def("__getitem__",
                                                                        get_coordinate<Coordinate4dHomogeneous>);
  Class<Coordinates1d>(module, "Coordinates1d").def("__getitem__", get_coordinates<Coordinates1d>);
  Class<Coordinates2d>(module, "Coordinates2d").def("__getitem__", get_coordinates<Coordinates2d>);
  Class<Coordinates3d>(module, "Coordinates3d").def("__getitem__", get_coordinates<Coordinates3d>);
  Class<Coordinates4dHomogeneous>(module, "Coordinates4dHomogeneous").def("__getitem__",
                                                                          get_coordinates<Coordinates4dHomogeneous>);

  Class<Degrees1d>(module, "Degrees1d").def("__getitem__", get_degree<Degrees1d>);
  Class<Degrees2d>(module, "Degrees2d").def("__getitem__", get_degree<Degrees2d>);
  Class<Degrees3d>(module, "Degrees3d").def("__getitem__", get_degree<Degrees3d>);
  Class<Degrees4d>(module, "Degrees4d").def("__getitem__", get_degree<Degrees4d>);

  Class<Knots>(module, "Knots").def("__getitem__", [] (Knots const &knots,
                                                       int const &index) { return knots[index].Get(); });
  Class<KnotVectors1d>(module, "KnotVectors1d").def("__getitem__", get_knots<KnotVectors1d>);
  Class<KnotVectors2d>(module, "KnotVectors2d").def("__getitem__", get_knots<KnotVectors2d>);
  Class<KnotVectors3d>(module, "KnotVectors3d").def("__getitem__", get_knots<KnotVectors3d>);
  Class<KnotVectors4d>(module, "KnotVectors4d").def("__getitem__", get_knots<KnotVectors4d>);

  Class<BSpline1d1d>(module, "BSpline1d1d")
      .def(init<BSpline1d1d::KnotVectorsPython_, BSpline1d1d::DegreesPython_, BSpline1d1d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline1d1d::knot_vectors_)
      .def_readonly("degrees", &BSpline1d1d::degrees_)
      .def_readonly("coordinates", &BSpline1d1d::coordinates_)
      .def("evaluate", &BSpline1d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline1d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline1d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline1d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline1d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline1d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline1d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline1d1d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline1d1d const &) { return "<splinelyp.BSpline1d1d>"; });
  Class<BSpline1d2d>(module, "BSpline1d2d")
      .def(init<BSpline1d2d::KnotVectorsPython_, BSpline1d2d::DegreesPython_, BSpline1d2d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline1d2d::knot_vectors_)
      .def_readonly("degrees", &BSpline1d2d::degrees_)
      .def_readonly("coordinates", &BSpline1d2d::coordinates_)
      .def("evaluate", &BSpline1d2d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline1d2d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline1d2d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline1d2d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline1d2d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline1d2d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline1d2d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline1d2d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline1d2d const &) { return "<splinelyp.BSpline1d2d>"; });
  Class<BSpline1d3d>(module, "BSpline1d3d")
      .def(init<BSpline1d3d::KnotVectorsPython_, BSpline1d3d::DegreesPython_, BSpline1d3d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline1d3d::knot_vectors_)
      .def_readonly("degrees", &BSpline1d3d::degrees_)
      .def_readonly("coordinates", &BSpline1d3d::coordinates_)
      .def("evaluate", &BSpline1d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline1d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline1d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline1d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline1d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline1d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline1d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline1d3d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline1d3d const &) { return "<splinelyp.BSpline1d3d>"; });
  Class<BSpline2d1d>(module, "BSpline2d1d")
      .def(init<BSpline2d1d::KnotVectorsPython_, BSpline2d1d::DegreesPython_, BSpline2d1d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline2d1d::knot_vectors_)
      .def_readonly("degrees", &BSpline2d1d::degrees_)
      .def_readonly("coordinates", &BSpline2d1d::coordinates_)
      .def("evaluate", &BSpline2d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline2d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline2d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline2d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline2d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline2d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline2d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline2d1d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline2d1d const &) { return "<splinelyp.BSpline2d1d>"; });
  Class<BSpline2d2d>(module, "BSpline2d2d")
      .def(init<BSpline2d2d::KnotVectorsPython_, BSpline2d2d::DegreesPython_, BSpline2d2d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline2d2d::knot_vectors_)
      .def_readonly("degrees", &BSpline2d2d::degrees_)
      .def_readonly("coordinates", &BSpline2d2d::coordinates_)
      .def("evaluate", &BSpline2d2d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline2d2d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline2d2d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline2d2d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline2d2d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline2d2d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline2d2d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline2d2d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline2d2d const &) { return "<splinelyp.BSpline2d2d>"; });
  Class<BSpline2d3d>(module, "BSpline2d3d")
      .def(init<BSpline2d3d::KnotVectorsPython_, BSpline2d3d::DegreesPython_, BSpline2d3d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline2d3d::knot_vectors_)
      .def_readonly("degrees", &BSpline2d3d::degrees_)
      .def_readonly("coordinates", &BSpline2d3d::coordinates_)
      .def("evaluate", &BSpline2d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline2d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline2d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline2d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline2d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline2d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline2d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline2d3d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline2d3d const &) { return "<splinelyp.BSpline2d3d>"; });
  Class<BSpline3d1d>(module, "BSpline3d1d")
      .def(init<BSpline3d1d::KnotVectorsPython_, BSpline3d1d::DegreesPython_, BSpline3d1d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline3d1d::knot_vectors_)
      .def_readonly("degrees", &BSpline3d1d::degrees_)
      .def_readonly("coordinates", &BSpline3d1d::coordinates_)
      .def("evaluate", &BSpline3d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline3d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline3d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline3d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline3d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline3d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline3d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline3d1d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline3d1d const &) { return "<splinelyp.BSpline3d1d>"; });
  Class<BSpline3d3d>(module, "BSpline3d3d")
      .def(init<BSpline3d3d::KnotVectorsPython_, BSpline3d3d::DegreesPython_, BSpline3d3d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline3d3d::knot_vectors_)
      .def_readonly("degrees", &BSpline3d3d::degrees_)
      .def_readonly("coordinates", &BSpline3d3d::coordinates_)
      .def("evaluate", &BSpline3d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline3d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline3d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline3d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline3d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline3d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline3d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline3d3d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline3d3d const &) { return "<splinelyp.BSpline3d3d>"; });
  Class<BSpline4d1d>(module, "BSpline4d1d")
      .def(init<BSpline4d1d::KnotVectorsPython_, BSpline4d1d::DegreesPython_, BSpline4d1d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline4d1d::knot_vectors_)
      .def_readonly("degrees", &BSpline4d1d::degrees_)
      .def_readonly("coordinates", &BSpline4d1d::coordinates_)
      .def("evaluate", &BSpline4d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline4d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline4d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline4d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline4d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline4d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline4d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline4d1d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline4d1d const &) { return "<splinelyp.BSpline4d1d>"; });
  Class<BSpline4d3d>(module, "BSpline4d3d")
      .def(init<BSpline4d3d::KnotVectorsPython_, BSpline4d3d::DegreesPython_, BSpline4d3d::CoordinatesPython_>())
      .def_readonly("knot_vectors", &BSpline4d3d::knot_vectors_)
      .def_readonly("degrees", &BSpline4d3d::degrees_)
      .def_readonly("coordinates", &BSpline4d3d::coordinates_)
      .def("evaluate", &BSpline4d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &BSpline4d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &BSpline4d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &BSpline4d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &BSpline4d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &BSpline4d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &BSpline4d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &BSpline4d3d::Write, return_value_policy::move)
      .def("__repr__", [] (BSpline4d3d const &) { return "<splinelyp.BSpline4d3d>"; });

  Class<Nurbs1d1d>(module, "Nurbs1d1d")
      .def(init<Nurbs1d1d::KnotVectorsPython_, Nurbs1d1d::DegreesPython_, Nurbs1d1d::CoordinatesPython_,
                Nurbs1d1d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs1d1d::knot_vectors_)
      .def_readonly("degrees", &Nurbs1d1d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs1d1d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs1d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs1d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs1d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs1d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs1d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs1d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs1d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs1d1d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs1d1d const &) { return "<splinelyp.Nurbs1d1d>"; });
  Class<Nurbs1d2d>(module, "Nurbs1d2d")
      .def(init<Nurbs1d2d::KnotVectorsPython_, Nurbs1d2d::DegreesPython_, Nurbs1d2d::CoordinatesPython_,
                Nurbs1d2d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs1d2d::knot_vectors_)
      .def_readonly("degrees", &Nurbs1d2d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs1d2d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs1d2d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs1d2d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs1d2d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs1d2d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs1d2d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs1d2d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs1d2d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs1d2d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs1d2d const &) { return "<splinelyp.Nurbs1d2d>"; });
  Class<Nurbs1d3d>(module, "Nurbs1d3d")
      .def(init<Nurbs1d3d::KnotVectorsPython_, Nurbs1d3d::DegreesPython_, Nurbs1d3d::CoordinatesPython_,
                Nurbs1d3d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs1d3d::knot_vectors_)
      .def_readonly("degrees", &Nurbs1d3d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs1d3d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs1d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs1d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs1d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs1d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs1d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs1d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs1d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs1d3d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs1d3d const &) { return "<splinelyp.Nurbs1d3d>"; });
  Class<Nurbs2d1d>(module, "Nurbs2d1d")
      .def(init<Nurbs2d1d::KnotVectorsPython_, Nurbs2d1d::DegreesPython_, Nurbs2d1d::CoordinatesPython_,
                Nurbs2d1d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs2d1d::knot_vectors_)
      .def_readonly("degrees", &Nurbs2d1d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs2d1d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs2d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs2d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs2d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs2d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs2d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs2d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs2d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs2d1d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs2d1d const &) { return "<splinelyp.Nurbs2d1d>"; });
  Class<Nurbs2d2d>(module, "Nurbs2d2d")
      .def(init<Nurbs2d2d::KnotVectorsPython_, Nurbs2d2d::DegreesPython_, Nurbs2d2d::CoordinatesPython_,
                Nurbs2d2d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs2d2d::knot_vectors_)
      .def_readonly("degrees", &Nurbs2d2d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs2d2d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs2d2d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs2d2d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs2d2d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs2d2d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs2d2d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs2d2d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs2d2d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs2d2d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs2d2d const &) { return "<splinelyp.Nurbs2d2d>"; });
  Class<Nurbs2d3d>(module, "Nurbs2d3d")
      .def(init<Nurbs2d3d::KnotVectorsPython_, Nurbs2d3d::DegreesPython_, Nurbs2d3d::CoordinatesPython_,
                Nurbs2d3d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs2d3d::knot_vectors_)
      .def_readonly("degrees", &Nurbs2d3d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs2d3d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs2d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs2d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs2d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs2d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs2d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs2d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs2d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs2d3d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs2d3d const &) { return "<splinelyp.Nurbs2d3d>"; });
  Class<Nurbs3d1d>(module, "Nurbs3d1d")
      .def(init<Nurbs3d1d::KnotVectorsPython_, Nurbs3d1d::DegreesPython_, Nurbs3d1d::CoordinatesPython_,
                Nurbs3d1d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs3d1d::knot_vectors_)
      .def_readonly("degrees", &Nurbs3d1d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs3d1d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs3d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs3d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs3d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs3d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs3d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs3d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs3d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs3d1d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs3d1d const &) { return "<splinelyp.Nurbs3d1d>"; });
  Class<Nurbs3d3d>(module, "Nurbs3d3d")
      .def(init<Nurbs3d3d::KnotVectorsPython_, Nurbs3d3d::DegreesPython_, Nurbs3d3d::CoordinatesPython_,
                Nurbs3d3d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs3d3d::knot_vectors_)
      .def_readonly("degrees", &Nurbs3d3d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs3d3d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs3d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs3d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs3d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs3d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs3d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs3d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs3d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs3d3d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs3d3d const &) { return "<splinelyp.Nurbs3d3d>"; });
  Class<Nurbs4d1d>(module, "Nurbs4d1d")
      .def(init<Nurbs4d1d::KnotVectorsPython_, Nurbs4d1d::DegreesPython_, Nurbs4d1d::CoordinatesPython_,
                Nurbs4d1d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs4d1d::knot_vectors_)
      .def_readonly("degrees", &Nurbs4d1d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs4d1d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs4d1d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs4d1d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs4d1d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs4d1d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs4d1d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs4d1d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs4d1d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs4d1d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs4d1d const &) { return "<splinelyp.Nurbs4d1d>"; });
  Class<Nurbs4d3d>(module, "Nurbs4d3d")
      .def(init<Nurbs4d3d::KnotVectorsPython_, Nurbs4d3d::DegreesPython_, Nurbs4d3d::CoordinatesPython_,
                Nurbs4d3d::WeightsPython_>())
      .def_readonly("knot_vectors", &Nurbs4d3d::knot_vectors_)
      .def_readonly("degrees", &Nurbs4d3d::degrees_)
      .def_readonly("homogeneous_coordinates", &Nurbs4d3d::homogeneous_coordinates_)
      .def("evaluate", &Nurbs4d3d::Evaluate, arg("parametric_coordinates"), return_value_policy::move)
      .def("derivative", &Nurbs4d3d::Derivative, arg("parametric_coordinates"), arg("derivative"),
           return_value_policy::move)
      .def("insert_knots", &Nurbs4d3d::RefineKnots, arg("dimension"), arg("knots"))
      .def("remove_knots", &Nurbs4d3d::CoarsenKnots, arg("dimension"), arg("knots"), arg("tolerance"),
           return_value_policy::move)
      .def("elevate_degree", &Nurbs4d3d::ElevateDegree, arg("dimension"))
      .def("reduce_degree", &Nurbs4d3d::ReduceDegree, arg("dimension"), arg("tolerance"), return_value_policy::move)
      .def("sample", &Nurbs4d3d::Sample, arg("number_of_parametric_coordinates"), return_value_policy::move)
      .def("write", &Nurbs4d3d::Write, return_value_policy::move)
      .def("__repr__", [] (Nurbs4d3d const &) { return "<splinelyp.Nurbs4d3d>"; });
}

}  // namespace splinelib::python::sources
