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

#include <gtest/gtest.h>
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Sources/Utilities/numeric_operations.hpp"
#include "Sources/Utilities/std_container_operations.hpp"

namespace splinelib::tests::utilities {

using sources::utilities::NamedType;

class NamedTypeSuite : public testing::Test {
 protected:
  using TestTypeDouble_ = NamedType<struct TestTypeDoubleName, double>;
  using TestTypeInt_ = NamedType<struct TestTypeIntName, int>;

  constexpr static TestTypeDouble_ const kMinus0_5_{-0.5}, k1_0_{1.0}, k2_0_{2.0};
  constexpr static TestTypeInt_ const k0_{}, k1_{1}, k2_{2}, k3_{3}, k10_{10};

  TestTypeDouble_ test_type_double_{0.5};
  TestTypeInt_ test_type_int_{1};
};

TEST_F(NamedTypeSuite, OperatorAdditionAssignment) {
  EXPECT_EQ(test_type_double_ += k1_0_, TestTypeDouble_{1.5});

  EXPECT_EQ(test_type_int_ += k10_, TestTypeInt_{11});
}

TEST_F(NamedTypeSuite, OperatorSubtractionAssignment) {
  EXPECT_EQ(test_type_double_ -= k1_0_, kMinus0_5_);

  EXPECT_EQ(test_type_int_ -= k1_, k0_);
}

// Operator also works for doubles, but is considered to be confusing; hence, no corresponding test for doubles.
TEST_F(NamedTypeSuite, OperatorsPreIncrementPostIncrement) {
  EXPECT_EQ(++test_type_int_, k2_);
}

// Operator also works for doubles, but is considered to be confusing; hence, no corresponding test for doubles.
TEST_F(NamedTypeSuite, OperatorPreDecrement) {
  EXPECT_EQ(--test_type_int_, k0_);
}

TEST_F(NamedTypeSuite, OperatorAddition) {
  EXPECT_EQ(test_type_double_ + k2_0_, TestTypeDouble_{2.5});

  EXPECT_EQ(test_type_int_ + k2_, k3_);
}

TEST_F(NamedTypeSuite, OperatorSubtraction) {
  EXPECT_EQ(test_type_double_ - k2_0_, TestTypeDouble_{-1.5});

  EXPECT_EQ(test_type_int_ - k1_, k0_);
}

TEST_F(NamedTypeSuite, OperatorMultiplication) {
  EXPECT_EQ(test_type_double_ * k2_0_, k1_0_);
  EXPECT_EQ(test_type_double_ * 2.0, k1_0_);
  EXPECT_EQ(2.0 * test_type_double_, k1_0_);

  EXPECT_EQ(test_type_int_ * k2_, k2_);
  EXPECT_EQ(test_type_int_ * 2, k2_);
  EXPECT_EQ(2 * test_type_int_, k2_);
}

TEST_F(NamedTypeSuite, OperatorDivison) {
  constexpr static TestTypeDouble_ const k0_25{0.25};

  EXPECT_EQ(test_type_double_ / k2_0_, k0_25);
  EXPECT_EQ(test_type_double_ / 2.0, k0_25);
  EXPECT_EQ(2.0 / test_type_double_, TestTypeDouble_{4.0});

  EXPECT_EQ(test_type_int_ / k2_, k0_);
  EXPECT_EQ(test_type_int_ / 2, k0_);
  EXPECT_EQ(2 / test_type_int_, k2_);
}

TEST_F(NamedTypeSuite,
       IsEqualIsLessOrEqualIsGreaterOrEqualIsLessAndIsGreaterAndOperatorsEqualLessOrEqualGreaterOrEqualLessAndGreater) {
  using Type = TestTypeDouble_::Type_;

  constexpr Type const kEpsilon{sources::utilities::numeric_operations::GetEpsilon<Type>()}, kTolerance{1.2 * kEpsilon};
  constexpr TestTypeDouble_ const kTestTypeDouble{0.5}, kPerturbationInsignificant{0.9 * kEpsilon},
      kPerturbationSignificant{1.1 * kEpsilon}, kTestTypeDoublePerturbedMinus = (kTestTypeDouble -
          kPerturbationSignificant), kTestTypeDoubleMinus{kTestTypeDouble - kPerturbationInsignificant},
              kTestTypeDoublePlus{kTestTypeDouble + kPerturbationInsignificant},
                  kTestTypeDoublePerturbedPlus{kTestTypeDouble + kPerturbationSignificant};

  EXPECT_TRUE(IsEqual(test_type_double_, kTestTypeDouble));
  EXPECT_TRUE(test_type_double_ == kTestTypeDouble);
  EXPECT_FALSE(IsEqual(test_type_double_, kTestTypeDoublePerturbedMinus));
  EXPECT_FALSE(test_type_double_ == kTestTypeDoublePerturbedMinus);
  EXPECT_TRUE(IsEqual(test_type_double_, kTestTypeDoubleMinus, kTolerance));
  EXPECT_TRUE(IsEqual(test_type_double_, kTestTypeDoubleMinus));
  EXPECT_TRUE(test_type_double_ == kTestTypeDoubleMinus);
  EXPECT_TRUE(IsEqual(test_type_double_, kTestTypeDoublePlus));
  EXPECT_TRUE(test_type_double_ == kTestTypeDoublePlus);
  EXPECT_FALSE(IsEqual(test_type_double_, kTestTypeDoublePerturbedPlus));
  EXPECT_FALSE(test_type_double_ == kTestTypeDoublePerturbedPlus);
  EXPECT_TRUE(IsEqual(test_type_double_, kTestTypeDoublePerturbedPlus, kTolerance));
  EXPECT_FALSE(!IsEqual(test_type_double_, kTestTypeDouble));
  EXPECT_FALSE(test_type_double_ != kTestTypeDouble);
  EXPECT_TRUE(!IsEqual(test_type_double_, kTestTypeDoublePerturbedMinus));
  EXPECT_TRUE(test_type_double_ != kTestTypeDoublePerturbedMinus);
  EXPECT_FALSE(!IsEqual(test_type_double_, kTestTypeDoublePerturbedMinus, kTolerance));
  EXPECT_TRUE(IsLessOrEqual(test_type_double_, kTestTypeDouble));
  EXPECT_TRUE(test_type_double_ <= kTestTypeDouble);
  EXPECT_FALSE(IsLessOrEqual(test_type_double_, kTestTypeDoublePerturbedMinus));
  EXPECT_FALSE(test_type_double_ <= kTestTypeDoublePerturbedMinus);
  EXPECT_TRUE(IsLessOrEqual(test_type_double_, kTestTypeDoublePerturbedMinus, kTolerance));
  EXPECT_TRUE(IsLessOrEqual(test_type_double_, kTestTypeDoubleMinus));
  EXPECT_TRUE(test_type_double_ <= kTestTypeDoubleMinus);
  EXPECT_TRUE(IsGreaterOrEqual(test_type_double_, kTestTypeDouble));
  EXPECT_TRUE(test_type_double_ >= kTestTypeDouble);
  EXPECT_TRUE(IsGreaterOrEqual(test_type_double_, kTestTypeDoublePlus));
  EXPECT_TRUE(test_type_double_ >= kTestTypeDoublePlus);
  EXPECT_FALSE(IsGreaterOrEqual(test_type_double_, kTestTypeDoublePerturbedPlus));
  EXPECT_FALSE(test_type_double_ >= kTestTypeDoublePerturbedPlus);
  EXPECT_TRUE(IsGreaterOrEqual(test_type_double_, kTestTypeDoublePerturbedPlus, kTolerance));
  EXPECT_FALSE(IsLess(test_type_double_, kTestTypeDouble));
  EXPECT_FALSE(test_type_double_ < kTestTypeDouble);
  EXPECT_TRUE(IsLess(test_type_double_, kTestTypeDoublePerturbedPlus));
  EXPECT_TRUE(test_type_double_ < kTestTypeDoublePerturbedPlus);
  EXPECT_FALSE(IsLess(test_type_double_, kTestTypeDoublePerturbedPlus, kTolerance));
  EXPECT_FALSE(IsGreater(test_type_double_, kTestTypeDouble));
  EXPECT_FALSE(test_type_double_ > kTestTypeDouble);
  EXPECT_TRUE(IsGreater(test_type_double_, kTestTypeDoublePerturbedMinus));
  EXPECT_TRUE(test_type_double_ > kTestTypeDoublePerturbedMinus);
  EXPECT_FALSE(IsGreater(test_type_double_, kTestTypeDoublePerturbedMinus, kTolerance));

  EXPECT_TRUE(test_type_int_ == k1_);
  EXPECT_FALSE(test_type_int_ == k2_);
  EXPECT_FALSE(test_type_int_ != k1_);
  EXPECT_TRUE(test_type_int_ != k2_);
  EXPECT_TRUE(test_type_int_ <= k1_);
  EXPECT_FALSE(test_type_int_ <= k0_);
  EXPECT_TRUE(test_type_int_ >= k1_);
  EXPECT_FALSE(test_type_int_ >= k2_);
  EXPECT_TRUE(test_type_int_ < k2_);
  EXPECT_FALSE(test_type_int_ < k1_);
  EXPECT_TRUE(test_type_int_ > k0_);
  EXPECT_FALSE(test_type_int_ > k1_);
}

TEST_F(NamedTypeSuite, GetValue) {
  using sources::utilities::numeric_operations::IsEqual;

  EXPECT_TRUE(IsEqual(test_type_double_.Get(), 0.5));
  EXPECT_NO_THROW(test_type_double_.Get() = -0.5);
  EXPECT_TRUE(IsEqual(test_type_double_.Get(), -0.5));

  EXPECT_EQ(test_type_int_.Get(), 1);
  EXPECT_NO_THROW(test_type_int_.Get() = 0);
  EXPECT_EQ(test_type_int_.Get(), 0);
}

TEST_F(NamedTypeSuite, IsNamedType) {
  using sources::utilities::is_named_type;

  EXPECT_TRUE(is_named_type<TestTypeInt_>);
  EXPECT_FALSE(is_named_type<int>);
}

TEST_F(NamedTypeSuite, ForEach) {
  using TestTypeDoubles = Vector<TestTypeDouble_>;
  using TestTypeInts = Array<TestTypeInt_, 2>;

  TestTypeDoubles doubles{kMinus0_5_};
  EXPECT_NO_THROW(TestTypeInt_::ForEach(0, 1, [&] (TestTypeInt_ const &test_type_int) { doubles[test_type_int.Get()] =
      TestTypeDouble_{static_cast<TestTypeDouble_::Type_>(test_type_int.Get())} *  // NOLINT(whitespace/braces)
      test_type_double_; }));
  EXPECT_EQ(doubles, (TestTypeDoubles{TestTypeDouble_{} * kMinus0_5_}));  // NOLINT(whitespace/braces)

  TestTypeInts integers{test_type_int_, test_type_int_};
  EXPECT_NO_THROW(TestTypeInt_::ForEach(0, 2, [&] (TestTypeInt_ const &test_type_int) { integers[test_type_int.Get()] +=
                                                                                            test_type_int; }));
  EXPECT_EQ(integers, (TestTypeInts{k1_, k2_}));
}

#ifndef NDEBUG
TEST_F(NamedTypeSuite, ThrowIfNamedIntegerIsNegative) {
  EXPECT_THROW(TestTypeInt_{-1}, DomainError);
}

TEST_F(NamedTypeSuite, ThrowIfDivisonByZeroEncountered) {
  EXPECT_THROW(test_type_double_ / TestTypeDouble_{}, DomainError);
  EXPECT_THROW(test_type_double_ / 0.0, DomainError);
  EXPECT_THROW(2.0 / TestTypeDouble_{}, DomainError);
  EXPECT_THROW(test_type_int_ / k0_, DomainError);
  EXPECT_THROW(test_type_int_ / 0, DomainError);
  EXPECT_THROW(2 / k0_, DomainError);
}

TEST_F(NamedTypeSuite, ThrowIfNamedIntegerIsOutOfBounds) {
  EXPECT_THROW(TestTypeInt_::ThrowIfNamedIntegerIsOutOfBounds(k3_, 2), OutOfRange);
}
#endif
}  // namespace splinelib::tests::utilities
