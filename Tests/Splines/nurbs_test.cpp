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
#include "Sources/Splines/nurbs.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Tests/ParameterSpaces/parameter_space_mock.hpp"
#include "Tests/Splines/b_spline_mock.hpp"
#include "Tests/Splines/nurbs_2d_to_3d.hpp"
#include "Tests/VectorSpaces/weighted_vector_space_mock.hpp"

namespace splinelib::tests::splines {

using sources::splines::Nurbs;
using std::make_shared;

// Test NURBS from NURBS book Exe. 4.4.
class NurbsSuite : public testing::Test {
 private:
  template<typename Type>
  using StrictMock_ = testing::StrictMock<Type>;

 protected:
  using BSpline_ = StrictMock_<A2d4dBSplineMock>;
  using Nurbs_ = Nurbs<2, 3>;
  using ParameterSpace_ = StrictMock_<parameter_spaces::A2dParameterSpaceMock>;
  using ParametricCoordinate_ = Nurbs_::ParametricCoordinate_;
  using WeightedVectorSpace_ = StrictMock_<vector_spaces::A3dWeightedVectorSpaceMock>;
  using Coordinate_ = Nurbs_::Coordinate_;

  constexpr static Coordinate const kCoordinate0_0_{0.0}, kCoordinate1_0_{1.0};
  constexpr static Dimension const kDimension0_{};
  constexpr static Nurbs_::Knot_ const kKnot0_5_{0.5};
  constexpr static sources::splines::Tolerance const &kEpsilon_ = sources::splines::kEpsilon;
  constexpr static ParametricCoordinate const kParametricCoordinate0_0_{0.0}, kParametricCoordinate0_5_{0.5};
  constexpr static ParametricCoordinate_ const kParametricCoordinate_{kParametricCoordinate0_5_,
                                                                      kParametricCoordinate0_5_};

  NurbsSuite();

  SharedPointer<ParameterSpace_> parameter_space_{make_shared<ParameterSpace_>()};
  SharedPointer<WeightedVectorSpace_> weighted_vector_space_{make_shared<WeightedVectorSpace_>()};
  SharedPointer<BSpline_> homogeneous_b_spline_{make_shared<BSpline_>()};
  Nurbs2dTo3d nurbs_, non_rational_nurbs_;
  StrictMock_<A2d3dBSplineMock> b_spline_;
};

NurbsSuite::NurbsSuite() {
  using std::move;

  parameter_space_->NurbsBookExe4_4();
  weighted_vector_space_->NurbsBookExe4_4();
  homogeneous_b_spline_->NurbsBookExe4_4();
  nurbs_ = Nurbs2dTo3d{parameter_space_, weighted_vector_space_, homogeneous_b_spline_};
  SharedPointer<WeightedVectorSpace_> non_rational_weighted_vector_space{make_shared<WeightedVectorSpace_>()};
  non_rational_weighted_vector_space->NurbsBookExe4_4BSpline();
  SharedPointer<BSpline_> non_rational_homogeneous_b_spline{make_shared<BSpline_>()};
  non_rational_homogeneous_b_spline->NurbsBookExe4_4BSpline();
  non_rational_nurbs_ = Nurbs2dTo3d{parameter_space_, move(non_rational_weighted_vector_space),
                                    move(non_rational_homogeneous_b_spline)};
  b_spline_.NurbsBookExe4_4();
}

TEST_F(NurbsSuite, CopyConstructAndAssign) {
  ASSERT_NO_THROW(Nurbs_ nurbs_copy_constructed(nurbs_));

  Nurbs_ nurbs_copy_assigned;
  EXPECT_NO_THROW(nurbs_copy_assigned = nurbs_);
}

TEST_F(NurbsSuite, IsEqualAndOperatorEqual) {
  Nurbs_ nurbs;
  ASSERT_NO_THROW(nurbs = Nurbs_(parameter_space_, weighted_vector_space_));
  EXPECT_TRUE(IsEqual(nurbs, nurbs_));
  EXPECT_TRUE(nurbs == nurbs_);

  SharedPointer<WeightedVectorSpace_> weighted_vector_space{make_shared<WeightedVectorSpace_>()};
  weighted_vector_space->NurbsBookExe4_4Perturbed();
  Nurbs_ nurbs_weighted_vector_space;
  ASSERT_NO_THROW(nurbs_weighted_vector_space = Nurbs_(parameter_space_, weighted_vector_space));
  EXPECT_FALSE(IsEqual(nurbs_weighted_vector_space, nurbs_));
  EXPECT_FALSE(nurbs_weighted_vector_space == nurbs_);
  EXPECT_TRUE(IsEqual(nurbs_weighted_vector_space, nurbs_, 1.2 * kEpsilon_));
}

TEST_F(NurbsSuite, Evaluate) {
  constexpr Coordinate const kCoordinate2_0{2.0}, kCoordinate3_0{3.0};
  constexpr ParametricCoordinate const kParametricCoordinate1_0{1.0};

  // See NURBS book P4.23.
  EXPECT_EQ(nurbs_({kParametricCoordinate1_0, kParametricCoordinate0_0_}), (Coordinate_{kCoordinate0_0_,
                                                                                kCoordinate1_0_, kCoordinate3_0}));
  EXPECT_EQ(nurbs_({kParametricCoordinate0_0_, kParametricCoordinate1_0}), (Coordinate_{kCoordinate2_0, kCoordinate1_0_,
                                                                                        kCoordinate1_0_}));
  EXPECT_EQ(nurbs_({kParametricCoordinate1_0, kParametricCoordinate1_0}), (Coordinate_{kCoordinate2_0, kCoordinate0_0_,
                                                                                       kCoordinate3_0}));
  // Compare NURBS book Exe. 4.6.
  EXPECT_EQ(nurbs_(kParametricCoordinate_), (Coordinate_{Coordinate{0.8}, Coordinate{0.4}, Coordinate{1.8}}));
  EXPECT_EQ(non_rational_nurbs_(kParametricCoordinate_), b_spline_(kParametricCoordinate_));
}

TEST_F(NurbsSuite, EvaluateDerivative) {
  using Derivative = Nurbs_::Derivative_;

  constexpr Coordinate const kCoordinateMinus2_78528{-2.78528}, kCoordinateMinus2_2528{-2.2528},
      kCoordinateMinus1_6384{-1.6384}, kCoordinateMinus0_2048{-0.2048}, kCoordinate0_16{0.16}, kCoordinate0_128{0.128},
          kCoordinate0_256{0.256}, kCoordinate0_32{0.32}, kCoordinate0_5{0.5}, kCoordinate1_536{1.536},
              kCoordinate1_92{1.92};
  constexpr splinelib::Derivative const kDerivative0{}, kDerivative1{1}, kDerivative2{2};
  constexpr Derivative const kDerivative1_0{kDerivative1, kDerivative0}, kDerivative0_1{kDerivative0, kDerivative1},
                             kDerivative1_1{kDerivative1, kDerivative1}, kDerivative2_2{kDerivative2, kDerivative2};
  constexpr ParametricCoordinate_ const kParametricCoordinate0{kParametricCoordinate0_0_, kParametricCoordinate0_0_};

  // See NURBS book Eqs. (4.24–4.26), (4.22–4.23), & (4.20).
  EXPECT_EQ(nurbs_(kParametricCoordinate_, Derivative{kDerivative0, kDerivative0}), nurbs_(kParametricCoordinate_));
  EXPECT_EQ(nurbs_(kParametricCoordinate0, kDerivative1_0), (Coordinate_{kCoordinate0_0_, kCoordinate0_5,
                                                                         kCoordinate1_0_}));
  EXPECT_EQ(nurbs_(kParametricCoordinate0, kDerivative0_1), (Coordinate_{kCoordinate1_0_, kCoordinate0_5,
                                                                         kCoordinate0_0_}));
  EXPECT_EQ(nurbs_(kParametricCoordinate0, kDerivative1_1), (Coordinate_{kCoordinate0_5, Coordinate{-0.5},
                                                                         kCoordinate0_5}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, kDerivative1_0), (Coordinate_{kCoordinate0_32, kCoordinate0_16,
                                                                         kCoordinate1_92}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, Derivative{kDerivative2, kDerivative0}),
            (Coordinate_{kCoordinate0_256, kCoordinate0_128, kCoordinate1_536}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, kDerivative0_1), (Coordinate_{kCoordinate1_92, kCoordinate0_16,
                                                                         kCoordinate0_32}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, kDerivative1_1), (Coordinate_{kCoordinate0_256, Coordinate{-1.792},
                                                                         kCoordinate0_256}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, Derivative{kDerivative2, kDerivative1}),
            (Coordinate_{kCoordinateMinus0_2048, kCoordinateMinus1_6384, kCoordinateMinus2_2528}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, Derivative{kDerivative0, kDerivative2}),
            (Coordinate_{kCoordinate1_536, kCoordinate0_128, kCoordinate0_256}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, Derivative{kDerivative1, kDerivative2}),
            (Coordinate_{kCoordinateMinus2_2528, kCoordinateMinus1_6384, kCoordinateMinus0_2048}));
  EXPECT_EQ(nurbs_(kParametricCoordinate_, kDerivative2_2), (Coordinate_{kCoordinateMinus2_78528, Coordinate{3.11296},
                                                                         kCoordinateMinus2_78528}));
  EXPECT_EQ(non_rational_nurbs_(kParametricCoordinate_, kDerivative1_1), b_spline_(kParametricCoordinate_,
                                                                                   kDerivative1_1));
  EXPECT_EQ(non_rational_nurbs_(kParametricCoordinate_, kDerivative2_2), b_spline_(kParametricCoordinate_,
                                                                                   kDerivative2_2));
}

TEST_F(NurbsSuite, InsertKnot) {
  EXPECT_NO_THROW(nurbs_.InsertKnot(kDimension0_, kKnot0_5_));
}

TEST_F(NurbsSuite, RemoveKnot) {
  EXPECT_EQ(nurbs_.RemoveKnot(kDimension0_, kKnot0_5_, kEpsilon_), Multiplicity{});
}

TEST_F(NurbsSuite, ElevateDegree) {
  EXPECT_NO_THROW(nurbs_.ElevateDegree(kDimension0_));
}

TEST_F(NurbsSuite, ReduceDegree) {
  EXPECT_FALSE(nurbs_.ReduceDegree(kDimension0_, kEpsilon_));
}

TEST_F(NurbsSuite, ComputeUpperBoundForMaximumDistanceFromOrigin) {
  EXPECT_TRUE(IsEqual(nurbs_.ComputeUpperBoundForMaximumDistanceFromOrigin(),
                      std::get<0>(weighted_vector_space_->DetermineMaximumDistanceFromOriginAndMinimumWeight())));
}

TEST_F(NurbsSuite, Write) {
  EXPECT_EQ(nurbs_.Write(), (Nurbs_::OutputInformation_{parameter_space_->Write(),
                                                        weighted_vector_space_->WriteProjected()}));
}

#ifndef NDEBUG
TEST_F(NurbsSuite, ThrowIfNotParameterSpaceAndVectorSpaceDoNotMatch) {
  SharedPointer<ParameterSpace_> parameter_space{make_shared<ParameterSpace_>()};
  parameter_space->NurbsBookExe3_8();
  EXPECT_THROW(Nurbs_(parameter_space, weighted_vector_space_), DomainError);
}

TEST_F(NurbsSuite, ThrowIfNotDimensionIsInvalid) {
  constexpr Dimension const kDimension2{2};

  EXPECT_THROW(nurbs_.InsertKnot(kDimension2, kKnot0_5_), OutOfRange);
  EXPECT_THROW(nurbs_.RemoveKnot(kDimension2, kKnot0_5_, kEpsilon_), OutOfRange);
  EXPECT_THROW(nurbs_.ElevateDegree(kDimension2), OutOfRange);
  EXPECT_THROW(nurbs_.ReduceDegree(kDimension2, kEpsilon_), OutOfRange);
}

TEST_F(NurbsSuite, ThrowIfParametricCoordinateIsOutsideScope) {
  EXPECT_THROW(nurbs_.InsertKnot(kDimension0_, ParametricCoordinate{-0.5}), OutOfRange);
}
#endif
}  // namespace splinelib::tests::splines
