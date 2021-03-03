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

#ifndef TESTS_SPLINES_B_SPLINE_MOCK_HPP_
#define TESTS_SPLINES_B_SPLINE_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/Splines/b_spline.hpp"
#include "Tests/VectorSpaces/vector_space_mock.hpp"

namespace splinelib::tests::splines {

using sources::splines::BSpline, sources::splines::Tolerance;

constexpr static Tolerance const &kEpsilon = sources::splines::kEpsilon;

class A2d3dBSplineMock : public BSpline<2, 3> {
 public:
  MOCK_METHOD(Coordinate_, Evaluate, (ParametricCoordinate_ const &, Tolerance const &), (const));
  Coordinate_ operator()(ParametricCoordinate_ const &parametric_coordinate, Tolerance const &tolerance = kEpsilon)
      const final;
  MOCK_METHOD(Coordinate_, EvaluateDerivative, (ParametricCoordinate_ const &, Derivative_ const &, Tolerance const &),
              (const));
  Coordinate_ operator()(ParametricCoordinate_ const &parametric_coordinate, Derivative_ const &derivative,
                         Tolerance const &tolerance = kEpsilon) const final;
  MOCK_METHOD(Coordinates_, SampleMock, (NumberOfParametricCoordinates_ const &, Tolerance const &), (const));
  Coordinates_ Sample(NumberOfParametricCoordinates_ const &number_of_parametric_coordinates,
                      Tolerance const &tolerance = kEpsilon) const;

  void NurbsBookExe4_4();  // See NURBS book Exe. 4.4.
  void SquareUnitSecondOrderMaximallySmooth();  // {0; 0; 0; 0.5; 1; 1; 1} & {0; 0; 0; 1; 1; 1} —> {[0; 1]^2; 0}
};

class A2d4dBSplineMock : public BSpline<2, 4> {
  constexpr static Multiplicity const &kMultiplicity_ = sources::splines::kMultiplicity;

 public:
  MOCK_METHOD(Coordinate_, Evaluate, (ParametricCoordinate_ const &, Tolerance const &), (const));
  Coordinate_ operator()(ParametricCoordinate_ const &parametric_coordinate, Tolerance const &tolerance = kEpsilon)
      const final;
  MOCK_METHOD(Coordinate_, EvaluateDerivative, (ParametricCoordinate_ const &, Derivative_ const &, Tolerance const &),
              (const));
  Coordinate_ operator()(ParametricCoordinate_ const &parametric_coordinate, Derivative_ const &derivative,
                         Tolerance const &tolerance = kEpsilon) const final;

  MOCK_METHOD(void, InsertKnotMock, (Dimension const &, Knot_, Multiplicity const &, Tolerance const &), (const));
  void InsertKnot(Dimension const &dimension, Knot_ knot, Multiplicity const &multiplicity = kMultiplicity_,
                  Tolerance const &tolerance = kEpsilon) const final;
  MOCK_METHOD(Multiplicity, RemoveKnotMock, (Dimension const &, Knot_ const &, Tolerance const &, Multiplicity const &,
                                             Tolerance const &), (const));
  Multiplicity RemoveKnot(Dimension const &dimension, Knot_ const &knot, Tolerance const &tolerance_removal,
      Multiplicity const &multiplicity = kMultiplicity_, Tolerance const &tolerance = kEpsilon) const final;
  MOCK_METHOD(void, ElevateDegreeMock, (Dimension const &, Multiplicity const &, Tolerance const &), (const));
  void ElevateDegree(Dimension const &dimension, Multiplicity const &multiplicity = kMultiplicity_,
                     Tolerance const &tolerance = kEpsilon) const final;
  MOCK_METHOD(bool, ReduceDegreeMock, (Dimension const &, Tolerance const &, Multiplicity const &,
                                       Tolerance const &), (const));
  bool ReduceDegree(Dimension const &dimension, Tolerance const &tolerance_reduction,
      Multiplicity const &multiplicity = kMultiplicity_, Tolerance const &tolerance = kEpsilon) const final;

  void NurbsBookExe4_4();  // See NURBS book Exe. 4.4.
  void NurbsBookExe4_4KnotVector();
  void NurbsBookExe4_4BSpline();
  void SquareUnitFirstOrderBezier();  // {0; 0; 1; 1}^2 —> {[0; 2]^2; 0; 2}
};

}  // namespace splinelib::tests::splines

#endif  // TESTS_SPLINES_B_SPLINE_MOCK_HPP_
