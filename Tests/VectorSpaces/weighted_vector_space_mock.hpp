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

#ifndef TESTS_VECTORSPACES_WEIGHTED_VECTOR_SPACE_MOCK_HPP_
#define TESTS_VECTORSPACES_WEIGHTED_VECTOR_SPACE_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/VectorSpaces/weighted_vector_space.hpp"

namespace splinelib::tests::vector_spaces {

class A3dWeightedVectorSpaceMock : public sources::vector_spaces::WeightedVectorSpace<3> {
 private:
  using Tolerance_ = sources::vector_spaces::Tolerance;

  constexpr static Precision const &kPrecision_ = sources::vector_spaces::kPrecision;
  constexpr static Tolerance_ const &kEpsilon_ = sources::vector_spaces::kEpsilon;

 public:
  MOCK_METHOD(HomogeneousCoordinate_ const &, OperatorSubscript, (Index const &), (const));
  HomogeneousCoordinate_ const & operator[](Index const &homogeneous_coordinate_index) const final;
  MOCK_METHOD(int, GetNumberOfCoordinates, (), (const, final));
  MOCK_METHOD(void, Insert, (Index const &, HomogeneousCoordinate_), (final));
  MOCK_METHOD(void, Replace, (Index const &, HomogeneousCoordinate_), (final));

  MOCK_METHOD(MaximumDistanceFromOriginAndMinimumWeight_, DetermineMaximumDistanceFromOriginAndMinimumWeightMock,
              (Tolerance_ const &), (const));
  MaximumDistanceFromOriginAndMinimumWeight_ DetermineMaximumDistanceFromOriginAndMinimumWeight(
      Tolerance_ const &tolerance = kEpsilon_) const final;
  MOCK_METHOD(OutputInformation_, WriteProjectedMock, (Precision const &), (const));
  OutputInformation_ WriteProjected(Precision const &precision = kPrecision_) const final;

  void NurbsBookExe4_4();  // See NURBS book Exe. 4.4.
  void NurbsBookExe4_4BSpline();
  void NurbsBookExe4_4Perturbed();
  void SquareUnit04();  // {0; 0; 0 | 2}, {1; 0; 0 | 2}, {0; 1; 0 | 2}, {1; 1; 0 | 2}
};

}  // namespace splinelib::tests::vector_spaces

#endif  // TESTS_VECTORSPACES_WEIGHTED_VECTOR_SPACE_MOCK_HPP_
