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
#include "Sources/InputOutput/xml.hpp"
#include "Sources/Splines/b_spline.hpp"
#include "Sources/Splines/nurbs.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Tests/InputOutput/config_irit.hpp"
#include "Tests/InputOutput/config_xml.hpp"

namespace splinelib::tests::input_output::xml {

using namespace sources::input_output::xml;  // NOLINT(build/namespaces)
using std::dynamic_pointer_cast;

class XmlSuite : public testing::Test {
 protected:
  template<int parametric_dimensionality, int dimensionality>
  using BSpline_ = sources::splines::BSpline<parametric_dimensionality, dimensionality>;
  template<int parametric_dimensionality, int dimensionality>
  using Nurbs_ = sources::splines::Nurbs<parametric_dimensionality, dimensionality>;
  using BSplineSurface_ = BSpline_<2, 3>;
  using NurbsSurface_ = Nurbs_<2, 3>;
  using BSplineSpaceTime_ = BSpline_<4, 4>;
  using NurbsSpaceTime_ = Nurbs_<4, 4>;
  using Splines_ = sources::input_output::Splines;
  using SplineConstIterator_ = Splines_::const_iterator;

  Splines_ const kSplines_{Read(xml_file)};
  SplineConstIterator_ spline_{kSplines_.begin()};
};

TEST_F(XmlSuite, Read) {
  EXPECT_TRUE(dynamic_pointer_cast<NurbsSurface_>(*(spline_++)));
  EXPECT_TRUE(dynamic_pointer_cast<BSplineSurface_>(*(spline_++)));
  EXPECT_TRUE(dynamic_pointer_cast<BSplineSpaceTime_>(*(spline_++)));
  EXPECT_TRUE(dynamic_pointer_cast<NurbsSpaceTime_>(*spline_));
}

TEST_F(XmlSuite, Write) {
  using std::static_pointer_cast;

  String const kFilename{"test.xml"};

  EXPECT_NO_THROW(Write({static_pointer_cast<NurbsSurface_>(*(spline_++)),
      static_pointer_cast<BSplineSurface_>(*(spline_++)), static_pointer_cast<BSplineSpaceTime_>(*(spline_++)),
          static_pointer_cast<NurbsSpaceTime_>(*spline_)}, kFilename));
  Splines_ splines_written;
  ASSERT_NO_THROW(splines_written = Read(kFilename));
  SplineConstIterator_ spline_written;
  ASSERT_NO_THROW(spline_written = splines_written.begin());
  EXPECT_TRUE(dynamic_pointer_cast<NurbsSurface_>(*(spline_written++)));
  EXPECT_TRUE(dynamic_pointer_cast<BSplineSurface_>(*(spline_written++)));
  EXPECT_TRUE(dynamic_pointer_cast<BSplineSpaceTime_>(*(spline_written++)));
  EXPECT_TRUE(dynamic_pointer_cast<NurbsSpaceTime_>(*spline_written));
  remove(kFilename.c_str());
}

#ifndef NDEBUG
TEST_F(XmlSuite, ThrowIfXmlCannotBeParsed) {
  EXPECT_THROW(Read(irit_file), RuntimeError);
}
#endif
}  // namespace splinelib::tests::input_output::xml
