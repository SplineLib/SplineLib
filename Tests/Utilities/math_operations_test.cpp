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
#include "Sources/Utilities/math_operations.hpp"

namespace splinelib::tests::utilities::math_operations {

using namespace sources::utilities::math_operations;  // NOLINT(build/namespaces)

TEST(MathOperationsSuite, ComputeBinomialCoefficient) {
  EXPECT_EQ(ComputeBinomialCoefficient(4, 0), 1);
  EXPECT_EQ(ComputeBinomialCoefficient(4, 4), 1);
  EXPECT_EQ(ComputeBinomialCoefficient(4, 2), 6);
}

#ifndef NDEBUG
TEST(MathOperationsSuite, ThrowIfGreaterNumberOfElementsInSubsetThanInSetOrNegativeNumberOfElementsEncountered) {
  EXPECT_THROW(ComputeBinomialCoefficient(2, 4), InvalidArgument);
  EXPECT_THROW(ComputeBinomialCoefficient(-1, 2), InvalidArgument);
  EXPECT_THROW(ComputeBinomialCoefficient(4, -1), InvalidArgument);
}
#endif
}  // namespace splinelib::tests::utilities::math_operations
