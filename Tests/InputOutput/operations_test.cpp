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
#include "Sources/InputOutput/operations.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Tests/InputOutput/config_iges.hpp"
#include "Tests/InputOutput/config_irit.hpp"
#include "Tests/InputOutput/config_xml.hpp"
#include "Tests/Splines/b_spline_mock.hpp"

namespace splinelib::tests::input_output::operations {

using namespace sources::input_output::operations;  // NOLINT(build/namespaces)

TEST(OperationsSuite, DetermineFileFormat) {
  constexpr FileFormat const kIges{FileFormat::kIges};

  EXPECT_EQ(DetermineFileFormat(iges_file_one), kIges);
  EXPECT_EQ(DetermineFileFormat(iges_file_two), kIges);
  EXPECT_EQ(DetermineFileFormat(irit_file), FileFormat::kIrit);
  EXPECT_EQ(DetermineFileFormat("test.vtk"), FileFormat::kVtk);
  EXPECT_EQ(DetermineFileFormat(xml_file), FileFormat::kXml);
}

TEST(OperationsSuite, Read) {
  EXPECT_NO_THROW(Read(iges_file_one));
  EXPECT_NO_THROW(Read(iges_file_two));
  EXPECT_NO_THROW(Read(irit_file));
  EXPECT_NO_THROW(Read(xml_file));
}

TEST(OperationsSuite, CastToSpline) {
  SplineEntry const b_spline_entry{std::make_shared<splines::A2d3dBSplineMock>()};

  EXPECT_TRUE((CastToSpline<2, 3, false>(b_spline_entry)));
  EXPECT_FALSE((CastToSpline<1, 3, false>(b_spline_entry)));
  EXPECT_FALSE((CastToSpline<2, 2, false>(b_spline_entry)));
  EXPECT_FALSE((CastToSpline<2, 3, true>(b_spline_entry)));
}

TEST(OperationsSuite, WriteCoordinate3d) {
  EXPECT_EQ(WriteCoordinate3d(StringArray<1>{"1"}, " "), "1 0 0");
  EXPECT_EQ(WriteCoordinate3d(StringArray<4>{"1", "2", "3", "4"}, " "), "1 2 3");
}

#ifndef NDEBUG
TEST(OperationsSuite, ThrowIfFileFormatNotSupported) {
  EXPECT_THROW(Read("test"), RuntimeError);
  EXPECT_THROW(Read("test.vtk"), RuntimeError);
  EXPECT_THROW(Read("test.invalid"), RuntimeError);
}
#endif
}  // namespace splinelib::tests::input_output::operations
