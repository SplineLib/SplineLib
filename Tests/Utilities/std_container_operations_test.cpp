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
#include "Sources/Utilities/std_container_operations.hpp"

namespace splinelib::tests::utilities::std_container_operations {

using namespace splinelib::sources::utilities::std_container_operations;  // NOLINT(build/namespaces)
using std::sqrt;

class StdContainerOperationsTestSuite : public testing::Test {
 private:
  template<typename Name, typename Type>
  using NamedType_ = sources::utilities::NamedType<Name, Type>;

 protected:
  using Double_ = NamedType_<struct DoubleName, double>;
  using Int_ = NamedType_<struct IntName, int>;
  using Ints_ = Array<Int_, 6>;
  using DoubleTmp_ = Double_::Type_;
  using Doubles_ = Vector<Double_>;

  constexpr static DoubleTmp_ const kEpsilon_{sources::utilities::numeric_operations::GetEpsilon<DoubleTmp_>()};
  constexpr static DoubleTmp_ const &kTolerance_ = (1.2 * kEpsilon_);
  constexpr static Double_ const kMinus4_3_{-4.3}, kMinus4_0_{-4.0}, kMinus3_4_{-3.4}, kMinus0_4_{-0.4}, k0_0_{},
      k0_2_{0.2}, k0_5_{0.5}, k1_0_{1.0}, k1_2_{1.2}, k2_0_{2.0}, k2_9_{2.9}, k3_0_{3.0}, k4_0_{4.0};
  constexpr static Int_ const k0_{}, k1_{1}, k2_{2}, k3_{3}, k4_{4}, k5_{5}, k6_{6}, k8_{8};
  constexpr static Ints_ const kInts_{k3_, k2_, k1_, k0_, k1_, k2_};

  Ints_ ints_{k1_, k2_, k3_, k4_, k0_, k6_};
  Doubles_ doubles0_{k0_5_, k1_2_, k2_9_, kMinus3_4_, kMinus4_0_},
           doubles1_{Double_{-0.3}, Double_{1.6}, Double_{2.2}, Double_{-3.0}, k4_0_};
};

TEST_F(StdContainerOperationsTestSuite, IsArray) {
  EXPECT_TRUE((is_array<Array<int, 2>>));
  EXPECT_FALSE(is_array<Vector<int>>);
}

TEST_F(StdContainerOperationsTestSuite, IsVector) {
  EXPECT_FALSE((is_vector<Array<double, 3>>));
  EXPECT_TRUE(is_vector<Vector<double>>);
}

TEST_F(StdContainerOperationsTestSuite, GetFront) {
  Ints_::const_iterator const &ints_begin = ints_.begin();
  EXPECT_EQ(GetFront(ints_), *ints_begin);

  Doubles_::const_iterator const &doubles0_begin = doubles0_.begin();
  EXPECT_EQ(GetFront(doubles0_), *doubles0_begin);
}

TEST_F(StdContainerOperationsTestSuite, GetBack) {
  Ints_::const_reverse_iterator const &ints_rbegin = ints_.rbegin();
  EXPECT_EQ(GetBack(ints_), *ints_rbegin);

  Doubles_::const_reverse_iterator const &doubles0_rbegin = doubles0_.rbegin();
  EXPECT_EQ(GetBack(doubles0_), *doubles0_rbegin);
}

TEST_F(StdContainerOperationsTestSuite, GetValue) {
  EXPECT_EQ(GetValue(ints_, k3_), k4_);

  EXPECT_EQ(GetValue(doubles0_, k2_), k2_9_);
}

TEST_F(StdContainerOperationsTestSuite, TransformNamedTypes) {
  using TestTypeDoubles = Array<Double_, 6>;

  EXPECT_EQ(TransformNamedTypes<TestTypeDoubles>(ints_), (TestTypeDoubles{k1_0_, k2_0_, k3_0_, k4_0_, k0_0_,
                                                                          Double_{6.0}}));
  EXPECT_EQ(TransformNamedTypes<Ints_>(Doubles_{k1_0_, k2_0_, k3_0_, k3_0_, k2_0_, k1_0_}), (Ints_{k1_, k2_, k3_, k3_,
                                                                                                   k2_, k1_}));
  EXPECT_EQ(TransformNamedTypes<Doubles_>(kInts_), (Doubles_{k3_0_, k2_0_, k1_0_, k0_0_, k1_0_, k2_0_}));
}

TEST_F(StdContainerOperationsTestSuite, DoesContainEqualValuesDoesContainPointersToEqualValuesAndOperatorEqual) {
  using Double = SharedPointer<Double_>;
  using std::make_shared;

  constexpr Double_ const kMinus3_4Perturbed{kMinus3_4_ + Double_{1.1 * kEpsilon_}};
  Doubles_ const kDoubles{doubles0_}, kDoublesPerturbed{k0_5_, k1_2_, k2_9_, kMinus3_4Perturbed, kMinus4_0_};
  EXPECT_TRUE(DoesContainEqualValues(kDoubles, doubles0_));
  EXPECT_TRUE(kDoubles == doubles0_);
  EXPECT_FALSE(DoesContainEqualValues(kDoublesPerturbed, doubles0_));
  EXPECT_FALSE(kDoublesPerturbed == doubles0_);
  EXPECT_TRUE(DoesContainEqualValues(kDoublesPerturbed, doubles0_, kTolerance_));

  Double const &kMinus4_0 = make_shared<Double_>(kMinus4_0_), &kMinus3_4 = make_shared<Double_>(kMinus3_4_),
      &k0_5 = make_shared<Double_>(k0_5_), &k1_2 = make_shared<Double_>(k1_2_), &k2_9 = make_shared<Double_>(k2_9_);
  Vector<Double> const kDoublesPointers{k0_5, k1_2, k2_9, kMinus3_4, kMinus4_0},
      kDoublesPerturbedPointers{k0_5, k1_2, k2_9, make_shared<Double_>(kMinus3_4Perturbed), kMinus4_0};
  EXPECT_TRUE(DoesContainPointersToEqualValues(kDoublesPointers, kDoublesPointers));
  EXPECT_FALSE(DoesContainPointersToEqualValues(kDoublesPerturbedPointers, kDoublesPointers));
  EXPECT_TRUE(DoesContainPointersToEqualValues(kDoublesPerturbedPointers, kDoublesPointers, kTolerance_));

  Ints_ ints{ints_};
  EXPECT_TRUE(ints == ints_);
  EXPECT_NO_THROW(ints[0] = k0_);
  EXPECT_FALSE(ints == ints_);
}

TEST_F(StdContainerOperationsTestSuite, AddAndAssignToFirst) {
  EXPECT_EQ(AddAndAssignToFirst(doubles0_, doubles1_), (Doubles_{k0_2_, Double_{2.8}, Double_{5.1}, Double_{-6.4},
                                                                 k0_0_}));
  EXPECT_EQ(AddAndAssignToFirst(doubles0_, doubles1_, doubles1_), (Doubles_{kMinus0_4_, Double_{6.0}, Double_{9.5},
                                                                            Double_{-12.4}, Double_{8.0}}));

  EXPECT_EQ(AddAndAssignToFirst(ints_, kInts_), (Ints_{k4_, k4_, k4_, k4_, k1_, k8_}));
  EXPECT_EQ(AddAndAssignToFirst(ints_, kInts_, kInts_), (Ints_{Int_{10}, k8_, k6_, k4_, k3_, Int_{12}}));
}

TEST_F(StdContainerOperationsTestSuite, AddDependingOnAddAndAssignToFirst) {
  Doubles_ sum_double, doubles0{doubles0_};
  ASSERT_NO_THROW(sum_double = Add(doubles0_, doubles1_));
  EXPECT_EQ(sum_double, AddAndAssignToFirst(doubles0_, doubles1_));
  EXPECT_EQ(Add(doubles1_, doubles0), sum_double);

  Ints_ sum_int, ints{ints_};
  ASSERT_NO_THROW(sum_int = Add(ints_, kInts_));
  EXPECT_EQ(sum_int, AddAndAssignToFirst(ints_, kInts_));
  EXPECT_EQ(Add(kInts_, ints), sum_int);
}

TEST_F(StdContainerOperationsTestSuite, SubtractAndAssignToFirst) {
  constexpr Ints_ kZeros{k0_, k0_, k0_, k0_, k0_, k0_};

  EXPECT_EQ(SubtractAndAssignToFirst(doubles0_, doubles1_), (Doubles_{Double_{0.8}, kMinus0_4_, Double_{0.7},
                                                                      kMinus0_4_, Double_{-8.0}}));
  EXPECT_EQ(SubtractAndAssignToFirst(doubles0_, doubles1_, doubles1_),
            (Doubles_{Double_{1.4}, Double_{-3.6}, Double_{-3.7}, Double_{5.6}, Double_{-16.0}}));

  EXPECT_EQ(SubtractAndAssignToFirst(ints_, ints_), kZeros);
  EXPECT_EQ(SubtractAndAssignToFirst(ints_, ints_, ints_), kZeros);
}

TEST_F(StdContainerOperationsTestSuite, SubtractDependingOnSubtractAndAssignToFirst) {
  Doubles_ difference_double, doubles0{doubles0_};
  ASSERT_NO_THROW(difference_double = Subtract(doubles0_, doubles1_));
  EXPECT_EQ(difference_double, SubtractAndAssignToFirst(doubles0_, doubles1_));
  EXPECT_EQ(Subtract(doubles1_, doubles0), Multiply(difference_double, -1.0));

  EXPECT_EQ(Subtract(ints_, ints_), SubtractAndAssignToFirst(ints_, ints_));
}

TEST_F(StdContainerOperationsTestSuite, Multiply) {
  EXPECT_EQ(Multiply(doubles0_, 2.5), (Doubles_{Double_{1.25}, k3_0_, Double_{7.25}, Double_{-8.5}, Double_{-10.0}}));
}

TEST_F(StdContainerOperationsTestSuite, DivideAndAssignToFirst) {
  EXPECT_EQ(DivideAndAssignToFirst(doubles1_, 2.5), (Doubles_{Double_{-0.12}, Double_{0.64}, Double_{0.88},
                                                              Double_{-1.2}, Double_{1.6}}));
}

TEST_F(StdContainerOperationsTestSuite, DivideDependingOnDivideAndAssignToFirst) {
  Doubles_ quotient;
  ASSERT_NO_THROW(quotient = Divide(doubles0_, 2.5));
  EXPECT_EQ(quotient, (Doubles_{k0_2_, Double_{0.48}, Double_{1.16}, Double_{-1.36}, Double_{-1.6}}));
  EXPECT_EQ(quotient, Multiply(doubles0_, 0.4));
}

TEST_F(StdContainerOperationsTestSuite, DotProduct) {
  Double_ dot_product_double;
  ASSERT_NO_THROW(dot_product_double = DotProduct(doubles0_, doubles1_));
  EXPECT_EQ(dot_product_double, Double_{2.35});
  EXPECT_EQ(DotProduct(doubles1_, doubles0_), dot_product_double);
  EXPECT_EQ(DotProduct(doubles0_, Multiply(doubles1_, -1.0)), Double_{-dot_product_double.Get()});

  Int_ dot_product_int;
  ASSERT_NO_THROW(dot_product_int = DotProduct(ints_, kInts_));
  EXPECT_EQ(dot_product_int, Int_{22});
  EXPECT_EQ(DotProduct(kInts_, ints_), dot_product_int);
}

TEST_F(StdContainerOperationsTestSuite, TwoNormDependingOnDotProduct) {
  Double_ root;
  EXPECT_EQ(root = TwoNorm(doubles0_), Double_{sqrt(37.66)});
  EXPECT_EQ(Double_{sqrt(DotProduct(doubles0_, doubles0_).Get())}, root);
}

TEST_F(StdContainerOperationsTestSuite, EuclidianDistanceDependingOnSubtractAndTwoNorm) {
  Double_ distance;
  EXPECT_EQ(distance = EuclidianDistance(doubles0_, doubles1_), Double_{sqrt(65.45)});
  EXPECT_EQ(EuclidianDistance(doubles1_, doubles0_), distance);
  EXPECT_EQ(EuclidianDistance(doubles0_, Doubles_{k0_0_, k0_0_, k0_0_, k0_0_, k0_0_}), TwoNorm(doubles0_));
}

#ifndef NDEBUG
TEST_F(StdContainerOperationsTestSuite, ThrowIfIndexIsOutOfRange) {
  doubles1_.clear();
  EXPECT_THROW(GetValue(doubles0_, k5_), OutOfRange);
  EXPECT_THROW(GetFront(doubles1_), OutOfRange);
  EXPECT_THROW(GetBack(doubles1_), OutOfRange);

  Array<int, 0> array_empty;
  EXPECT_THROW(GetValue(ints_, k6_), OutOfRange);
  EXPECT_THROW(GetFront(array_empty), OutOfRange);
  EXPECT_THROW(GetBack(array_empty), OutOfRange);
}

TEST_F(StdContainerOperationsTestSuite, ThrowIfContainerSizesDiffer) {
  doubles1_.push_back(k0_0_);
  EXPECT_THROW(ThrowIfContainerSizesDiffer(doubles1_, doubles0_), InvalidArgument);
  EXPECT_THROW(TransformNamedTypes<Ints_>(Doubles_{k1_0_, k2_0_, k3_0_, k3_0_, k2_0_, k1_0_, k0_0_}), InvalidArgument);
}

TEST_F(StdContainerOperationsTestSuite, ThrowIfDivisonByZeroIsEncountered) {
  EXPECT_THROW(Divide(doubles0_, 2e-14), InvalidArgument);
  EXPECT_THROW(Divide(doubles0_, 3e-14, 3e-14), InvalidArgument);
}
#endif
}  // namespace splinelib::tests::utilities::std_container_operations
