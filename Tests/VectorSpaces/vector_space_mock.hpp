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

#ifndef TESTS_VECTORSPACES_VECTOR_SPACE_MOCK_HPP_
#define TESTS_VECTORSPACES_VECTOR_SPACE_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/VectorSpaces/vector_space.hpp"

namespace splinelib::tests::vector_spaces {

using sources::vector_spaces::VectorSpace;
class A3dVectorSpaceMock : public VectorSpace<3> {
 private:
  using Tolerance_ = sources::vector_spaces::Tolerance;

  constexpr static Precision const &kPrecision_ = sources::vector_spaces::kPrecision;
  constexpr static Tolerance_ const &kEpsilon_ = sources::vector_spaces::kEpsilon;

 public:
  MOCK_METHOD(Coordinate_ const &, OperatorSubscript, (Index const &), (const));
  Coordinate_ const & operator[](Index const &coordinate) const final;
  MOCK_METHOD(int, GetNumberOfCoordinates, (), (const, final));
  MOCK_METHOD(void, Replace, (Index const &, Coordinate_), (final));
  MOCK_METHOD(void, Insert, (Index const &, Coordinate_), (final));
  MOCK_METHOD(void, Erase, (Index const &), (final));

  MOCK_METHOD(Coordinate, DetermineMaximumDistanceMock, (Tolerance_ const &), (const));
  Coordinate DetermineMaximumDistanceFromOrigin(Tolerance_ const &tolerance = kEpsilon_) const final;
  MOCK_METHOD(OutputInformation_, WriteMock, (Precision const &), (const));
  OutputInformation_ Write(Precision const &precision = kPrecision_) const final;

  void NurbsBookExe3_8();  // See NURBS book Exe. 3.8.
  void NurbsBookExe3_8ElevatedTwice();
  void NurbsBookExe3_8ElevateOnce();
  void NurbsBookExe3_8ElevateReduce();
  void NurbsBookExe3_8ElevateTwice();
  void NurbsBookExe3_8Insert();
  void NurbsBookExe3_8InsertRemove();
  void NurbsBookExe3_8Perturbed();
  void NurbsBookExe3_8ReduceOnce();
  void NurbsBookExe3_8ReduceTwice();
  void NurbsBookExe3_8Remove();
  void NurbsBookExe3_8Subdivided();
  void NurbsBookExe3_8Unsuccessful();
  void NurbsBookExe4_4();  // See NURBS book Exe. 4.4.
  void SquareUnit04();  // {0; 0; 0}, {1; 0; 0}, {0; 1; 0}, {1; 1; 0}
  void SquareUnit12();  // {0; 0; 0}, {1/3; 0; 0}, {2/3; 0; 0}, {1; 0; 0}, {0; 0.5; 0}, {1/3, 0.5, 0}, ..., {1; 1; 0}

 private:
  using Expectation_ = testing::Expectation;

  void NurbsBookExe3_8Bezier(Expectation_ const &expectation);
  void NurbsBookExe3_8BezierElevatedReducedOnce(Expectation_ const &expectation);
  void NurbsBookExe3_8BezierElevatedTwice(Expectation_ const &expectation);
  void NurbsBookExe3_8BezierElevatedTwiceMakeBSpline(Expectation_ const &expectation);
  void NurbsBookExe3_8BezierReducedTwiceMakeBSpline(Expectation_ const &expectation);
  void NurbsBookExe3_8ElevateReduce(Expectation_ const &expectation);
  void NurbsBookExe3_8InsertRemove(Expectation_ const &expectation);
  void NurbsBookExe3_8Subdivided(Expectation_ const &expectation);
};

class A4dVectorSpaceMock : public VectorSpace<4> {
 public:
  MOCK_METHOD(Coordinate_ const &, OperatorSubscript, (Index const &), (const));
  Coordinate_ const & operator[](Index const &coordinate) const final;

  void NurbsBookExe4_4();  // See NURBS book Exe. 4.4.
  void NurbsBookExe4_4NonRational();
  void SquareUnit04();  // {0; 0; 0; 2}, {2; 0; 0; 2}, {0; 2; 0; 2}, {2; 2; 0; 2}
};

}  // namespace splinelib::tests::vector_spaces

#endif  // TESTS_VECTORSPACES_VECTOR_SPACE_MOCK_HPP_
