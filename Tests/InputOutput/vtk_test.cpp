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
#include "Sources/InputOutput/vtk.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/std_container_operations.hpp"
#include "Tests/Splines/b_spline_mock.hpp"

namespace splinelib::tests::input_output {

using namespace sources::input_output::vtk;  // NOLINT(build/namespaces)

class VtkSuite : public testing::Test {
 private:
  using BSpline_ = splines::A2d3dBSplineMock;

 protected:
  constexpr static NumbersOfParametricCoordinates::value_type::value_type const k3_{3};
  inline static sources::utilities::string_operations::String const kFilename_{"test.vtk"};

  VtkSuite();

  SharedPointer<BSpline_> b_spline_{std::make_shared<BSpline_>()};
};

VtkSuite::VtkSuite() {
  b_spline_->NurbsBookExe4_4();
}

TEST_F(VtkSuite, Write) {
  EXPECT_NO_THROW(Sample({b_spline_}, kFilename_, {{k3_, k3_}}));
  remove(kFilename_.c_str());
}

#ifndef NDEBUG
TEST_F(VtkSuite, ThrowIfNumbersOfParametricCoordinatesIsInvalid) {
  EXPECT_THROW(Sample({b_spline_}, kFilename_, {}), RuntimeError);
  EXPECT_THROW(Sample({b_spline_}, kFilename_, {{k3_}}), RuntimeError);
}

TEST_F(VtkSuite, ThrowIfDimensionanlityIsGreaterThanThree) {
  using BSpline = splines::A2d4dBSplineMock;

  SharedPointer<BSpline> b_spline{std::make_shared<BSpline>()};
  b_spline->NurbsBookExe4_4();

  EXPECT_THROW(Sample({b_spline}, kFilename_, {{k3_, k3_}}), RuntimeError);
  remove(kFilename_.c_str());
}
#endif
}  // namespace splinelib::tests::input_output
