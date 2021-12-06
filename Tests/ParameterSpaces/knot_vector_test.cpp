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
#include "Sources/ParameterSpaces/knot_vector.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/std_container_operations.hpp"

namespace splinelib::tests::parameter_spaces {

using sources::parameter_spaces::KnotVector;

// Test with knot vector U = {0.0, 0.0, 0.0, 0.5, 0.5, 0.75, 1.0, 1.0, 1.0}.
class KnotVectorSuite : public testing::Test {
 protected:
  using Knots_ = KnotVector::Knots_;

  constexpr static Index kIndex8_{8};
  constexpr static sources::parameter_spaces::Tolerance const &kEpsilon_ = sources::parameter_spaces::kEpsilon,
                                                              &kTolerance_ = (1.2 * kEpsilon_);
  constexpr static Multiplicity const &kMultiplicity1_ = sources::parameter_spaces::kMultiplicity;
  constexpr static Multiplicity const kMultiplicity2_{2};
  constexpr static ParametricCoordinate const k0_0_{}, k0_5_{0.5}, k0_75_{0.75}, k1_0_{1.0}, kPerturbation_{1.1 *
                                                                                                            kEpsilon_};
  constexpr static ParametricCoordinate const &k0_5Perturbed_ = (k0_5_ - kPerturbation_),
      &k0_75Perturbed_ = (k0_75_ - kPerturbation_), &k1_0Minus_ = (k1_0_ - kPerturbation_);
  inline static Knots_ const kKnotsPerturbed{k0_0_, k0_0_, k0_0_, k0_5_, k0_5Perturbed_, k0_75_, k1_0_, k1_0_, k1_0_};

  Knots_ knots_{k0_0_, k0_0_, k0_0_, k0_5_, k0_5_, k0_75_, k1_0_, k1_0_, k1_0_};
  KnotVector knot_vector_{knots_}, knot_vector_perturbed_{kKnotsPerturbed, kTolerance_};
};

TEST_F(KnotVectorSuite, IsEqualAndOperatorEqual) {
  KnotVector knot_vector;
  ASSERT_NO_THROW(knot_vector = KnotVector(knots_));
  EXPECT_TRUE(IsEqual(knot_vector, knot_vector_));
  EXPECT_TRUE(knot_vector == knot_vector_);

  EXPECT_FALSE(IsEqual(knot_vector_perturbed_, knot_vector_));
  EXPECT_FALSE(knot_vector_perturbed_ == knot_vector_);
  EXPECT_TRUE(IsEqual(knot_vector_perturbed_, knot_vector_, kTolerance_));
}

TEST_F(KnotVectorSuite, OperatorSubscript) {
  EXPECT_EQ(knot_vector_[kIndex8_], k1_0_);
}

TEST_F(KnotVectorSuite, GetSize) {
  EXPECT_EQ(knot_vector_.GetSize(), 9);
}

TEST_F(KnotVectorSuite, GetFront) {
  EXPECT_EQ(knot_vector_.GetFront(), k0_0_);
}

TEST_F(KnotVectorSuite, GetBack) {
  EXPECT_EQ(knot_vector_.GetBack(), k1_0_);
}

TEST_F(KnotVectorSuite, DoesParametricCoordinateEqualBackDependingOnGetBack) {
  EXPECT_TRUE(knot_vector_.DoesParametricCoordinateEqualBack(k1_0_));
  EXPECT_FALSE(knot_vector_.DoesParametricCoordinateEqualBack(k1_0Minus_));
  EXPECT_TRUE(knot_vector_.DoesParametricCoordinateEqualBack(k1_0Minus_, kTolerance_));
}

TEST_F(KnotVectorSuite, DoesParametricCoordinateEqualFrontOrBackDependingOnGetFrontAndDoesParametricCoordinateEqualBack)
{  // NOLINT(whitespace/braces)
  constexpr ParametricCoordinate const k0_0Plus{k0_0_ + kPerturbation_};

  EXPECT_TRUE(knot_vector_.DoesParametricCoordinateEqualFrontOrBack(k0_0_));
  EXPECT_TRUE(knot_vector_.DoesParametricCoordinateEqualFrontOrBack(k1_0_));
  EXPECT_FALSE(knot_vector_.DoesParametricCoordinateEqualFrontOrBack(k0_0Plus));
  EXPECT_FALSE(knot_vector_.DoesParametricCoordinateEqualFrontOrBack(k1_0Minus_));
  EXPECT_TRUE(knot_vector_.DoesParametricCoordinateEqualFrontOrBack(k0_0Plus, kTolerance_));
  EXPECT_TRUE(knot_vector_.DoesParametricCoordinateEqualFrontOrBack(k1_0Minus_, kTolerance_));
}

TEST_F(KnotVectorSuite, FindSpan) {
  constexpr KnotSpan const kKnotSpan5{5};

  EXPECT_EQ(knot_vector_.FindSpan(k0_0_), KnotSpan{2});
  EXPECT_EQ(knot_vector_.FindSpan(k0_75_), kKnotSpan5);
  EXPECT_EQ(knot_vector_.FindSpan(k0_75Perturbed_), KnotSpan{4});
  EXPECT_EQ(knot_vector_.FindSpan(k0_75Perturbed_, kTolerance_), kKnotSpan5);
  EXPECT_EQ(knot_vector_.FindSpan(k1_0_), kKnotSpan5);
}

TEST_F(KnotVectorSuite, DetermineMultiplicity) {
  EXPECT_EQ(knot_vector_.DetermineMultiplicity(k0_0_), Multiplicity{3});
  Multiplicity multiplicity;
  EXPECT_EQ(multiplicity = knot_vector_.DetermineMultiplicity(k0_75_), kMultiplicity1_);
  EXPECT_EQ(knot_vector_.DetermineMultiplicity(k0_75Perturbed_), Multiplicity{});
  EXPECT_EQ(knot_vector_.DetermineMultiplicity(k0_75Perturbed_, kTolerance_), multiplicity);
}

TEST_F(KnotVectorSuite, GetUniqueKnots) {
  Knots_ unique_knots;
  EXPECT_EQ(unique_knots = knot_vector_.GetUniqueKnots(), (Knots_{k0_0_, k0_5_, k0_75_, k1_0_}));
  EXPECT_EQ(knot_vector_perturbed_.GetUniqueKnots(), (Knots_{k0_0_, k0_5_, k0_5Perturbed_, k0_75_, k1_0_}));
  EXPECT_TRUE(sources::utilities::std_container_operations::DoesContainEqualValues(
                  knot_vector_perturbed_.GetUniqueKnots(kTolerance_), unique_knots, kTolerance_));
}

TEST_F(KnotVectorSuite, Insert) {
  constexpr ParametricCoordinate const kKnot{0.25};

  EXPECT_NO_THROW(knot_vector_.Insert(kKnot));
  ASSERT_NO_THROW(knots_.insert(knots_.begin() + 3, kKnot));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_NO_THROW(knot_vector_.Insert(kKnot, kMultiplicity2_));
  ASSERT_NO_THROW(knots_.insert(knots_.begin() + 4, 2, kKnot));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_NO_THROW(knot_vector_.Insert(k0_75Perturbed_));
  ASSERT_NO_THROW(knots_.insert(knots_.begin() + 8, k0_75Perturbed_));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_NO_THROW(knot_vector_.Insert(k0_75Perturbed_, kMultiplicity1_, kTolerance_));
  ASSERT_NO_THROW(knots_.insert(knots_.begin() + 10, k0_75Perturbed_));
  EXPECT_EQ(knot_vector_, KnotVector(knots_, kTolerance_));
}

TEST_F(KnotVectorSuite, Remove) {
  EXPECT_EQ(knot_vector_.Remove(k1_0Minus_), Multiplicity{});
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_EQ(knot_vector_.Remove(k1_0_), kMultiplicity1_);
  ASSERT_NO_THROW(knots_.erase(knots_.begin() + 8));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_EQ(knot_vector_.Remove(k1_0_, kMultiplicity2_), kMultiplicity2_);
  ASSERT_NO_THROW(knots_.erase(knots_.begin() + 6, knots_.begin() + 8));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_EQ(knot_vector_.Remove(k0_0_), kMultiplicity1_);
  ASSERT_NO_THROW(knots_.erase(knots_.begin() + 2));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
  EXPECT_EQ(knot_vector_.Remove(k0_0_, kMultiplicity2_), kMultiplicity2_);
  ASSERT_NO_THROW(knots_.erase(knots_.begin(), knots_.begin() + 2));
  EXPECT_EQ(knot_vector_, KnotVector(knots_));
}

TEST_F(KnotVectorSuite, IncreaseMultiplicitiesDependingOnGetUniqueKnots) {
  KnotVector knot_vector{knot_vector_};
  EXPECT_NO_THROW(knot_vector_.IncreaseMultiplicities());
  EXPECT_EQ(knot_vector_, KnotVector({k0_0_, k0_0_, k0_0_, k0_0_, k0_5_, k0_5_, k0_5_, k0_75_, k0_75_, k1_0_, k1_0_,
                                      k1_0_, k1_0_}));
  EXPECT_NO_THROW(knot_vector_perturbed_.IncreaseMultiplicities(kMultiplicity1_, kTolerance_));
  EXPECT_TRUE(IsEqual(knot_vector_perturbed_, knot_vector_, kTolerance_));
  EXPECT_NO_THROW(knot_vector_.IncreaseMultiplicities());
  EXPECT_EQ(knot_vector_, KnotVector({k0_0_, k0_0_, k0_0_, k0_0_, k0_0_, k0_5_, k0_5_, k0_5_, k0_5_, k0_75_, k0_75_,
                                      k0_75_, k1_0_, k1_0_, k1_0_, k1_0_, k1_0_}));
  EXPECT_NO_THROW(knot_vector.IncreaseMultiplicities(kMultiplicity2_));
  EXPECT_EQ(knot_vector, knot_vector_);
}

TEST_F(KnotVectorSuite, DecreaseMultiplicitiesDependingOnGetUniqueKnots) {
  KnotVector knot_vector{knot_vector_};
  EXPECT_NO_THROW(knot_vector_.DecreaseMultiplicities());
  EXPECT_EQ(knot_vector_, KnotVector({k0_0_, k0_0_, k0_5_, k1_0_, k1_0_}));
  EXPECT_NO_THROW(knot_vector_perturbed_.DecreaseMultiplicities(kMultiplicity1_, kTolerance_));
  EXPECT_TRUE(IsEqual(knot_vector_perturbed_, knot_vector_, kTolerance_));
  EXPECT_NO_THROW(knot_vector_.DecreaseMultiplicities());
  EXPECT_EQ(knot_vector_, KnotVector({k0_0_, k1_0_}));
  EXPECT_NO_THROW(knot_vector.DecreaseMultiplicities(kMultiplicity2_));
  EXPECT_EQ(knot_vector, knot_vector_);
  Knots_ knots{k0_0_, k1_0_};
  KnotVector knot_vector_minimum;
  ASSERT_NO_THROW(knot_vector_minimum = KnotVector(knots));
  EXPECT_NO_THROW(knot_vector_minimum.DecreaseMultiplicities());
  EXPECT_EQ(knot_vector_minimum, KnotVector(knots));
}

TEST_F(KnotVectorSuite, Write) {
  using sources::utilities::string_operations::Write;

  String const kZero{Write(k0_0_)}, kZeroFive{Write(k0_5_)}, kOne{Write(k1_0_)};

  EXPECT_EQ(knot_vector_.Write(), (KnotVector::OutputInformation_{kZero, kZero, kZero, kZeroFive, kZeroFive,
                                                                  Write(k0_75_), kOne, kOne, kOne}));
}

#ifndef NDEBUG
TEST_F(KnotVectorSuite, ThrowIfNumberOfKnotsIsTooSmall) {
  EXPECT_THROW(KnotVector({k0_0_}), DomainError);
}

TEST_F(KnotVectorSuite, ThrowIfNumberOfKnotsIsNotNonDecreasing) {
  EXPECT_THROW(KnotVector{kKnotsPerturbed}, DomainError);
  KnotVector knot_vector;
  ASSERT_NO_THROW(knot_vector = KnotVector(kKnotsPerturbed, kTolerance_));
  EXPECT_THROW(knot_vector.DoesParametricCoordinateEqualBack(k0_5_), DomainError);
  EXPECT_THROW(knot_vector.FindSpan(k0_5_), DomainError);
  EXPECT_THROW(knot_vector.DetermineMultiplicity(k0_5_), DomainError);
  EXPECT_THROW(knot_vector.Insert(k0_5_), DomainError);
  EXPECT_THROW(knot_vector.Remove(k0_5_), DomainError);
}

TEST_F(KnotVectorSuite, ThrowIfIndexIsInvalid) {
  EXPECT_THROW(knot_vector_[Index{9}], OutOfRange);
}

TEST_F(KnotVectorSuite, ThrowIfParametricCoordinateIsOutsideScopeDependingOnGetFrontAndGetBack) {
  constexpr ParametricCoordinate const k1_0Plus{k1_0_ + kPerturbation_};

  EXPECT_THROW(knot_vector_.FindSpan(k1_0Plus), OutOfRange);
  EXPECT_THROW(knot_vector_.Insert(k1_0Plus), OutOfRange);
}
#endif
}  // namespace splinelib::tests::parameter_spaces
