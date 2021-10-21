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

template<int parametric_dimensionality, int dimensionality>
BSpline<parametric_dimensionality, dimensionality>::BSpline() : Spline_(false, this) {}

template<int parametric_dimensionality, int dimensionality>
BSpline<parametric_dimensionality, dimensionality>::BSpline(KnotVectorsPython_ const &knot_vectors,
    DegreesPython_ const &degrees, CoordinatesPython_ const &coordinates) :
    Spline_(std::move(knot_vectors), std::move(degrees), std::move(coordinates), false, this) {
  using std::make_shared, std::move, std::to_string;

#ifndef NDEBUG
  try {
#endif
    Base_::parameter_space_ = move(Spline_::parameter_space_);
    SharedPointer<VectorSpace_> vector_space{make_shared<VectorSpace_>(move(Spline_::coordinates_cpp_))};
    Base_::vector_space_ = vector_space;
    coordinates_ = &vector_space->coordinates_;
#ifndef NDEBUG
  } catch (DomainError const &exception) { Throw(exception, "splinelib::python::sources::BSpline::BSpline"); }
#endif
}

template<int parametric_dimensionality, int dimensionality>
typename BSpline<parametric_dimensionality, dimensionality>::CoordinatesPython_
BSpline<parametric_dimensionality, dimensionality>::Evaluate(ParametricCoordinatesPython_ const &parametric_coordinates)
    const {
  using namespace std::placeholders;

  return Spline_::Evaluate(std::bind(std::mem_fn<Coordinate_ (ParametricCoordinate_ const &, Tolerance_ const &) const>(
                               &Base_::operator()), this, _1, _2), parametric_coordinates);
}

template<int parametric_dimensionality, int dimensionality>
typename BSpline<parametric_dimensionality, dimensionality>::CoordinatesPython_
BSpline<parametric_dimensionality, dimensionality>::Derivative(
    ParametricCoordinatesPython_ const &parametric_coordinates, DerivativePython_ const &derivative) const {
  using namespace std::placeholders;

  return Spline_::Derivative(std::bind(std::mem_fn<Coordinate_(ParametricCoordinate_ const &, Derivative_ const &,
             Tolerance_ const &) const>(&Base_::operator()), this, _1, _2, _3), parametric_coordinates, derivative);
}

template<int parametric_dimensionality, int dimensionality>
void BSpline<parametric_dimensionality, dimensionality>::RefineKnots(DimensionPython_ const &dimension,
                                                                     KnotsPython_ const &knots) const {
  using namespace std::placeholders;

  Spline_::RefineKnots(std::bind(std::mem_fn(&Base_::RefineKnots), this, _1, _2, _3, _4), dimension, knots);
}

template<int parametric_dimensionality, int dimensionality>
typename BSpline<parametric_dimensionality, dimensionality>::MultiplicityPython_
BSpline<parametric_dimensionality, dimensionality>::CoarsenKnots(DimensionPython_ const &dimension,
    KnotsPython_ const &knots, Tolerance_ const &tolerance) const {
  using namespace std::placeholders;

  return Spline_::CoarsenKnots(std::bind(std::mem_fn(&Base_::CoarsenKnots), this, _1, _2, tolerance, _3, _4), dimension,
                               knots);
}

template<int parametric_dimensionality, int dimensionality>
void BSpline<parametric_dimensionality, dimensionality>::ElevateDegree(DimensionPython_ const &dimension) const {
  using namespace std::placeholders;

  Spline_::ElevateDegree(std::bind(std::mem_fn(&Base_::ElevateDegree), this, _1, _2, _3), dimension);
}

template<int parametric_dimensionality, int dimensionality>
bool BSpline<parametric_dimensionality, dimensionality>::ReduceDegree(DimensionPython_ const &dimension,
                                                                      Tolerance_ const &tolerance) const {
  using namespace std::placeholders;

  return Spline_::ReduceDegree(std::bind(std::mem_fn(&Base_::ReduceDegree), this, _1, tolerance, _2, _3), dimension);
}

template<int parametric_dimensionality, int dimensionality>
typename BSpline<parametric_dimensionality, dimensionality>::CoordinatesPython_
BSpline<parametric_dimensionality, dimensionality>::Sample(
    NumberOfParametricCoordinatesPython_ const &number_of_parametric_coordinates) const {
  using namespace std::placeholders;

  return Spline_::Sample(std::bind(std::mem_fn(&Base_::Base_::Sample), this, _1, _2), number_of_parametric_coordinates);
}

template<int parametric_dimensionality, int dimensionality>
typename BSpline<parametric_dimensionality, dimensionality>::OutputInformation_
BSpline<parametric_dimensionality, dimensionality>::Write() const {
  return Base_::Write();
}
