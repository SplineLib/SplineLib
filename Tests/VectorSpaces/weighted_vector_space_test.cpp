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

#include <cmath>
#include <utility>

#include <gtest/gtest.h>
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Sources/Utilities/string_operations.hpp"
#include "Sources/VectorSpaces/weighted_vector_space.hpp"
#include "Tests/VectorSpaces/vector_space_mock.hpp"
#include "Tests/VectorSpaces/weighted_vector_space_3d.hpp"

namespace splinelib::tests::vector_spaces {

using sources::vector_spaces::WeightedVectorSpace;

// Test weighted vector space form NURBS book Exe. 4.4.
class WeightedVectorSpaceSuite : public testing::Test {
 protected:
  using WeightedVectorSpace_ = WeightedVectorSpace<3>;
  using Coordinate_ = WeightedVectorSpace_::Coordinate_;

  constexpr static Coordinate const kCoordinate0_0_{0.0}, kCoordinate1_0_{1.0}, kCoordinate2_0_{2.0},
                                    kCoordinate3_0_{3.0};
  constexpr static Coordinate_ const kCoordinate0_{kCoordinate0_0_, kCoordinate0_0_, kCoordinate1_0_};
  constexpr static WeightedVectorSpace_::HomogeneousCoordinate_ const kHomogeneousCoordinate0_{kCoordinate0_0_,
      kCoordinate0_0_, kCoordinate2_0_, kCoordinate2_0_};
  constexpr static Weight const kWeight1_0_{1.0}, kWeight2_0_{2.0};

  WeightedVectorSpaceSuite();

  testing::StrictMock<A4dVectorSpaceMock> homogeneous_vector_space;
  WeightedVectorSpace_::Coordinates_ coordinates_{kCoordinate0_, {kCoordinate0_0_, kCoordinate1_0_, kCoordinate3_0_},
      {kCoordinate2_0_, kCoordinate1_0_, kCoordinate1_0_}, {kCoordinate2_0_, kCoordinate0_0_, kCoordinate3_0_}};
  WeightedVectorSpace_::Weights_ weights_{kWeight2_0_, kWeight1_0_, kWeight1_0_, kWeight1_0_};
  WeightedVectorSpace3d weighted_vector_space_;
};

WeightedVectorSpaceSuite::WeightedVectorSpaceSuite() {
  homogeneous_vector_space.NurbsBookExe4_4();
  weighted_vector_space_ = std::move(homogeneous_vector_space);
}

TEST_F(WeightedVectorSpaceSuite, IsEqualAndOperatorEqual) {
  using Tolerance = sources::vector_spaces::Tolerance;
  constexpr Tolerance const &kEpsilon = sources::vector_spaces::kEpsilon;
  constexpr Tolerance const kPerturbation{1.1 * kEpsilon};

  WeightedVectorSpace_ weighted_vector_space;
  ASSERT_NO_THROW(weighted_vector_space = WeightedVectorSpace_(coordinates_, weights_));
  EXPECT_TRUE(IsEqual(weighted_vector_space, weighted_vector_space_));
  EXPECT_TRUE(weighted_vector_space == weighted_vector_space_);

  coordinates_[0] = {kCoordinate0_0_, kCoordinate0_0_, kCoordinate1_0_ + Coordinate{kPerturbation}};
  weights_[0] = (kWeight2_0_ + Weight{kPerturbation});
  WeightedVectorSpace_ weighted_vector_space_perturbed;
  ASSERT_NO_THROW(weighted_vector_space_perturbed = WeightedVectorSpace_(coordinates_, weights_));
  EXPECT_FALSE(IsEqual(weighted_vector_space_perturbed, weighted_vector_space_));
  EXPECT_FALSE(weighted_vector_space_perturbed == weighted_vector_space_);
  EXPECT_TRUE(IsEqual(weighted_vector_space_perturbed, weighted_vector_space_, (1.0 + 2.0) * 1.2 * kEpsilon));
}

TEST_F(WeightedVectorSpaceSuite, Project) {
  EXPECT_EQ(WeightedVectorSpace_::Project(kHomogeneousCoordinate0_), kCoordinate0_);
}

TEST_F(WeightedVectorSpaceSuite, DetermineMaximumDistanceFromOriginAndMinimumWeight) {
  EXPECT_EQ(weighted_vector_space_.DetermineMaximumDistanceFromOriginAndMinimumWeight(),
            WeightedVectorSpace_::MaximumDistanceFromOriginAndMinimumWeight_(Coordinate{std::sqrt(13.0)}, kWeight1_0_));
}

TEST_F(WeightedVectorSpaceSuite, ProjectAndWrite) {
  String const kZero{"0"}, kOne{"1"}, kTwo{"2"}, kThree{"3"};

  EXPECT_EQ(weighted_vector_space_.WriteProjected(), (WeightedVectorSpace_::OutputInformation_{{{kZero, kZero, kOne},
                {kZero, kOne, kThree}, {kTwo, kOne, kOne}, {kTwo, kZero, kThree}}, {kTwo, kOne, kOne, kOne}}));
}

#ifndef NDEBUG
TEST_F(WeightedVectorSpaceSuite, ThrowIfNotEquallyManyCoordinatesAndWeightsAreProvided) {
  coordinates_.push_back(kCoordinate0_);
  EXPECT_THROW(WeightedVectorSpace_(coordinates_, weights_), DomainError);
}
#endif
}  // namespace splinelib::tests::vector_spaces
