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

namespace splinelib::tests::utilities::error_handling {

using namespace sources::utilities::error_handling;  // NOLINT(build/namespaces)

TEST(ErrorHandlingSuite, DependentFalse) {
  EXPECT_FALSE(is_false<void>);
}

#ifndef NDEBUG
TEST(ErrorHandlingSuite, Throw) {
  constexpr char const * const kWhat{"Name: Throws the following —> what"};
  Message const kExcept{"what"}, kName{"Name"};

  try { Throw(DomainError(kExcept), kName); } catch (DomainError const &exception) {
    EXPECT_STREQ(exception.what(), kWhat);
  }
  try { Throw(InvalidArgument(kExcept), kName); } catch (InvalidArgument const &exception) {
    EXPECT_STREQ(exception.what(), kWhat);
  }
  try { Throw(OutOfRange(kExcept), kName); } catch (OutOfRange const &exception) {
    EXPECT_STREQ(exception.what(), kWhat);
  }
  try { Throw(RuntimeError(kExcept), kName); } catch (RuntimeError const &exception) {
    EXPECT_STREQ(exception.what(), kWhat);
  }

  try { Throw(DomainError(kExcept), kName, 1); } catch (DomainError const &exception) {
    EXPECT_STREQ(exception.what(), "Name: Throws the following —> for dimension 1: what");
  }
  try { Throw(InvalidArgument(kExcept), kName, 2); } catch (InvalidArgument const &exception) {
    EXPECT_STREQ(exception.what(), "Name: Throws the following —> for dimension 2: what");
  }
  try { Throw(OutOfRange(kExcept), kName, 3); } catch (OutOfRange const &exception) {
    EXPECT_STREQ(exception.what(), "Name: Throws the following —> for dimension 3: what");
  }
  try { Throw(RuntimeError(kExcept), kName, 4); } catch (RuntimeError const &exception) {
    EXPECT_STREQ(exception.what(), "Name: Throws the following —> for dimension 4: what");
  }
}
#endif
}  // namespace splinelib::tests::utilities::error_handling
