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
#include "Sources/Splines/b_spline.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Tests/ParameterSpaces/knot_vector_mock.hpp"
#include "Tests/ParameterSpaces/parameter_space_mock.hpp"
#include "Tests/VectorSpaces/vector_space_mock.hpp"

namespace splinelib::tests::splines {

using sources::splines::BSpline;
using std::make_shared;

// Test B-spline from NURBS book Exe. 3.8.
class BSplineSuite : public testing::Test {
 private:
  template<typename Type>
  using StrictMock_ = testing::StrictMock<Type>;

 protected:
  using BSpline_ = BSpline<2, 3>;
  using ParameterSpace_ = StrictMock_<parameter_spaces::A2dParameterSpaceMock>;
  using ParametricCoordinate_ = ParameterSpace_::ParametricCoordinate_;
  using VectorSpace_ = StrictMock_<vector_spaces::A3dVectorSpaceMock>;
  using Coordinate_ = VectorSpace_::Coordinate_;

  constexpr static Coordinate const kCoordinate0_0_{0.0}, kCoordinate2_0_{2.0}, kCoordinate4_0_{4.0};
  constexpr static Coordinate_ const kCoordinate8_{kCoordinate0_0_, kCoordinate4_0_, kCoordinate0_0_};
  constexpr static Dimension const kDimension0_{}, kDimension1_{1};
  constexpr static BSpline_::Knot_ const kKnot0_5_{0.5};
  constexpr static Multiplicity const kMultiplicity2_{2};
  constexpr static ParametricCoordinate const kParametricCoordinate0_0_{0.0};
  constexpr static ParametricCoordinate_ const kParametricCoordinate_{ParametricCoordinate{0.75},
                                                                      ParametricCoordinate{0.5}};
  constexpr static sources::splines::Tolerance const &kEpsilon_ = sources::splines::kEpsilon;

  BSplineSuite();

  SharedPointer<ParameterSpace_> parameter_space_{make_shared<ParameterSpace_>()},
                                 parameter_space_insert_remove_{make_shared<ParameterSpace_>()};
  SharedPointer<VectorSpace_> vector_space_{make_shared<VectorSpace_>()};
  BSpline_ b_spline_, b_spline_insert_remove_, b_spline_elevate_reduce_;
};

BSplineSuite::BSplineSuite() {
  using std::move;

  parameter_space_->NurbsBookExe3_8();
  vector_space_->NurbsBookExe3_8();
  b_spline_ = BSpline_{parameter_space_, vector_space_};
  parameter_space_insert_remove_->NurbsBookExe3_8InsertRemove();
  SharedPointer<VectorSpace_> vector_space_insert_remove{make_shared<VectorSpace_>()};
  vector_space_insert_remove->NurbsBookExe3_8InsertRemove();
  b_spline_insert_remove_ = BSpline_{parameter_space_insert_remove_, move(vector_space_insert_remove)};
  SharedPointer<ParameterSpace_> parameter_space_elevate_reduce{make_shared<ParameterSpace_>()};
  parameter_space_elevate_reduce->NurbsBookExe3_8ElevateReduce();
  SharedPointer<VectorSpace_> vector_space_elevate_reduce{make_shared<VectorSpace_>()};
  vector_space_elevate_reduce->NurbsBookExe3_8ElevateReduce();
  b_spline_elevate_reduce_ = BSpline_{move(parameter_space_elevate_reduce), move(vector_space_elevate_reduce)};
}

TEST_F(BSplineSuite, CopyConstructAndCopyAssign) {
  ASSERT_NO_THROW(BSpline_ b_spline_copy_constructed(b_spline_));

  BSpline_ b_spline_copy_assigned;
  EXPECT_NO_THROW(b_spline_copy_assigned = b_spline_);
}

TEST_F(BSplineSuite, IsEqualAndOperatorEqual) {
  BSpline_ b_spline;
  ASSERT_NO_THROW(b_spline = BSpline_(parameter_space_, vector_space_));
  EXPECT_TRUE(IsEqual(b_spline, b_spline_));
  EXPECT_TRUE(b_spline == b_spline_);

  SharedPointer<VectorSpace_> vector_space{make_shared<VectorSpace_>()};
  vector_space->NurbsBookExe3_8Perturbed();
  BSpline_ b_spline_vector_space;
  ASSERT_NO_THROW(b_spline_vector_space = BSpline_(parameter_space_, vector_space));
  EXPECT_FALSE(IsEqual(b_spline_vector_space, b_spline_));
  EXPECT_FALSE(b_spline_vector_space == b_spline_);
  EXPECT_TRUE(IsEqual(b_spline_vector_space, b_spline_, 1.2 * kEpsilon_));
}

// See NURBS book P3.20.
TEST_F(BSplineSuite, Evaluate) {
  constexpr Coordinate const kCoordinate9_0{9.0};
  constexpr ParametricCoordinate const kParametricCoordinate1_0{1.0};

  EXPECT_EQ(b_spline_({kParametricCoordinate1_0, kParametricCoordinate0_0_}),
            (Coordinate_{kCoordinate9_0, kCoordinate0_0_, kCoordinate0_0_}));
  EXPECT_EQ(b_spline_({kParametricCoordinate0_0_, kParametricCoordinate1_0}), kCoordinate8_);
  EXPECT_EQ(b_spline_({kParametricCoordinate1_0, kParametricCoordinate1_0}),
            (Coordinate_{kCoordinate9_0, kCoordinate4_0_, kCoordinate0_0_}));
  EXPECT_EQ(b_spline_(kParametricCoordinate_), (Coordinate_{Coordinate{6.375}, kCoordinate2_0_, Coordinate{3.25}}));
}

// See NURBS book Eq. (3.24).
TEST_F(BSplineSuite, EvaluateDerivative) {
  constexpr Coordinate const kCoordinate12_0{12.0};
  constexpr Derivative const kDerivative0{}, kDerivative1{1};
  constexpr BSpline_::Derivative_ const kDerivative1_0{kDerivative1, kDerivative0},
      kDerivative0_1{kDerivative0, kDerivative1}, kDerivative1_1{kDerivative1, kDerivative1};
  constexpr ParametricCoordinate_ const kParametricCoordinate0{kParametricCoordinate0_0_, kParametricCoordinate0_0_};

  EXPECT_EQ(b_spline_(kParametricCoordinate_, {kDerivative0, kDerivative0}), b_spline_(kParametricCoordinate_));
  EXPECT_EQ(b_spline_(kParametricCoordinate0, kDerivative1_0), (Coordinate_{kCoordinate12_0, kCoordinate0_0_,
                                                                            kCoordinate12_0}));
  EXPECT_EQ(b_spline_(kParametricCoordinate0, kDerivative0_1), (Coordinate_{kCoordinate0_0_, kCoordinate4_0_,
                                                                            kCoordinate4_0_}));
  EXPECT_EQ(b_spline_(kParametricCoordinate0, kDerivative1_1), (Coordinate_{kCoordinate0_0_, kCoordinate0_0_,
                                                                            kCoordinate0_0_}));
  EXPECT_EQ(b_spline_(kParametricCoordinate_, kDerivative1_0), (Coordinate_{Coordinate{15.0}, kCoordinate4_0_,
                                                                            kCoordinate2_0_}));
  EXPECT_EQ(b_spline_(kParametricCoordinate_, kDerivative0_1), kCoordinate8_);
  EXPECT_EQ(b_spline_(kParametricCoordinate_, kDerivative1_1), (Coordinate_{kCoordinate0_0_, Coordinate{8.0},
                                                                            kCoordinate0_0_}));
}

TEST_F(BSplineSuite, InsertKnot) {
  SharedPointer<ParameterSpace_> parameter_space_insert{make_shared<ParameterSpace_>()},
                                 parameter_space_subdivide{make_shared<ParameterSpace_>()},
                                 parameter_space_subdivided{make_shared<ParameterSpace_>()};
  parameter_space_insert->NurbsBookExe3_8();
  parameter_space_subdivide->NurbsBookExe3_8();
  parameter_space_subdivided->NurbsBookExe3_8Subdivided();
  SharedPointer<VectorSpace_> vector_space_insert{make_shared<VectorSpace_>()},
      vector_space_subdivide{make_shared<VectorSpace_>()}, vector_space_subdivided{make_shared<VectorSpace_>()};
  vector_space_insert->NurbsBookExe3_8Insert();
  vector_space_subdivide->NurbsBookExe3_8Insert();
  vector_space_subdivided->NurbsBookExe3_8Subdivided();
  BSpline_ b_spline_insert, b_spline_subdivide;
  ASSERT_NO_THROW(b_spline_insert = BSpline_(parameter_space_insert, vector_space_insert));
  ASSERT_NO_THROW(b_spline_subdivide = BSpline_(parameter_space_subdivide, vector_space_subdivide));
  EXPECT_NO_THROW(b_spline_insert.InsertKnot(kDimension1_, kKnot0_5_));
  EXPECT_EQ(b_spline_insert, b_spline_insert_remove_);
  EXPECT_NO_THROW(b_spline_subdivide.InsertKnot(kDimension1_, kKnot0_5_, kMultiplicity2_));
  EXPECT_EQ(b_spline_subdivide, BSpline_(parameter_space_subdivided, vector_space_subdivided));
  EXPECT_NO_THROW(b_spline_insert.InsertKnot(kDimension1_, kKnot0_5_));
  EXPECT_EQ(b_spline_insert, b_spline_subdivide);
}

TEST_F(BSplineSuite, RemoveKnot) {
  constexpr Multiplicity const kMultiplicity0{0};
  constexpr Multiplicity const &kMultiplicity = sources::splines::kMultiplicity;

  SharedPointer<ParameterSpace_> parameter_space_remove{make_shared<ParameterSpace_>()},
      parameter_space{make_shared<ParameterSpace_>()}, parameter_space_unsuccessful{make_shared<ParameterSpace_>()};
  parameter_space_remove->NurbsBookExe3_8Subdivided();
  parameter_space->NurbsBookExe3_8Subdivided();
  parameter_space_unsuccessful->NurbsBookExe3_8Unsuccessful();
  SharedPointer<VectorSpace_> vector_space_remove{make_shared<VectorSpace_>()},
      vector_space{make_shared<VectorSpace_>()}, vector_space_unsuccessful{make_shared<VectorSpace_>()},
      vector_space_b_spline{make_shared<VectorSpace_>()};
  vector_space_remove->NurbsBookExe3_8Remove();
  vector_space->NurbsBookExe3_8Remove();
  vector_space_unsuccessful->NurbsBookExe3_8Unsuccessful();
  BSpline_ b_spline_remove, b_spline, b_spline_unsuccessful;
  ASSERT_NO_THROW(b_spline_remove = BSpline_(parameter_space_remove, vector_space_remove));
  ASSERT_NO_THROW(b_spline = BSpline_(parameter_space, vector_space));
  ASSERT_NO_THROW(b_spline_unsuccessful = BSpline_(parameter_space_unsuccessful, vector_space_unsuccessful));
  EXPECT_EQ(b_spline_remove.RemoveKnot(kDimension1_, kKnot0_5_, kEpsilon_), kMultiplicity);
  EXPECT_EQ(b_spline_remove, b_spline_insert_remove_);
  EXPECT_EQ(b_spline.RemoveKnot(kDimension1_, kKnot0_5_, kEpsilon_, kMultiplicity2_), kMultiplicity2_);
  EXPECT_EQ(b_spline, b_spline_);
  EXPECT_EQ(b_spline_remove.RemoveKnot(kDimension1_, kKnot0_5_, kEpsilon_), kMultiplicity);
  EXPECT_EQ(b_spline_remove, b_spline_);
  EXPECT_EQ(b_spline_unsuccessful.RemoveKnot(kDimension1_, kKnot0_5_, kEpsilon_), kMultiplicity0);
  EXPECT_EQ(b_spline_unsuccessful, b_spline_insert_remove_);
  EXPECT_EQ(b_spline_remove.RemoveKnot(kDimension1_, kKnot0_5_, kEpsilon_), kMultiplicity0);
  EXPECT_EQ(b_spline_remove, b_spline_);
}

TEST_F(BSplineSuite, ElevateDegreeDependingOnMakeBezierAndMakeBSpline) {
  SharedPointer<ParameterSpace_> parameter_space_elevate_once{make_shared<ParameterSpace_>()},
                                 parameter_space_elevate_twice{make_shared<ParameterSpace_>()},
                                 parameter_space_elevated_twice{make_shared<ParameterSpace_>()};
  parameter_space_elevate_once->NurbsBookExe3_8();
  parameter_space_elevate_twice->NurbsBookExe3_8();
  parameter_space_elevated_twice->NurbsBookExe3_8ElevatedTwice();
  SharedPointer<VectorSpace_> vector_space_elevate_once{make_shared<VectorSpace_>()},
      vector_space_elevate_twice{make_shared<VectorSpace_>()}, vector_space_elevated_twice{make_shared<VectorSpace_>()};
  vector_space_elevate_once->NurbsBookExe3_8ElevateOnce();
  vector_space_elevate_twice->NurbsBookExe3_8ElevateTwice();
  vector_space_elevated_twice->NurbsBookExe3_8ElevatedTwice();
  BSpline_ b_spline_elevate_once, b_spline_elevate_twice;
  ASSERT_NO_THROW(b_spline_elevate_once = BSpline_(parameter_space_elevate_once, vector_space_elevate_once));
  ASSERT_NO_THROW(b_spline_elevate_twice = BSpline_(parameter_space_elevate_twice, vector_space_elevate_twice));
  EXPECT_NO_THROW(b_spline_elevate_once.ElevateDegree(kDimension0_));
  EXPECT_EQ(b_spline_elevate_once, b_spline_elevate_reduce_);
  EXPECT_NO_THROW(b_spline_elevate_twice.ElevateDegree(kDimension0_, kMultiplicity2_));
  EXPECT_EQ(b_spline_elevate_twice, BSpline_(parameter_space_elevated_twice, vector_space_elevated_twice));
  EXPECT_NO_THROW(b_spline_elevate_once.ElevateDegree(kDimension0_));
  EXPECT_EQ(b_spline_elevate_once, b_spline_elevate_twice);
}

TEST_F(BSplineSuite, ReduceDegreeDependingOnMakeBezierAndMakeBSpline) {
  SharedPointer<ParameterSpace_> parameter_space_reduce{make_shared<ParameterSpace_>()},
      parameter_space{make_shared<ParameterSpace_>()}, parameter_space_unsuccessful{make_shared<ParameterSpace_>()};
  parameter_space_reduce->NurbsBookExe3_8ElevatedTwice();
  parameter_space->NurbsBookExe3_8ElevatedTwice();
  parameter_space_unsuccessful->NurbsBookExe3_8();
  SharedPointer<VectorSpace_> vector_space_reduce{make_shared<VectorSpace_>()},
      vector_space{make_shared<VectorSpace_>()}, vector_space_unsuccessful{make_shared<VectorSpace_>()};
  vector_space_reduce->NurbsBookExe3_8ReduceOnce();
  vector_space->NurbsBookExe3_8ReduceTwice();
  vector_space_unsuccessful->NurbsBookExe3_8();
  BSpline_ b_spline_reduce, b_spline, b_spline_unsuccessful;
  ASSERT_NO_THROW(b_spline_reduce = BSpline_(parameter_space_reduce, vector_space_reduce));
  ASSERT_NO_THROW(b_spline = BSpline_(parameter_space, vector_space));
  ASSERT_NO_THROW(b_spline_unsuccessful = BSpline_(parameter_space_unsuccessful, vector_space_unsuccessful));
  EXPECT_TRUE(b_spline_reduce.ReduceDegree(kDimension0_, kEpsilon_));
  EXPECT_EQ(b_spline_reduce, b_spline_elevate_reduce_);
  EXPECT_TRUE(b_spline.ReduceDegree(kDimension0_, kEpsilon_, kMultiplicity2_));
  EXPECT_EQ(b_spline, b_spline_);
  EXPECT_TRUE(b_spline_reduce.ReduceDegree(kDimension0_, kEpsilon_));
  EXPECT_EQ(b_spline_reduce, b_spline_);
  EXPECT_FALSE(b_spline_unsuccessful.ReduceDegree(kDimension1_, kEpsilon_));
  EXPECT_EQ(b_spline_unsuccessful, b_spline_);
}

TEST_F(BSplineSuite, ComputeUpperBoundForMaximumDistanceFromOrigin) {
  EXPECT_TRUE(IsEqual(b_spline_.ComputeUpperBoundForMaximumDistanceFromOrigin(),
                      vector_space_->DetermineMaximumDistanceFromOrigin()));
}

TEST_F(BSplineSuite, Write) {
  EXPECT_EQ(b_spline_.Write(), (BSpline_::OutputInformation_{parameter_space_->Write(), vector_space_->Write()}));
}

#ifndef NDEBUG
TEST_F(BSplineSuite, ThrowIfNotParameterSpaceAndVectorSpaceDoNotMatch) {
  EXPECT_THROW(BSpline_(parameter_space_insert_remove_, vector_space_), DomainError);
}

TEST_F(BSplineSuite, ThrowIfNotDimensionIsInvalid) {
  constexpr Dimension const kDimension2{2};

  EXPECT_THROW(b_spline_.InsertKnot(kDimension2, kKnot0_5_), OutOfRange);
  EXPECT_THROW(b_spline_.RemoveKnot(kDimension2, kKnot0_5_, kEpsilon_), OutOfRange);
  EXPECT_THROW(b_spline_.ElevateDegree(kDimension2), OutOfRange);
  EXPECT_THROW(b_spline_.ReduceDegree(kDimension2, kEpsilon_), OutOfRange);
}

TEST_F(BSplineSuite, ThrowIfParametricCoordinateIsOutsideScope) {
  EXPECT_THROW(b_spline_.InsertKnot(kDimension0_, ParametricCoordinate{-0.5}), OutOfRange);
}
#endif
}  // namespace splinelib::tests::splines
