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
#include "Sources/Splines/b_spline.hpp"
#include "Sources/Splines/nurbs.hpp"
#include "Sources/Splines/spline_item.hpp"
#include "Sources/Utilities/std_container_operations.hpp"

namespace splinelib::tests::splines {

using sources::splines::SplineItem;

// Test B-spline and NURBS from NURBS book Exe. 3.8 and Exe. 4.4, respectively.
class SplineItemSuite : public testing::Test {
 protected:
  template<int parametric_dimensionality, int dimensionality>
  using BSpline_ = sources::splines::BSpline<parametric_dimensionality, dimensionality>;
  template<int parametric_dimensionality, int dimensionality>
  using Nurbs_ = sources::splines::Nurbs<parametric_dimensionality, dimensionality>;
  template<int dimensionality>
  using BSplineSurface_ = BSpline_<2, dimensionality>;
  template<int dimensionality>
  using NurbsSurface_ = Nurbs_<2, dimensionality>;
  using BSplineSurfaceEmbeddedInto3dSpace_ = BSplineSurface_<3>;
  using NurbsSurfaceEmbeddedInto3dSpace_ = NurbsSurface_<3>;

  SplineItemSuite();

  SharedPointer<SplineItem> b_spline_, nurbs_;
};

SplineItemSuite::SplineItemSuite() {
  using std::make_shared;

  b_spline_ = make_shared<BSplineSurfaceEmbeddedInto3dSpace_>();

  nurbs_ = make_shared<NurbsSurfaceEmbeddedInto3dSpace_>();
}

TEST_F(SplineItemSuite, ParametricDimensionalityDimensionalityAndIsRational) {
  EXPECT_EQ(b_spline_->parametric_dimensionality_, 2);
  EXPECT_EQ(b_spline_->dimensionality_, 3);
  EXPECT_FALSE(b_spline_->is_rational_);

  EXPECT_EQ(nurbs_->parametric_dimensionality_, 2);
  EXPECT_EQ(nurbs_->dimensionality_, 3);
  EXPECT_TRUE(nurbs_->is_rational_);
}

TEST_F(SplineItemSuite, IsEqualAndOperatorEqual) {
  BSplineSurfaceEmbeddedInto3dSpace_ const kBspline;
  BSpline_<1, 3> const kBSplineParametricDimensionality;
  BSplineSurface_<2> const kBSplineDimensionality;
  NurbsSurfaceEmbeddedInto3dSpace_ const kNurbs;
  Nurbs_<1, 3> const kNurbsParametricDimensionality;
  NurbsSurface_<2> const kNurbsDimensionality;

  EXPECT_TRUE(IsEqual(*b_spline_, kBspline));
  EXPECT_TRUE(*b_spline_ == kBspline);
  EXPECT_FALSE(IsEqual(*b_spline_, kBSplineParametricDimensionality));
  EXPECT_FALSE(*b_spline_ == kBSplineParametricDimensionality);
  EXPECT_FALSE(IsEqual(*b_spline_, kBSplineDimensionality));
  EXPECT_FALSE(*b_spline_ == kBSplineDimensionality);
  EXPECT_FALSE(IsEqual(*b_spline_, kNurbs));
  EXPECT_FALSE(*b_spline_ == kNurbs);

  EXPECT_TRUE(IsEqual(*nurbs_, kNurbs));
  EXPECT_TRUE(*nurbs_ == kNurbs);
  EXPECT_FALSE(IsEqual(*nurbs_, kNurbsParametricDimensionality));
  EXPECT_FALSE(*nurbs_ == kNurbsParametricDimensionality);
  EXPECT_FALSE(IsEqual(*nurbs_, kNurbsDimensionality));
  EXPECT_FALSE(*nurbs_ == kNurbsDimensionality);
  EXPECT_FALSE(IsEqual(*nurbs_, kBspline));
  EXPECT_FALSE(*nurbs_ == kBspline);
}

}  // namespace splinelib::tests::splines
