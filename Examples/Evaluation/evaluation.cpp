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

#include <iostream>
#include <memory>

#include <SplineLib/Sources/Splines/b_spline.hpp>

using splinelib::SharedPointer, std::cerr, std::cout, std::endl, std::make_shared;

int main() {
  // Construct a B-spline curve that embeds into a plane.
  using BSpline = splinelib::sources::splines::BSpline<1, 2>;
  using ParameterSpace = BSpline::ParameterSpace_;
  using VectorSpace = BSpline::VectorSpace_;
  using Coordinates = VectorSpace::Coordinates_;
  using Degrees = ParameterSpace::Degrees_;
  using KnotVectors = ParameterSpace::KnotVectors_;
  using Coordinate = Coordinates::value_type;
  using Degree = Degrees::value_type;
  using KnotVector = KnotVectors::value_type::element_type;
  using Knots = KnotVector::Knots_;
  using ScalarCoordinate = Coordinate::value_type;
  using Knot = Knots::value_type;

  constexpr Knot const kKnot0_0{0.0}, kKnot1_0{1.0};
  Knots const knots{kKnot0_0, kKnot0_0, Knot{0.5}, kKnot1_0, kKnot1_0};
  constexpr ScalarCoordinate const kCoordinate0_0{0.0}, kCoordinate1_0{1.0};
  constexpr Coordinate const kCoordinate0{kCoordinate0_0, kCoordinate0_0},
      kCoordinate1{ScalarCoordinate{0.25}, ScalarCoordinate{0.75}}, kCoordinate2{kCoordinate1_0, kCoordinate1_0};
  constexpr Degree const kDegree{1};
  SharedPointer<KnotVector> const knot_vector{make_shared<KnotVector>(knots)};
  Coordinates const coordinates{kCoordinate0, kCoordinate1, kCoordinate2};
  constexpr Degrees const kDegrees{kDegree};
  KnotVectors const knot_vectors{knot_vector};
  SharedPointer<ParameterSpace> const parameter_space{make_shared<ParameterSpace>(knot_vectors, kDegrees)};
  SharedPointer<VectorSpace> const vector_space{make_shared<VectorSpace>(coordinates)};
  BSpline const b_spline{parameter_space, vector_space};

  // Evaluate the planar B-spline curve.
  using ParametricCoordinate = BSpline::ParametricCoordinate_;
  using ScalarParametricCoordinate = ParametricCoordinate::value_type;

  constexpr ScalarParametricCoordinate const kParametricCoordinate0_25{0.25};
  constexpr ParametricCoordinate const kParametricCoordinate{kParametricCoordinate0_25};
  Coordinate const &evaluated = b_spline(kParametricCoordinate);

  // Check the evaluation result.
  constexpr Coordinate const kReference{ScalarCoordinate{0.125}, ScalarCoordinate{0.375}};
  if (evaluated == kReference) {
    cout << "\"Hello World!\" from a SplineLib consumer." << endl;
  } else {
    cerr << "Oops, something went wrong!" << endl;
#ifdef SPLINELIB_GOOGLETEST
    cerr << "You might want to run SplineLib's tests!" << endl;
#endif
  }

  return 0;
}
