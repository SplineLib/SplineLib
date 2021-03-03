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

#include "Tests/VectorSpaces/weighted_vector_space_mock.hpp"

#include <cmath>

namespace splinelib::tests::vector_spaces {

namespace {

using HomogeneousCoordinate = A3dWeightedVectorSpaceMock::HomogeneousCoordinate_;
using testing::Return;

constexpr Coordinate const k0_0{0.0}, k1_0{1.0}, k2_0{2.0}, k3_0{3.0};
constexpr HomogeneousCoordinate const kHomogeneousCoordinate1_0{k0_0, k1_0, k3_0, k1_0},
    kHomogeneousCoordinate0_1{k2_0, k1_0, k1_0, k1_0}, kHomogeneousCoordinate1_1{k2_0, k0_0, k3_0, k1_0};

}  // namespace

HomogeneousCoordinate const & A3dWeightedVectorSpaceMock::operator[](Index const &homogeneous_coordinate_index) const {
  return OperatorSubscript(homogeneous_coordinate_index);
}

A3dWeightedVectorSpaceMock::MaximumDistanceFromOriginAndMinimumWeight_
A3dWeightedVectorSpaceMock::DetermineMaximumDistanceFromOriginAndMinimumWeight(Tolerance_ const &tolerance) const {
  return DetermineMaximumDistanceFromOriginAndMinimumWeightMock(tolerance);
}


A3dWeightedVectorSpaceMock::OutputInformation_ A3dWeightedVectorSpaceMock::WriteProjected(Precision const &precision)
    const {
  return WriteProjectedMock(precision);
}

void A3dWeightedVectorSpaceMock::NurbsBookExe4_4() {
  using sources::utilities::string_operations::Write;

  constexpr Weight const kWeight{1.0};
  String const kZero{Write(k0_0)}, kOne{Write(k1_0)}, kOneWeight(Write(kWeight)), kTwo{Write(k2_0)},
               kThree{Write(k3_0)};

  coordinates_.assign({HomogeneousCoordinate{k0_0, k0_0, k2_0, k2_0}, kHomogeneousCoordinate1_0,
                       kHomogeneousCoordinate0_1, kHomogeneousCoordinate1_1});

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(4));

  EXPECT_CALL(*this, DetermineMaximumDistanceFromOriginAndMinimumWeightMock(kEpsilon_))
      .WillRepeatedly(Return(MaximumDistanceFromOriginAndMinimumWeight_{Coordinate{std::sqrt(13.0)}, kWeight}));

  EXPECT_CALL(*this, WriteProjectedMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{{{kZero, kZero, kOne},
      {kZero, kOne, kThree}, {kTwo, kOne, kOne}, {kTwo, kZero, kThree}}, {Write(Weight{2.0}), kOneWeight, kOneWeight,
                                                                          kOneWeight}}));
}

void A3dWeightedVectorSpaceMock::NurbsBookExe4_4BSpline() {
  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(4));
}

void A3dWeightedVectorSpaceMock::NurbsBookExe4_4Perturbed() {
  constexpr Coordinate const k2_0Perturbed{2.0 + (1.1 * kEpsilon_)};

  coordinates_.assign({HomogeneousCoordinate{k0_0, k0_0, k2_0Perturbed, k2_0Perturbed}, kHomogeneousCoordinate1_0,
                       kHomogeneousCoordinate0_1, kHomogeneousCoordinate1_1});

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(4));
}

void A3dWeightedVectorSpaceMock::SquareUnit04() {
  coordinates_.assign({HomogeneousCoordinate{k0_0, k0_0, k0_0, k2_0}, HomogeneousCoordinate_{k2_0, k0_0, k0_0, k2_0},
                       HomogeneousCoordinate_{k0_0, k2_0, k0_0, k2_0}, HomogeneousCoordinate_{k2_0, k2_0, k0_0, k2_0}});
}

}  // namespace splinelib::tests::vector_spaces
