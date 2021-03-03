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
#include "Sources/Utilities/index.hpp"

namespace splinelib::tests::utilities {

using sources::utilities::Index;

class IndexSuite : public testing::Test {
 protected:
  using DoubleIndex_ = Index<2>;
  using Index_ = splinelib::Index;
  using SingleIndex_ = Index<1>;
  using TripleIndex_ = Index<3>;
  using QuadrupleIndex_ = Index<4>;
  using SingleIndexLength_ = SingleIndex_::Length_;
  using SingleIndexValue_ = SingleIndex_::Value_;
  using TripleIndexLength_ = TripleIndex_::Length_;
  using TripleIndexValue_ = TripleIndex_::Value_;

  constexpr static Dimension const kDimension0_{}, kDimension1_{1};
  constexpr static Length const kLength0_{}, kLength2_{2}, kLength3_{3}, kLength4_{4}, kLength5_{5}, kLength10_{10};
  constexpr static Index_ const kIndex0_{}, kIndex1_{1}, kIndex2_{2}, kIndex3_{3}, kIndex4_{4}, kIndex5_{5},
                                kIndex9_{9};
  constexpr static SingleIndexLength_ const kLength1d_{kLength10_};
  constexpr static DoubleIndex_::Length_ const kLength2d_{kLength3_, kLength4_};
  constexpr static TripleIndexLength_ const kLength3d_{kLength5_, kLength5_, kLength0_};
  constexpr static QuadrupleIndex_::Length_ const kLength4d_{kLength2_, kLength2_, kLength4_, kLength4_};
  constexpr static SingleIndexValue_ const kValue1d_{kIndex5_};
  constexpr static DoubleIndex_::Value_ const kValue2d_{kIndex1_, kIndex1_};
  constexpr static QuadrupleIndex_::Value_ const kValue4d_{kIndex0_, kIndex1_, kIndex2_, kIndex3_};
  inline static SingleIndex_ const kIndex1d_{kLength1d_, {kIndex5_}};
  inline static DoubleIndex_ const kIndex2d_{kLength2d_, kValue2d_};
  inline static QuadrupleIndex_ const kIndex4d_{kLength4d_, kValue4d_};
  inline static Index<5> const kIndex5d_{{kLength3_, kLength4_, kLength5_, Length{6}, kLength5_}};

  SingleIndex_ index_1d_{kLength1d_, {kIndex0_}}, index_1d_last_{kLength1d_, {kIndex9_}};
  TripleIndex_ index_3d_{kLength3d_, {kIndex4_, kIndex4_, kIndex0_}};
  QuadrupleIndex_ index_4d_{kLength4d_};
};

TEST_F(IndexSuite, OperatorAdditionAssignment) {
  EXPECT_EQ(index_1d_ += kValue1d_, kIndex1d_);

  EXPECT_EQ(index_4d_ += kValue4d_, kIndex4d_);
}

TEST_F(IndexSuite, OperatorSubtractionAssignment) {
  EXPECT_EQ(SingleIndex_(kLength1d_, kValue1d_) -= kValue1d_, index_1d_);

  EXPECT_EQ(QuadrupleIndex_(kLength4d_, kValue4d_) -= kValue4d_, index_4d_);
}

TEST_F(IndexSuite, OperatorsPreIncrementAndIncrement) {
  EXPECT_EQ(++index_1d_, SingleIndex_(kLength1d_, {kIndex1_}));
  EXPECT_EQ(index_1d_.Increment(kDimension0_), SingleIndex_(kLength1d_, {kIndex2_}));
  EXPECT_EQ(index_1d_.Increment(kDimension0_), ++index_1d_);

  EXPECT_EQ(++index_3d_, TripleIndex_::Behind(kLength3d_));

  EXPECT_EQ(++index_4d_, QuadrupleIndex_(kLength4d_, {kIndex1_, kIndex0_, kIndex0_, kIndex0_}));
  EXPECT_EQ(index_4d_.Increment(kDimension1_), QuadrupleIndex_(kLength4d_, {kIndex1_, kIndex1_, kIndex0_, kIndex0_}));
}

TEST_F(IndexSuite, OperatorsPreDecrementAndDecrement) {
  EXPECT_EQ(--index_1d_last_, SingleIndex_(kLength1d_, {Index_{8}}));
  EXPECT_EQ(index_1d_last_.Decrement(kDimension0_), SingleIndex_(kLength1d_, {Index_{7}}));

  EXPECT_EQ(--index_3d_, TripleIndex_(kLength3d_, {kIndex3_, kIndex4_, kIndex0_}));
  EXPECT_EQ(index_3d_.Decrement(kDimension1_), TripleIndex_(kLength3d_, {kIndex3_, kIndex3_, kIndex0_}));
  EXPECT_EQ(index_3d_.Decrement(kDimension0_), --index_3d_);

  EXPECT_EQ(--index_4d_, QuadrupleIndex_::Before({kLength4d_}));
}

TEST_F(IndexSuite, OperatorAddition) {
  EXPECT_EQ(index_1d_ + kValue1d_, kIndex1d_);

  EXPECT_EQ(index_4d_ + kValue4d_, kIndex4d_);
}

TEST_F(IndexSuite, OperatorSubtraction) {
  EXPECT_EQ(kIndex1d_ - kValue1d_, index_1d_);

  EXPECT_EQ(kIndex4d_ - kValue4d_, index_4d_);
}

TEST_F(IndexSuite, OperatorsEqualAndNotEqual) {
  DoubleIndex_ index_2d_invalid, index_2d_length, index_2d_value;
  ASSERT_NO_THROW(index_2d_invalid = DoubleIndex_({kLength4_, kLength4_}, kValue2d_, true));
  ASSERT_NO_THROW(index_2d_length = DoubleIndex_({kLength4_, kLength4_}, kValue2d_));
  ASSERT_NO_THROW(index_2d_value = DoubleIndex_(kLength2d_, {kIndex0_, kIndex2_}));
  EXPECT_TRUE(kIndex2d_ == DoubleIndex_(kLength2d_, {kIndex1_, kIndex1_}));
  EXPECT_FALSE(index_2d_invalid == kIndex2d_);
  EXPECT_FALSE(index_2d_length == kIndex2d_);
  EXPECT_FALSE(index_2d_value == kIndex2d_);
  EXPECT_TRUE(index_2d_invalid != kIndex2d_);
  EXPECT_TRUE(index_2d_length != kIndex2d_);
  EXPECT_TRUE(index_2d_value != kIndex2d_);
}

TEST_F(IndexSuite, OperatorSubscript) {
  EXPECT_EQ(index_1d_[kDimension0_], kIndex0_);

  EXPECT_EQ(kIndex2d_[kDimension1_], kIndex1_);
}

TEST_F(IndexSuite, FirstLastBehindAndBefore) {
  SingleIndex_ index_1d_begin;
  ASSERT_NO_THROW(index_1d_begin = index_1d_);
  EXPECT_EQ(SingleIndex_::First({kLength10_}), index_1d_begin);
  EXPECT_EQ(SingleIndex_::Last({kLength10_}), index_1d_last_);
  EXPECT_EQ(SingleIndex_::Behind({kLength10_}), ++index_1d_last_);
  EXPECT_EQ(SingleIndex_::Before({kLength10_}), --index_1d_begin);

  DoubleIndex_ index_2d_begin, index_2d_last;
  ASSERT_NO_THROW(index_2d_begin = DoubleIndex_(kLength2d_));
  ASSERT_NO_THROW(index_2d_last = DoubleIndex_(kLength2d_, {kIndex2_, kIndex3_}));
  EXPECT_EQ(DoubleIndex_::First(kLength2d_), index_2d_begin);
  EXPECT_EQ(DoubleIndex_::Last(kLength2d_), index_2d_last);
  EXPECT_EQ(DoubleIndex_::Behind(kLength2d_), ++index_2d_last);
  EXPECT_EQ(DoubleIndex_::Before(kLength2d_), --index_2d_begin);
}

TEST_F(IndexSuite, GetTotalNumberOfIndicesDependingOnDetermineStride) {
  EXPECT_EQ(index_1d_.GetTotalNumberOfIndices(), 10);

  EXPECT_EQ(index_3d_.GetTotalNumberOfIndices(), 25);
}

TEST_F(IndexSuite, GetIndex) {
  EXPECT_EQ(index_1d_.GetIndex(), (SingleIndexValue_{kIndex0_}));

  EXPECT_EQ(index_3d_.GetIndex(), (TripleIndexValue_{kIndex4_, kIndex4_, kIndex0_}));
}

TEST_F(IndexSuite, GetIndex1dDependingOnDetermineStride) {
  EXPECT_EQ(index_1d_.GetIndex1d(), kIndex0_);

  EXPECT_EQ(index_3d_.GetIndex1d(), Index_{24});
}

#ifndef NDEBUG
TEST_F(IndexSuite, ThrowIfValueIsInvalid) {
  constexpr TripleIndexValue_ const kValue3d{kIndex0_, kIndex0_, kIndex1_};

  EXPECT_THROW(DoubleIndex_(kLength2d_, {kIndex3_, kIndex3_}), OutOfRange);
  EXPECT_THROW(TripleIndex_(index_3d_) += kValue3d, OutOfRange);
  EXPECT_THROW(index_3d_ + kValue3d, OutOfRange);
  EXPECT_THROW(TripleIndex_(index_3d_) -= kValue3d, DomainError);
  EXPECT_THROW(index_3d_ - kValue3d, DomainError);
}

TEST_F(IndexSuite, ThrowIfDimensionIsInvalid) {
  constexpr Dimension const kDimension2{2};

  EXPECT_THROW(kIndex2d_[kDimension2], OutOfRange);
  EXPECT_THROW(index_1d_.Increment(kDimension2), OutOfRange);
  EXPECT_THROW(index_1d_.Decrement(kDimension2), OutOfRange);
}
#endif
}  // namespace splinelib::tests::utilities
