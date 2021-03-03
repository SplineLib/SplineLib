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
#include "Sources/Utilities/numeric_operations.hpp"

namespace splinelib::tests::utilities::numeric_operations {

using namespace sources::utilities::numeric_operations;  // NOLINT(build/namespaces)

TEST(NumericOperationsSuite, GetMachineEpsilonForNumericTypes) {
  EXPECT_NO_THROW(GetEpsilon<double>());
  // Invoked by comparison operators of NamedType<Name, int>; should not be called by users (not meaningful)!
  EXPECT_NO_THROW(GetEpsilon<int>());
}

TEST(NumericOperationsSuite, GetNumberOfBase10Digits) {
  EXPECT_EQ(GetPrecision<double>(), 15);
}

TEST(NumericOperationsSuite, IsEqualIsLess) {
  EXPECT_FALSE(IsEqual(0.0, -3e-14));
  EXPECT_TRUE(IsEqual(0.0, -3e-14, 3e-14));
  EXPECT_TRUE(IsEqual(0.0, -2e-14));
  EXPECT_TRUE(IsEqual(0.0, 0.0));
  EXPECT_TRUE(IsEqual(0.0, 2e-14));
  EXPECT_FALSE(IsEqual(0.0, 3e-14));
  EXPECT_TRUE(IsEqual(0.0, 3e-14, 3e-14));

  EXPECT_FALSE(IsLess(0.0, -3e-14));
  EXPECT_FALSE(IsLess(0.0, 2e-14));
  EXPECT_TRUE(IsLess(0.0, 3e-14));
  EXPECT_FALSE(IsLess(0.0, 3e-14, 3e-14));
}

#ifndef NDEBUG
TEST(NumericOperationsSuite, ThrowsIfToleranceHasNegativeSign) {
  EXPECT_THROW(IsEqual(0.0, 0.0, -3e-14), InvalidArgument);
  EXPECT_THROW(IsLess(0.0, 0.0, -3e-14), InvalidArgument);
}
#endif
}  // namespace splinelib::tests::utilities::numeric_operations
