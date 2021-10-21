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
Spline<parametric_dimensionality, dimensionality>::Spline(bool is_rational, Implementation_ * const spline) {
  spline->parametric_dimensionality_ = parametric_dimensionality;
  spline->dimensionality_ = dimensionality;
  spline->is_rational_ = std::move(is_rational);
}

template<int parametric_dimensionality, int dimensionality>
Spline<parametric_dimensionality, dimensionality>::Spline(KnotVectorsPython_ const &knot_vectors,
    DegreesPython_ const &degrees, CoordinatesPython_ const &coordinates, bool is_rational,
    Implementation_ * const spline) : Spline(std::move(is_rational), std::move(spline)) {
  using std::make_shared, std::move, std::to_string;

#ifndef NDEBUG
  try {
#endif
    typename ParameterSpace_::KnotVectorsBase_ knot_vectors_cpp{};
    DimensionPython_ dimension{};
#ifndef NDEBUG
    int const &knot_vectors_size = knot_vectors.size();
    if (knot_vectors_size != parametric_dimensionality)
        throw DomainError{"Wrong number of knot vectors (" + to_string(dimension + 1) + " instead of " +
                          to_string(parametric_dimensionality) + ") were provided."};
#endif
    for (Handle_ const &knot_vector : knot_vectors) {
      Knots_ knots;
      for (Handle_ const &knot : knot_vector) knots.emplace_back(knot.cast<KnotPython_>());
      SharedPointer<KnotVector_> knot_vector_cpp{make_shared<KnotVector_>(knots)};
      knot_vectors_cpp[dimension] = knot_vector_cpp;
      knot_vectors_[dimension++] = &(knot_vector_cpp->knots_);
    }
    BufferInfo_ const &degrees_python = degrees.request();
#ifndef NDEBUG
    if (degrees_python.ndim == 1) {
      int const &number_of_degrees = degrees_python.shape[0];
      if (number_of_degrees != parametric_dimensionality)
          throw DomainError{"Provided " + to_string(number_of_degrees) + " instead of " +
                            to_string(parametric_dimensionality) + " degrees."};
    } else {
      throw DomainError{"Degrees must be provided as one-dimensional array."};
    }
#endif
    Degrees_ degrees_cpp;
    for (DimensionPython_ dimension{}; dimension < parametric_dimensionality; ++dimension)
        degrees_cpp[dimension] = Degree_{static_cast<DegreePython_ *>(degrees_python.ptr)[dimension]};
    parameter_space_ = make_shared<ParameterSpace_>(move(knot_vectors_cpp), move(degrees_cpp));
    degrees_ = &parameter_space_->degrees_;

    for (Handle_ const coordinate : coordinates) {
      BufferInfo_ const &coordinate_python = coordinate.template cast<CoordinatePython_>().request();
#ifndef NDEBUG
      if (coordinate_python.ndim == 1) {
        int const &dimensionality_python = coordinate_python.shape[0];
        if (dimensionality_python != dimensionality)
            throw DomainError{"Provided coordinates are " + to_string(dimensionality_python) + "- instead of " +
                              to_string(dimensionality) + "-dimensional."};
      } else {
        throw DomainError{"Each coordinate must be provided as one-dimensional array."};
      }
#endif
      Coordinate_ coordinate_cpp{};
      for (DimensionPython_ dimension{}; dimension < dimensionality; ++dimension)
          coordinate_cpp[dimension] =
              ScalarCoordinate_{static_cast<typename ScalarCoordinate_::Type_ *>(coordinate_python.ptr)[dimension]};
      coordinates_cpp_.push_back(coordinate_cpp);
    }
#ifndef NDEBUG
  } catch (DomainError const &exception) { Throw(exception, "splinelib::python::sources::BSpline::BSpline"); }
#endif
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::CoordinatesPython_
Spline<parametric_dimensionality, dimensionality>::Evaluate(Evaluation_ const &Evaluate,
    ParametricCoordinatesPython_ const &parametric_coordinates) const {
  return VectorizeEvaluation(Evaluate, parametric_coordinates);
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::CoordinatesPython_
Spline<parametric_dimensionality, dimensionality>::Derivative(Differentiation_ const &Derivative,
    ParametricCoordinatesPython_ const &parametric_coordinates, DerivativePython_ const &derivative) const {
  using namespace std::placeholders;

  Derivative_ derivative_cpp;
  for (DimensionPython_ dimension{}; dimension < parametric_dimensionality; ++dimension)
      derivative_cpp[dimension] =
          ScalarDerivative_{static_cast<typename ScalarDerivative_::Type_ *>(derivative.request().ptr)[dimension]};
  return VectorizeEvaluation(std::bind(Derivative, _1, derivative_cpp, _2), parametric_coordinates);
}

template<int parametric_dimensionality, int dimensionality>
void Spline<parametric_dimensionality, dimensionality>::RefineKnots(Refinement_ const &RefineKnots,
    DimensionPython_ const &dimension, KnotsPython_ const &knots) const {
  RefineKnots(Dimension{dimension}, ConvertKnots(knots), kMultiplicity_, kEpsilon_);
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::MultiplicityPython_
Spline<parametric_dimensionality, dimensionality>::CoarsenKnots(Coarsening_ const &CoarsenKnots,
    DimensionPython_ const &dimension, KnotsPython_ const &knots) const {
  return CoarsenKnots(Dimension{dimension}, ConvertKnots(knots), kMultiplicity_, kEpsilon_).Get();
}

template<int parametric_dimensionality, int dimensionality>
void Spline<parametric_dimensionality, dimensionality>::ElevateDegree(Elevation_ const &ElevateDegree,
                                                                      DimensionPython_ const &dimension) const {
  ElevateDegree(Dimension{dimension}, kMultiplicity_, kEpsilon_);
}

template<int parametric_dimensionality, int dimensionality>
bool Spline<parametric_dimensionality, dimensionality>::ReduceDegree(Reduction_ const &ReduceDegree,
                                                                     DimensionPython_ const &dimension) const {
  return ReduceDegree(Dimension{dimension}, kMultiplicity_, kEpsilon_);
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::CoordinatesPython_
Spline<parametric_dimensionality, dimensionality>::Sample(Sampling_ const &Sample,
    NumberOfParametricCoordinatesPython_ const &number_of_parametric_coordinates) const {
  using std::to_string;

  BufferInfo_ const &number_of_parametric_coordinates_python = number_of_parametric_coordinates.request();
#ifndef NDEBUG
  if (number_of_parametric_coordinates_python.ndim == 1) {
    int const &number_of_parametric_coordinates_python_size = number_of_parametric_coordinates_python.shape[0];
    if (number_of_parametric_coordinates_python_size != parametric_dimensionality)
        throw DomainError{"Provided " + to_string(number_of_parametric_coordinates_python_size) + " instead of " +
                          to_string(parametric_dimensionality) + " number of parametric coordinates."};
  } else {
    throw DomainError{"Number of parametric coordinates must be provided as one-dimensional array."};
  }
#endif
  NumberOfParametricCoordinates_ number_of_parametric_coordinates_cpp;
  for (DimensionPython_ dimension{}; dimension < parametric_dimensionality; ++dimension)
      number_of_parametric_coordinates_cpp[dimension] = ScalarNumberOfParametricCoordinates_{
          static_cast<ScalarNumberOfParametricCoordinates_ *>(number_of_parametric_coordinates_python.ptr)[dimension]};
  Coordinates_ const &coordinates_cpp = Sample(number_of_parametric_coordinates_cpp, kEpsilon_);
  CoordinatesPython_ coordinates;
  for (Coordinate_ const &coordinate_cpp : coordinates_cpp) coordinates.append(ConvertCoordinate(coordinate_cpp));
  return coordinates;
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::CoordinatesPython_
Spline<parametric_dimensionality, dimensionality>::VectorizeEvaluation(Vectorizable_ const &Evaluate,
    ParametricCoordinatesPython_ const &parametric_coordinates) const {
  using std::to_string;

  CoordinatesPython_ coordinates;
  for (Handle_ const &parametric_coordinate : parametric_coordinates) {
    BufferInfo_ const &parametric_coordinate_python =
        parametric_coordinate.cast<Array_<typename ScalarParametricCoordinate_::Type_>>().request();
#ifndef NDEBUG
  if (parametric_coordinate_python.ndim == 1) {
    int const &parametric_coordinate_python_size = parametric_coordinate_python.shape[0];
    if (parametric_coordinate_python_size != parametric_dimensionality)
        throw DomainError{"Provided " + to_string(parametric_coordinate_python_size) + " instead of " +
                          to_string(parametric_dimensionality) + " parametric coordinates."};
  } else {
    throw DomainError{"Parametric coordinate must be provided as one-dimensional array."};
  }
#endif
    ParametricCoordinate_ parametric_coordinate_cpp;
    for (DimensionPython_ dimension{}; dimension < parametric_dimensionality; ++dimension)
        parametric_coordinate_cpp[dimension] =
            static_cast<ScalarParametricCoordinate_ *>(parametric_coordinate_python.ptr)[dimension];
    coordinates.append(ConvertCoordinate(Evaluate(parametric_coordinate_cpp, kEpsilon_)));
  }
  return coordinates;
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::CoordinatePython_
Spline<parametric_dimensionality, dimensionality>::ConvertCoordinate(Coordinate_ const &coordinate_cpp) const {
  CoordinatePython_ coordinate(dimensionality);
  for (DimensionPython_ dimension{}; dimension < dimensionality; ++dimension)
      static_cast<ScalarCoordinatePython_ *>(coordinate.request().ptr)[dimension] = coordinate_cpp[dimension].Get();
  return coordinate;
}

template<int parametric_dimensionality, int dimensionality>
typename Spline<parametric_dimensionality, dimensionality>::Knots_
Spline<parametric_dimensionality, dimensionality>::ConvertKnots(KnotsPython_ const &knots) const {
  Knots_ knots_cpp;
  knots_cpp.reserve(len(knots));
  for (Handle_ const &knot : knots) knots_cpp.emplace_back(knot.cast<KnotPython_>());
  return knots_cpp;
}
