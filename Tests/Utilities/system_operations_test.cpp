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
#include "Sources/Utilities/system_operations.hpp"

namespace splinelib::tests::utilities::system_operations {

using namespace sources::utilities::system_operations;  // NOLINT(build/namespaces)

class SystemOperationsSuite : public testing::Test {
 protected:
  File const file_name{"file.test"};
};

TEST_F(SystemOperationsSuite, GetLocalTime) {
  EXPECT_NO_THROW(GetLocalTime());
}

TEST_F(SystemOperationsSuite, Open) {
  EXPECT_TRUE((Open<OutputStream, kModeOut>(file_name).is_open()));
  EXPECT_TRUE((Open<OutputStream, kModeAppend>(file_name).is_open()));
  EXPECT_TRUE((Open<InputStream, kModeIn>(file_name).is_open()));
  remove(file_name.c_str());
}

#ifndef NDEBUG
TEST_F(SystemOperationsSuite, ThrowIfFileCannotBeOpened) {
  EXPECT_THROW((Open<InputStream, kModeIn>(file_name)), RuntimeError);
}
#endif
}  // namespace splinelib::tests::utilities::system_operations
