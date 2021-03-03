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

#include "Tests/Utilities/index_mock.hpp"

namespace splinelib::tests::utilities {

using ScalarIndex = A2dIndexMock::Index_;
using testing::ReturnRef, testing::ReturnRefOfCopy;

constexpr Dimension const kDimension0{}, kDimension1{1};
constexpr ScalarIndex const kIndex1{1};

ScalarIndex const & A2dIndexMock::operator[](Dimension const &dimension) const {
  return OperatorSubscript(dimension);
}

void A2dIndexMock::NurbsBookExa2_2_1_0() {
  constexpr ScalarIndex const kIndex0{};

  length_ = Length_{Length{8}, Length{3}};
  value_ = Value_{kIndex1, kIndex0};
  invalid_ = false;

  EXPECT_CALL(*this, OperatorSubscript(kDimension0)).WillRepeatedly(ReturnRef(kIndex1));
  EXPECT_CALL(*this, OperatorSubscript(kDimension1)).WillRepeatedly(ReturnRefOfCopy(kIndex0));
}

#ifndef NDEBUG
void A2dIndexMock::NurbsBookExa2_2_1_3() {
  EXPECT_CALL(*this, OperatorSubscript(kDimension0)).WillRepeatedly(ReturnRef(kIndex1));
  EXPECT_CALL(*this, OperatorSubscript(kDimension1)).WillRepeatedly(ReturnRefOfCopy(ScalarIndex{3}));
}
#endif

}  // namespace splinelib::tests::utilities
