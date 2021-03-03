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

#include <gtest/gtest.h>
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Sources/Utilities/string_operations.hpp"
#include "Sources/VectorSpaces/vector_space.hpp"

namespace splinelib::tests::vector_spaces {

using sources::vector_spaces::VectorSpace;

// Test vector space from NURBS book Exe. 3.8.
class VectorSpaceSuite : public testing::Test {
 protected:
  using VectorSpace_ = VectorSpace<3>;
  using Coordinate_ = VectorSpace_::Coordinate_;
  using Coordinates_ = VectorSpace_::Coordinates_;

  constexpr static Index const kIndex4_{4};
  constexpr static Coordinate const k0_0_{0.0}, k2_0_{2.0}, k3_0_{3.0}, k4_0_{4.0}, k5_0_{5.0}, k6_0_{6.0}, k9_0_{9.0};
  constexpr static Coordinate_ const kCoordinate0_{k0_0_, k0_0_, k0_0_}, kCoordinate4_{k0_0_, k2_0_, k2_0_};

  Coordinates_ coordinates_{kCoordinate0_, Coordinate_{k3_0_, k0_0_, k3_0_}, Coordinate_{k6_0_, k0_0_, k3_0_},
      Coordinate_{k9_0_, k0_0_, k0_0_}, kCoordinate4_, Coordinate_{k3_0_, k2_0_, k5_0_}, Coordinate_{k6_0_, k2_0_,
          k5_0_}, Coordinate_{k9_0_, k2_0_, k2_0_}, Coordinate_{k0_0_, k4_0_, k0_0_}, Coordinate_{k3_0_, k4_0_, k3_0_},
              Coordinate_{k6_0_, k4_0_, k3_0_}, Coordinate_{k9_0_, k4_0_, k0_0_}};
  Coordinates_::iterator const kIndex_{coordinates_.begin() + kIndex4_.Get()};
  VectorSpace_ vector_space_{coordinates_};
};

TEST_F(VectorSpaceSuite, IsEqualAndOperatorEqual) {
  constexpr sources::vector_spaces::Tolerance const &kEpsilon = sources::vector_spaces::kEpsilon;

  VectorSpace_ vector_space;
  ASSERT_NO_THROW(vector_space = VectorSpace_{coordinates_});
  EXPECT_TRUE(IsEqual(vector_space, vector_space_));
  EXPECT_TRUE(vector_space == vector_space_);

  coordinates_[0] = Coordinate_{k0_0_, k0_0_, Coordinate{1.1 * kEpsilon}};
  VectorSpace_ vector_space_perturbed;
  ASSERT_NO_THROW(vector_space_perturbed = VectorSpace_{coordinates_});
  EXPECT_FALSE(IsEqual(vector_space_perturbed, vector_space_));
  EXPECT_FALSE(vector_space_perturbed == vector_space_);
  EXPECT_TRUE(IsEqual(vector_space_perturbed, vector_space_, 1.2 * kEpsilon));
}

TEST_F(VectorSpaceSuite, OperatorIndex) {
  EXPECT_EQ(vector_space_[kIndex4_], kCoordinate4_);
}

TEST_F(VectorSpaceSuite, GetNumberOfCoordinates) {
  EXPECT_EQ(vector_space_.GetNumberOfCoordinates(), 12);
}

TEST_F(VectorSpaceSuite, Replace) {
  coordinates_[kIndex4_.Get()] = kCoordinate0_;
  EXPECT_NO_THROW(vector_space_.Replace(kIndex4_, kCoordinate0_));
  EXPECT_EQ(vector_space_, VectorSpace_{coordinates_});
}

TEST_F(VectorSpaceSuite, Insert) {
  coordinates_.insert(kIndex_, kCoordinate4_);
  EXPECT_NO_THROW(vector_space_.Insert(kIndex4_, kCoordinate4_));
  EXPECT_EQ(vector_space_, VectorSpace_{coordinates_});
}

TEST_F(VectorSpaceSuite, Erase) {
  coordinates_.erase(kIndex_);
  EXPECT_NO_THROW(vector_space_.Erase(kIndex4_));
  EXPECT_EQ(vector_space_, VectorSpace_{coordinates_});
}

TEST_F(VectorSpaceSuite, DetermineMaximumDistanceFromOrigin) {
  EXPECT_TRUE(IsEqual(vector_space_.DetermineMaximumDistanceFromOrigin(), Coordinate{std::sqrt(97.0)}));
}

TEST_F(VectorSpaceSuite, Write) {
  String const kZero{"0"}, kTwo{"2"}, kThree{"3"}, kFour{"4"}, kFive{"5"}, kSix{"6"}, kNine{"9"};

  EXPECT_EQ(vector_space_.Write(), (VectorSpace_::OutputInformation_{{{kZero, kZero, kZero}, {kThree, kZero, kThree},
                {kSix, kZero, kThree}, {kNine, kZero, kZero}, {kZero, kTwo, kTwo}, {kThree, kTwo, kFive}, {kSix, kTwo,
                    kFive}, {kNine, kTwo, kTwo}, {kZero, kFour, kZero}, {kThree, kFour, kThree}, {kSix, kFour, kThree},
                        {kNine, kFour, kZero}}}));
}

#ifndef NDEBUG
TEST_F(VectorSpaceSuite, ThrowIfIndexValueInvalid) {
  constexpr Index const kIndex12{12};

  EXPECT_THROW(vector_space_[kIndex12], OutOfRange);
  EXPECT_THROW(vector_space_.Replace(kIndex12, kCoordinate0_), OutOfRange);
  EXPECT_THROW(vector_space_.Insert(kIndex12, kCoordinate0_), OutOfRange);
  EXPECT_THROW(vector_space_.Erase(kIndex12), OutOfRange);
}
#endif
}  // namespace splinelib::tests::vector_spaces
