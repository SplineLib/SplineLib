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
#include "Sources/Models/rectangular.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Tests/Splines/b_spline_mock.hpp"
#include "Tests/Splines/nurbs_mock.hpp"

namespace splinelib::tests::models {

using namespace sources::models::rectangular;  // NOLINT(build/namespaces)

TEST(RectangularSuite, Generate) {
  using testing::StrictMock;

  constexpr Degree const kDegreeOne{1}, kDegreeTwo{2};
  constexpr Length const kLengthOne{1};

  StrictMock<splines::A2d3dBSplineMock> square_b_spline;
  square_b_spline.SquareUnitSecondOrderMaximallySmooth();
  EXPECT_EQ((Generate<2, 3, false>({Length{2}, kLengthOne}, {kDegreeTwo, kDegreeTwo})), square_b_spline);
  StrictMock<splines::A2d3dNurbsMock> square_nurbs;
  square_nurbs.SquareUnitFirstOrderBezier();
  EXPECT_EQ((Generate<2, 3, true>({kLengthOne, kLengthOne}, {kDegreeOne, kDegreeOne})), square_nurbs);
}

}  // namespace splinelib::tests::models

