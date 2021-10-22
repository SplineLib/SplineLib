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
#include "Sources/ParameterSpaces/parameter_space.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/numeric_operations.hpp"
#include "Tests/ParameterSpaces/parameter_space_2d.hpp"
#include "Tests/ParameterSpaces/knot_vector_mock.hpp"
#include "Tests/ParameterSpaces/non_zero_degree_b_spline_basis_function_mock.hpp"
#include "Tests/Utilities/index_mock.hpp"

namespace splinelib::tests::parameter_spaces {

using sources::parameter_spaces::ParameterSpace, testing::StrictMock;
using sources::utilities::numeric_operations::IsEqual, std::make_shared;

// Test parameter space combining knot vectors from NURBS book Exa. 2.2 (U_0) and Exa. 2.1 (U_1).
class ParameterSpaceSuite : public testing::Test {
 protected:
  using Index_ = StrictMock<utilities::A2dIndexMock>;
  using KnotVector_ = StrictMock<AKnotVectorMock>;
  using ParameterSpace_ = ParameterSpace<2>;
  using Tolerance_ = sources::parameter_spaces::Tolerance;
  using BinomialRatios_ = ParameterSpace_::BinomialRatios_;
  using Degrees_ = ParameterSpace_::Degrees_;
  using Derivative_ = ParameterSpace_::Derivative_;
  using ElevationInformation_ = ParameterSpace_::ElevationInformation_;
  using InsertionInformation_ = ParameterSpace_::InsertionInformation_;
  using Knot_ = ParameterSpace_::Knot_;
  using NumberOfBasisFunctions_ = ParameterSpace_::NumberOfBasisFunctions_;

  constexpr static BinomialRatios_::value_type const kOneSixth_{1.0 / 6.0}, kOneFourth_{0.25}, kOneThird_{1.0 / 3.0},
                                                     kOneHalf_{0.5}, kTwoThirds_{2.0 / 3.0}, kThreeFourth_{0.75};
  constexpr static Degree const kDegree2_{2};
  constexpr static Degrees_ const kDegrees_{kDegree2_, kDegree2_}, kDegreesElevatedTwice_{Degree{4}, kDegree2_};
  constexpr static Derivative const kDerivative0_{}, kDerivative1_{1};
  constexpr static Derivative_ const kDerivative_{kDerivative1_, kDerivative0_};
  constexpr static Dimension const kDimension0_{}, kDimension1_{1};
  constexpr static Index const kIndex2_{2};
  constexpr static Knot_ const k0_0_{}, k0_5_{0.5}, k1_0_{1.0}, k5_0_{5.0};
  constexpr static Length const kLength3_{3}, kLength8_{8};
  constexpr static Multiplicity const kMultiplicity2_{2};
  constexpr static NumberOfBasisFunctions_ const kNumberOfBasisFunctions_{kLength8_, kLength3_},
                                                 kNumberOfNonZeroBasisFunctions_{kLength3_, kLength3_};
  constexpr static Tolerance_ const &kEpsilon_ = sources::parameter_spaces::kEpsilon;
  constexpr static ParametricCoordinate const kPerturbation_{1.1 * kEpsilon_};
  constexpr static ParameterSpace_::ParametricCoordinate_ kParametricCoordinate_{k1_0_, k0_5_};
  inline static BinomialRatios_ const kBinomialRatios_{kOneHalf_, kOneHalf_};
  inline static ElevationInformation_ const kElevationInformationFirst_{kIndex2_, {{kOneThird_, kTwoThirds_},
      {kTwoThirds_, kOneThird_}}}, kElevationInformationSecond_{Index{3}, {{kOneFourth_, kThreeFourth_},
          kBinomialRatios_, {kThreeFourth_, kOneFourth_}}}, kElevationInformationTwice_{kIndex2_, {kBinomialRatios_,
              {kOneSixth_, kTwoThirds_, kOneSixth_}, kBinomialRatios_}};
  inline static ParameterSpace_::KnotRatios_ const kKnotRatiosFirst_{kOneHalf_, kOneHalf_},
                                                   kKnotRatiosSecond_{kOneHalf_};
  inline static InsertionInformation_ const kInsertionInformationFirst_{kIndex2_, {kKnotRatiosFirst_}},
      kInsertionInformationSecond_{kIndex2_, {kKnotRatiosSecond_}}, kInsertionInformationTwice_{kIndex2_,
          {kKnotRatiosFirst_, kKnotRatiosSecond_}};
  inline static ParameterSpace_::KnotVectors_ const kKnotVectors_{mock_knot_vectors::NurbsBookExa2_2()};
  inline static ParameterSpace2d const kParameterSpaceElevatedOnce_{mock_knot_vectors::NurbsBookExa2_2IncreasedOnce(),
      Degrees_{Degree{3}, kDegree2_}, mock_b_spline_basis_functions::NurbsBookExa2_2ElevatedOnce()},
          kParameterSpaceInserted_{mock_knot_vectors::NurbsBookExa2_2Inserted(), kDegrees_,
              mock_b_spline_basis_functions::NurbsBookExa2_2Inserted()};

  ParameterSpaceSuite();

  StrictMock<ANonZeroDegreeBSplineBasisFunctionMock> basis_function0_, basis_function1_;
  Index_ basis_function1_0_;
  SharedPointer<KnotVector_> knot_vector_{make_shared<KnotVector_>()};
  ParameterSpace2d parameter_space_{kKnotVectors_, kDegrees_, mock_b_spline_basis_functions::NurbsBookExa2_2()};
};

ParameterSpaceSuite::ParameterSpaceSuite() {
  basis_function1_.NurbsBookExa2_2_1_2();
  basis_function0_.NurbsBookExa2_1_0_2();
  basis_function1_0_.NurbsBookExa2_2_1_0();
  knot_vector_->NurbsBookExa2_1();
}

TEST_F(ParameterSpaceSuite, CopyConstructAndCopyAssignDependingOnCopyKnotVectorsAndRecreateBasisFunctions) {
  EXPECT_NO_THROW(ParameterSpace_ parameter_space_copy_constructed(parameter_space_));

  ParameterSpace_ parameter_space_copy_assigned;
  EXPECT_NO_THROW(parameter_space_copy_assigned = parameter_space_);
}

TEST_F(ParameterSpaceSuite, IsEqualAndOperatorEqual) {
  constexpr static Tolerance_ const &kTolerance = (1.2 * kEpsilon_);

  ParameterSpace_ parameter_space;
  ASSERT_NO_THROW(parameter_space = ParameterSpace_(kKnotVectors_, kDegrees_));
  EXPECT_TRUE(IsEqual(parameter_space, parameter_space_));
  EXPECT_TRUE(parameter_space == parameter_space_);

  SharedPointer<KnotVector_> knot_vector{make_shared<KnotVector_>()};
  knot_vector->NurbsBookExa2_2Perturbed();
  ParameterSpace_ parameter_space_knot_vector;
  ASSERT_NO_THROW(parameter_space_knot_vector = ParameterSpace_({knot_vector, knot_vector_}, kDegrees_, kTolerance));
//  ASSERT_NO_THROW(parameter_space_knot_vector = ParameterSpace2d({knot_vector, knot_vector_}, kDegrees_,
//                                                    mock_b_spline_basis_functions::NurbsBookExe2_2Perturbed()));
  EXPECT_FALSE(IsEqual(parameter_space_knot_vector, parameter_space_));
  EXPECT_FALSE(parameter_space_knot_vector == parameter_space_);
  EXPECT_TRUE(IsEqual(parameter_space_knot_vector, parameter_space_, kTolerance));
}

TEST_F(ParameterSpaceSuite, BeginDependingOnGetNumberOfNonZeroBasisFunctions) {
  EXPECT_EQ(parameter_space_.First(), Index_::First(kNumberOfNonZeroBasisFunctions_));
}

TEST_F(ParameterSpaceSuite, EndDependingOnGetNumberOfNonZeroBasisFunctions) {
  EXPECT_EQ(parameter_space_.Behind(), Index_::Behind(kNumberOfNonZeroBasisFunctions_));
}

TEST_F(ParameterSpaceSuite, GetNumberOfBasisFunctionsDependingOnGetNumberOfBasisFunctions) {
  EXPECT_EQ(parameter_space_.GetNumberOfBasisFunctions(), kNumberOfBasisFunctions_);
}

TEST_F(ParameterSpaceSuite, GetTotalNumberOfBasisFunctionsDependingOnGetNumberOfBasisFunctions) {
  EXPECT_EQ(parameter_space_.GetTotalNumberOfBasisFunctions(), (kLength8_ * kLength3_).Get());
}

TEST_F(ParameterSpaceSuite, FindFirstNonZeroBasisFunctionIndexValueDependingOnGetNumberOfBasisFunctions) {
  Index_ basis_function1_0;
  basis_function1_0.NurbsBookExa2_2_1_0();
  EXPECT_EQ(parameter_space_.FindFirstNonZeroBasisFunction(kParametricCoordinate_), basis_function1_0);
}

TEST_F(ParameterSpaceSuite, DetermineBezierExtractionKnots) {
  EXPECT_EQ(parameter_space_.DetermineBezierExtractionKnots(kDimension0_), (ParameterSpace_::BezierInformation_{5,
                                                                                {k1_0_, Knot_{2.0}, Knot_{3.0}}}));
}

TEST_F(ParameterSpaceSuite, EvaluateBasisFunction) {
  EXPECT_TRUE(IsEqual(parameter_space_.EvaluateBasisFunction(basis_function1_0_, kParametricCoordinate_),
                      basis_function1_(k1_0_) * basis_function0_(k0_5_)));
}

TEST_F(ParameterSpaceSuite, EvaluateBasisFunctionDerivative) {
  EXPECT_TRUE(IsEqual(parameter_space_.EvaluateBasisFunctionDerivative(basis_function1_0_, kParametricCoordinate_,
                  kDerivative_), basis_function1_(k1_0_, kDerivative1_) * basis_function0_(k0_5_, kDerivative0_)));
  EXPECT_TRUE(IsEqual(parameter_space_.EvaluateBasisFunctionDerivative(basis_function1_0_, kParametricCoordinate_,
      Derivative_{kDerivative0_, kDerivative0_}), parameter_space_.EvaluateBasisFunction(basis_function1_0_,
                                                                                         kParametricCoordinate_)));
}

TEST_F(ParameterSpaceSuite, InsertKnotDependingOnDetermineInsertionInformationAndRecreateBasisFunctions) {
  ParameterSpace_ parameter_space_insert, parameter_space_subdivide;
  ASSERT_NO_THROW(parameter_space_insert = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2(), kDegrees_,
                                                            mock_b_spline_basis_functions::NurbsBookExa2_2()));
  ASSERT_NO_THROW(parameter_space_subdivide = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2(), kDegrees_,
                                                               mock_b_spline_basis_functions::NurbsBookExa2_2()));
  EXPECT_EQ(parameter_space_insert.InsertKnot(kDimension1_, k0_5_), kInsertionInformationFirst_);
  EXPECT_EQ(parameter_space_insert, kParameterSpaceInserted_);
  EXPECT_EQ(parameter_space_subdivide.InsertKnot(kDimension1_, k0_5_, kMultiplicity2_), kInsertionInformationTwice_);
  EXPECT_EQ(parameter_space_subdivide, ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2Subdivided(), kDegrees_,
                                                        mock_b_spline_basis_functions::NurbsBookExa2_2Subdivided()));
  EXPECT_EQ(parameter_space_insert.InsertKnot(kDimension1_, k0_5_), kInsertionInformationSecond_);
  EXPECT_EQ(parameter_space_insert, parameter_space_subdivide);
}

TEST_F(ParameterSpaceSuite, RemoveKnotDependingOnDetermineInsertionInformationAndRecreateBasisFunctions) {
  ParameterSpace_ parameter_space_remove, parameter_space_erase;
  ASSERT_NO_THROW(parameter_space_remove = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2Subdivided(), kDegrees_,
                                                            mock_b_spline_basis_functions::Empty()));
  ASSERT_NO_THROW(parameter_space_erase = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2Subdivided(), kDegrees_,
                                                           mock_b_spline_basis_functions::Empty()));
  EXPECT_EQ(parameter_space_remove.RemoveKnot(kDimension1_, k0_5_), kInsertionInformationSecond_);
  EXPECT_EQ(parameter_space_remove, kParameterSpaceInserted_);
  EXPECT_EQ(parameter_space_erase.RemoveKnot(kDimension1_, k0_5_, kMultiplicity2_), kInsertionInformationTwice_);
  EXPECT_EQ(parameter_space_erase, parameter_space_);
  EXPECT_EQ(parameter_space_remove.RemoveKnot(kDimension1_, k0_5_), kInsertionInformationFirst_);
  EXPECT_EQ(parameter_space_remove, parameter_space_);
  EXPECT_EQ(parameter_space_remove.RemoveKnot(kDimension1_, k0_5_), InsertionInformation_{});
  EXPECT_EQ(parameter_space_remove, parameter_space_);
}

TEST_F(ParameterSpaceSuite, ElevateDegreeDependingOnRecreateBasisFunctions) {
  ParameterSpace_ parameter_space_elevate_once, parameter_space_elevate_twice;
  ASSERT_NO_THROW(parameter_space_elevate_once = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2(), kDegrees_,
                                                                  mock_b_spline_basis_functions::NurbsBookExa2_2()));
  ASSERT_NO_THROW(parameter_space_elevate_twice = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2(), kDegrees_,
                                                                   mock_b_spline_basis_functions::NurbsBookExa2_2()));
  EXPECT_EQ(parameter_space_elevate_once.ElevateDegree(kDimension0_), kElevationInformationFirst_);
  EXPECT_EQ(parameter_space_elevate_once, kParameterSpaceElevatedOnce_);
  EXPECT_EQ(parameter_space_elevate_twice.ElevateDegree(kDimension0_, kMultiplicity2_), kElevationInformationTwice_);
  EXPECT_EQ(parameter_space_elevate_twice, ParameterSpace_(mock_knot_vectors::NurbsBookExa2_2IncreasedTwice(),
                                                           kDegreesElevatedTwice_));
//  EXPECT_EQ(parameter_space_elevate_twice, ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2IncreasedTwice(),
//                kDegreesElevatedTwice_, mock_b_spline_basis_functions::NurbsBookExa2_2ElevatedTwice()));
  EXPECT_EQ(parameter_space_elevate_once.ElevateDegree(kDimension0_), kElevationInformationSecond_);
  EXPECT_EQ(parameter_space_elevate_once, parameter_space_elevate_twice);
}

TEST_F(ParameterSpaceSuite, ReduceDegreeDependingOnRecreateBasisFunctions) {
  constexpr Degree const kDegree1{1};

  ParameterSpace_ parameter_space_reduce_once, parameter_space_reduce_twice;
  ASSERT_NO_THROW(parameter_space_reduce_once = ParameterSpace_(mock_knot_vectors::NurbsBookExa2_2IncreasedTwice(),
                                                                kDegreesElevatedTwice_));
//  ASSERT_NO_THROW(parameter_space_reduce_once = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2IncreasedTwice(),
//                      kDegreesElevatedTwice_, mock_b_spline_basis_functions::NurbsBookExa2_2ElevatedTwice()));
  ASSERT_NO_THROW(parameter_space_reduce_twice = ParameterSpace_(mock_knot_vectors::NurbsBookExa2_2IncreasedTwice(),
                                                                 kDegreesElevatedTwice_));
//  ASSERT_NO_THROW(parameter_space_reduce_twice = ParameterSpace2d(mock_knot_vectors::NurbsBookExa2_2IncreasedTwice(),
//                      kDegreesElevatedTwice_, mock_b_spline_basis_functions::NurbsBookExa2_2ElevatedTwice()));
  EXPECT_EQ(parameter_space_reduce_once.ReduceDegree(kDimension0_), kElevationInformationSecond_);
  EXPECT_EQ(parameter_space_reduce_once, kParameterSpaceElevatedOnce_);
  EXPECT_EQ(parameter_space_reduce_twice.ReduceDegree(kDimension0_, kMultiplicity2_), kElevationInformationTwice_);
  EXPECT_EQ(parameter_space_reduce_twice, parameter_space_);
  EXPECT_EQ(parameter_space_reduce_once.ReduceDegree(kDimension0_), kElevationInformationFirst_);
  EXPECT_EQ(parameter_space_reduce_once, parameter_space_reduce_twice);
  EXPECT_EQ(ParameterSpace_(mock_knot_vectors::NurbsBookExe4_4(), Degrees_{kDegree1,
                kDegree1}).ReduceDegree(kDimension0_), (ElevationInformation_{Index{kDegree1.Get()}, {}}));
}

TEST_F(ParameterSpaceSuite, Sample) {
  constexpr ParametricCoordinate const k2_5{2.5};

  EXPECT_EQ(parameter_space_.Sample({kLength3_, Length{2}}), (ParameterSpace_::ParametricCoordinates_{{k0_0_, k0_0_},
                {k2_5, k0_0_}, {k5_0_, k0_0_}, {k0_0_, k1_0_}, {k2_5, k1_0_}, {k5_0_, k1_0_}}));
}

TEST_F(ParameterSpaceSuite, WriteDependingOnGetNumberOfBasisFunctions) {
  using OutputInformation = ParameterSpace_::OutputInformation_;
  using std::tuple_element_t;
  using sources::utilities::string_operations::Write;

  EXPECT_EQ(parameter_space_.Write(), (OutputInformation{{kKnotVectors_[0]->Write(), kKnotVectors_[1]->Write()},
                                           Write<tuple_element_t<1, OutputInformation>>(kDegrees_),
                                           Write<tuple_element_t<2, OutputInformation>>(kNumberOfBasisFunctions_)}));
}

#ifndef NDEBUG
TEST_F(ParameterSpaceSuite, ThrowIfKnotVectorsAreNotClamped) {
  SharedPointer<KnotVector_> knot_vector_unclamped{make_shared<KnotVector_>()},
                             knot_vector_interior{make_shared<KnotVector_>()};
  knot_vector_unclamped->NurbsBookExa2_2Unclamped();
  knot_vector_interior->NurbsBookExa2_2Interior();
  EXPECT_THROW(ParameterSpace_({knot_vector_unclamped, knot_vector_}, kDegrees_), DomainError);
  EXPECT_THROW(ParameterSpace_({knot_vector_interior, knot_vector_}, kDegrees_), DomainError);
  EXPECT_THROW(ParameterSpace_(kKnotVectors_, Degrees_{Degree{}, kDegree2_}), DomainError);
  EXPECT_THROW(parameter_space_.InsertKnot(kDimension0_, k0_0_), DomainError);
  EXPECT_THROW(parameter_space_.RemoveKnot(kDimension0_, k5_0_), DomainError);
}

TEST_F(ParameterSpaceSuite, ThrowIfDimensionIsInvalid) {
  constexpr Dimension const kDimension2{2};

  EXPECT_THROW(parameter_space_.InsertKnot(kDimension2, k0_5_), OutOfRange);
  EXPECT_THROW(parameter_space_.RemoveKnot(kDimension2, k0_5_), OutOfRange);
  EXPECT_THROW(parameter_space_.ElevateDegree(kDimension2), OutOfRange);
  EXPECT_THROW(parameter_space_.ReduceDegree(kDimension2), OutOfRange);
}

TEST_F(ParameterSpaceSuite, ThrowIfParametricCoordinateIsOutsideScope) {
  constexpr ParametricCoordinate const kMinus0_5{-0.5};

  EXPECT_THROW(parameter_space_.FindFirstNonZeroBasisFunction({kMinus0_5, k0_5_}), OutOfRange);
  EXPECT_THROW(parameter_space_.InsertKnot(kDimension0_, kMinus0_5), OutOfRange);
}

TEST_F(ParameterSpaceSuite, ThrowIfBasisFunctionIndexIsInvalid) {
  Index_ basis_function_index_invalid;
  basis_function_index_invalid.NurbsBookExa2_2_1_3();
  EXPECT_THROW(parameter_space_.EvaluateBasisFunction(basis_function_index_invalid, kParametricCoordinate_),
               OutOfRange);
  EXPECT_THROW(parameter_space_.EvaluateBasisFunctionDerivative(basis_function_index_invalid, kParametricCoordinate_,
                                                                kDerivative_), OutOfRange);
}
#endif
}  // namespace splinelib::tests::parameter_spaces
