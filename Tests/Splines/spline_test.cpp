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

#include <utility>

#include <gtest/gtest.h>
#include "Sources/Splines/spline.hpp"
#include "Sources/Splines/b_spline.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/std_container_operations.hpp"
#include "Tests/ParameterSpaces/parameter_space_mock.hpp"
#include "Tests/Splines/b_spline_mock.hpp"
#include "Tests/Splines/nurbs_2d_to_3d.hpp"
#include "Tests/VectorSpaces/vector_space_mock.hpp"
#include "Tests/VectorSpaces/weighted_vector_space_mock.hpp"

namespace splinelib::tests::splines {

using sources::splines::Spline;
using std::make_shared, std::move;

// Test B-spline and NURBS from NURBS book Exe. 3.8 and Exe. 4.4, respectively.
class SplineSuite : public testing::Test {
 private:
  template<typename Type>
  using StrictMock_ = testing::StrictMock<Type>;

 protected:
  using BSpline_ = sources::splines::BSpline<2, 3>;
  using HomogeneousBSpline_ = StrictMock_<A2d4dBSplineMock>;
  using ParameterSpace_ = StrictMock_<parameter_spaces::A2dParameterSpaceMock>;
  using Spline_ = Spline<2, 3>;
  using Tolerance_ = sources::splines::Tolerance;
  using VectorSpace_ = StrictMock_<vector_spaces::A3dVectorSpaceMock>;
  using WeightedVectorSpace_ = StrictMock_<vector_spaces::A3dWeightedVectorSpaceMock>;

  constexpr static Dimension const kDimension0_{}, kDimension1_{1};
  constexpr static Spline_::Knot_ const kKnot0_5_{0.5};
  constexpr static Tolerance_ const &kEpsilon_ = sources::splines::kEpsilon;
  inline static Spline_::Knots_ const kKnots_{kKnot0_5_, kKnot0_5_};

  SplineSuite();

  SharedPointer<ParameterSpace_> parameter_space_b_spline_{make_shared<ParameterSpace_>()},
                                 parameter_space_nurbs_{make_shared<ParameterSpace_>()};
  SharedPointer<VectorSpace_> vector_space_{make_shared<VectorSpace_>()};
  SharedPointer<WeightedVectorSpace_> weighted_vector_space_{make_shared<WeightedVectorSpace_>()};
  SharedPointer<HomogeneousBSpline_> homogeneous_b_spline_{make_shared<HomogeneousBSpline_>()};
  SharedPointer<Spline_> b_spline_, nurbs_;
};

SplineSuite::SplineSuite() {
  parameter_space_b_spline_->NurbsBookExe3_8();
  vector_space_->NurbsBookExe3_8();
  b_spline_ = make_shared<BSpline_>(parameter_space_b_spline_, vector_space_);

  parameter_space_nurbs_->NurbsBookExe4_4();
  weighted_vector_space_->NurbsBookExe4_4();
  homogeneous_b_spline_->NurbsBookExe4_4();
  nurbs_ = make_shared<Nurbs2dTo3d>(parameter_space_nurbs_, weighted_vector_space_, homogeneous_b_spline_);
}

TEST_F(SplineSuite, IsEqualAndOperatorEqual) {
  constexpr Tolerance_ const kTolerance{1.2 * kEpsilon_};

  SharedPointer<Spline_> b_spline;
  ASSERT_NO_THROW(b_spline = make_shared<BSpline_>(parameter_space_b_spline_, vector_space_));
  SharedPointer<ParameterSpace_> parameter_space_b_spline_knot_vector{make_shared<ParameterSpace_>()};
  parameter_space_b_spline_knot_vector->NurbsBookExe3_8KnotVector();
  SharedPointer<Spline_> b_spline_knot_vector;
  ASSERT_NO_THROW(b_spline_knot_vector = make_shared<BSpline_>(parameter_space_b_spline_knot_vector, vector_space_));
  EXPECT_TRUE(IsEqual(*b_spline, *b_spline_));
  EXPECT_TRUE(*b_spline == *b_spline_);
  EXPECT_FALSE(IsEqual(*b_spline_knot_vector, *b_spline_));
  EXPECT_FALSE(*b_spline_knot_vector == *b_spline_);
  EXPECT_TRUE(IsEqual(*b_spline_knot_vector, *b_spline_, kTolerance));

  SharedPointer<Spline_> nurbs;
  ASSERT_NO_THROW(nurbs = make_shared<Nurbs2dTo3d>(parameter_space_nurbs_, weighted_vector_space_,
                                                   homogeneous_b_spline_));
  SharedPointer<ParameterSpace_> parameter_space_nurbs_knot_vector{make_shared<ParameterSpace_>()};
  parameter_space_nurbs_knot_vector->NurbsBookExe4_4KnotVector();
  SharedPointer<HomogeneousBSpline_> homogeneous_b_spline_knot_vector{make_shared<HomogeneousBSpline_>()};
  homogeneous_b_spline_knot_vector->NurbsBookExe4_4KnotVector();
  SharedPointer<Spline_> nurbs_knot_vector;
  ASSERT_NO_THROW(nurbs_knot_vector = make_shared<Nurbs2dTo3d>(parameter_space_nurbs_knot_vector,
                                          weighted_vector_space_, homogeneous_b_spline_knot_vector));
  EXPECT_TRUE(IsEqual(*nurbs, *nurbs_));
  EXPECT_TRUE(*nurbs == *nurbs_);
  EXPECT_FALSE(IsEqual(*nurbs_knot_vector, *nurbs_));
  EXPECT_FALSE(*nurbs_knot_vector == *nurbs_);
  EXPECT_TRUE(IsEqual(*nurbs_knot_vector, *nurbs_, kTolerance));
}

TEST_F(SplineSuite, RefineKnots) {
  SharedPointer<ParameterSpace_> parameter_space{make_shared<ParameterSpace_>()};
  parameter_space->NurbsBookExe3_8();
  SharedPointer<VectorSpace_> vector_space{make_shared<VectorSpace_>()};
  vector_space->NurbsBookExe3_8Insert();
  SharedPointer<Spline_> b_spline;
  ASSERT_NO_THROW(b_spline = make_shared<BSpline_>(move(parameter_space), move(vector_space)));
  EXPECT_NO_THROW(b_spline->RefineKnots(kDimension1_, kKnots_));

  EXPECT_NO_THROW(nurbs_->RefineKnots(kDimension0_, {kKnot0_5_}));
}

TEST_F(SplineSuite, CoarsenKnots) {
  SharedPointer<ParameterSpace_> parameter_space{make_shared<ParameterSpace_>()};
  parameter_space->NurbsBookExe3_8Subdivided();
  SharedPointer<VectorSpace_> vector_space{make_shared<VectorSpace_>()};
  vector_space->NurbsBookExe3_8Remove();
  SharedPointer<Spline_> b_spline;
  ASSERT_NO_THROW(b_spline = make_shared<BSpline_>(move(parameter_space), move(vector_space)));
  EXPECT_EQ(b_spline->CoarsenKnots(kDimension1_, kKnots_, kEpsilon_), sources::splines::kMultiplicity);

  EXPECT_EQ(nurbs_->CoarsenKnots(kDimension0_, {kKnot0_5_}, kEpsilon_), Multiplicity{});
}

TEST_F(SplineSuite, Sample) {
  using Coordinates = Spline_::Coordinates_;

  constexpr Coordinate const kCoordinate0_0{}, kCoordinate1_0{1.0}, kCoordinate2_0{2.0}, kCoordinate3_0{3.0},
                             kCoordinate4_0{4.0}, kCoordinate9_0{9.0};
  constexpr Length const kLength{2};
  Spline_::NumberOfParametricCoordinates_ const kNumberOfParametricCoordinates{kLength, kLength};

  EXPECT_EQ(b_spline_->Sample(kNumberOfParametricCoordinates), (Coordinates{{kCoordinate0_0, kCoordinate0_0,
                kCoordinate0_0}, {kCoordinate9_0, kCoordinate0_0, kCoordinate0_0}, {kCoordinate0_0, kCoordinate4_0,
                    kCoordinate0_0}, {kCoordinate9_0, kCoordinate4_0, kCoordinate0_0}}));
  EXPECT_EQ(nurbs_->Sample(kNumberOfParametricCoordinates), (Coordinates{{kCoordinate0_0, kCoordinate0_0,
                kCoordinate1_0}, {kCoordinate0_0, kCoordinate1_0, kCoordinate3_0}, {kCoordinate2_0, kCoordinate1_0,
                    kCoordinate1_0}, {kCoordinate2_0, kCoordinate0_0, kCoordinate3_0}}));
}

}  // namespace splinelib::tests::splines
