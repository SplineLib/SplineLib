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

#include "Tests/ParameterSpaces/parameter_space_mock.hpp"

#include <utility>

#include "Tests/ParameterSpaces/knot_vector_mock.hpp"
#include "Tests/ParameterSpaces/b_spline_basis_function_mock.hpp"
#include "Tests/ParameterSpaces/non_zero_degree_b_spline_basis_function_mock.hpp"

namespace splinelib::tests::parameter_spaces {

namespace {

MATCHER_P2(IsGeAndLt, minimum, supremum, "") {
  return ((minimum <= arg) && (arg < supremum));
}

using std::tuple_element_t;
using BezierInformation = A2dParameterSpaceMock::BezierInformation_;
using BinomialRatios = A2dParameterSpaceMock::BinomialRatios_;
using Degrees = A2dParameterSpaceMock::Degrees_;
using DegreesOutput = tuple_element_t<1, A2dParameterSpaceMock::OutputInformation_>;
using Derivative = A2dParameterSpaceMock::Derivative_;
using ElevationInformation = A2dParameterSpaceMock::ElevationInformation_;
using Index = A2dParameterSpaceMock::Index_;
using IndexLength = Index::Length_;
using InsertionInformation = A2dParameterSpaceMock::InsertionInformation_;
using ParametricCoordinate = A2dParameterSpaceMock::ParametricCoordinate_;
using ScalarIndex = Index::Value_::value_type;
using ScalarParametricCoordinate = ParametricCoordinate::value_type;
using Type = A2dParameterSpaceMock::Type_;
using testing::AnyNumber, testing::DoAll, testing::Ge, testing::InvokeWithoutArgs, testing::Lt, testing::Return,
      testing::StrictMock, testing::Throw;

constexpr BinomialRatios::value_type const kOneSixth{1.0 / 6.0}, kOneFourth{0.25}, kOneThird{1.0 / 3.0}, kOneHalf{0.5},
                                           kTwoThirds{2.0 / 3.0}, kThreeFourths{0.75};
constexpr Degrees::value_type const kDegree1{1}, kDegree2{2};
constexpr Degrees const kDegrees1_1{kDegree1, kDegree1}, kDegrees2_2{kDegree2, kDegree2};
constexpr Derivative::value_type const kDerivative0{}, kDerivative1{1};
constexpr Derivative const kDerivative0_0{kDerivative0, kDerivative0}, kDerivative1_0{kDerivative1, kDerivative0},
                           kDerivative0_1{kDerivative0, kDerivative1}, kDerivative1_1{kDerivative1, kDerivative1};
constexpr Dimension const kDimension0{}, kDimension1{1};
constexpr sources::parameter_spaces::KnotRatio const kKnotRatio{0.5};
constexpr Length const kLength2{2}, kLength3{3}, kLength4{4};
constexpr Multiplicity const kMultiplicity2{2};
constexpr ScalarIndex const kIndex1{1}, kIndex2{2}, kIndex3{3};
constexpr ScalarParametricCoordinate const kParametricCoordinate0_0{0.0}, kParametricCoordinate0_5{0.5},
                                           kParametricCoordinate1_0{1.0};
constexpr ParametricCoordinate const kParametricCoordinate0{kParametricCoordinate0_0, kParametricCoordinate0_0},
                                     kParametricCoordinate1{kParametricCoordinate1_0, kParametricCoordinate0_0},
                                     kParametricCoordinate2{kParametricCoordinate0_0, kParametricCoordinate1_0},
                                     kParametricCoordinate3{kParametricCoordinate1_0, kParametricCoordinate1_0};
constexpr A2dParameterSpaceMock::NumberOfParametricCoordinates_ const kNumberOfParametricCoordinates{kLength2,
                                                                                                     kLength2};
A2dParameterSpaceMock::BezierInformation_ const kBezierInformation{2, {kParametricCoordinate0_5}};
BinomialRatios const kBinomialRatios{kOneHalf, kOneHalf};
A2dParameterSpaceMock::KnotRatios_ const kKnotRatiosFirst{kKnotRatio, kKnotRatio}, kKnotRatiosSecond{kKnotRatio};
ElevationInformation const kElevationInformationOnce{kIndex2, {{kOneThird, kTwoThirds}, {kTwoThirds, kOneThird}}},
    kElevationInformationElevateReduce{kIndex3, {{kOneFourth, kThreeFourths}, kBinomialRatios, {kThreeFourths,
        kOneFourth}}}, kElevationInformationTwice{kIndex2, {kBinomialRatios, {kOneSixth, kTwoThirds, kOneSixth},
            kBinomialRatios}};
InsertionInformation const kInsertionInformation{kIndex2, {kKnotRatiosFirst}},
    kInsertionInformationInsertRemove{kIndex2, {kKnotRatiosSecond}}, kInsertionInformationSubdivided{kIndex2,
        {kKnotRatiosFirst, kKnotRatiosSecond}}, kInsertionInformationElevateReduce{kIndex3, {kKnotRatiosSecond}},
            kInsertionInformationElevatedTwice{ScalarIndex{4}, {kKnotRatiosSecond}};
IsGeAndLtMatcherP2<Dimension, Dimension> const &IsValidDimension = IsGeAndLt(kDimension0, Dimension{3});
IsGeAndLtMatcherP2<double, double> const &IsGe0_0AndLt0_5 = IsGeAndLt(0.0, 0.5);
IsGeAndLtMatcherP2<ScalarParametricCoordinate, ScalarParametricCoordinate> const &IsInScope =
    IsGeAndLt(kParametricCoordinate0_0, kParametricCoordinate1_0);

}  // namespace

Index A2dParameterSpaceMock::FindFirstNonZeroBasisFunction(ParametricCoordinate_ const &parametric_coordinate,
                                                           Tolerance_ const &tolerance) const {
  return FindFirstNonZeroBasisFunctionMock(parametric_coordinate, tolerance);
}

BezierInformation A2dParameterSpaceMock::DetermineBezierExtractionKnots(Dimension const &dimension,
                                                                        Tolerance_ const &tolerance) const {
  return DetermineBezierExtractionKnotsMock(dimension, tolerance);
}

Type A2dParameterSpaceMock::EvaluateBasisFunction(Index_ const &basis_function_index,
    ParametricCoordinate_ const &parametric_coordinate, Tolerance_ const &tolerance) const {
  return EvaluateBasisFunctionMock(basis_function_index, parametric_coordinate, tolerance);
}

Type A2dParameterSpaceMock::EvaluateBasisFunctionDerivative(Index_ const &basis_function_index,
    ParametricCoordinate_ const &parametric_coordinate, Derivative_ const &derivative, Tolerance_ const &tolerance)
        const {
  return EvaluateBasisFunctionDerivativeMock(basis_function_index, parametric_coordinate, derivative, tolerance);
}

InsertionInformation A2dParameterSpaceMock::InsertKnot(Dimension const &dimension, Knot_ knot,
                                                       Multiplicity const &multiplicity, Tolerance_ const &tolerance) {
  return InsertKnotMock(dimension, std::move(knot), multiplicity, tolerance);
}

InsertionInformation A2dParameterSpaceMock::RemoveKnot(Dimension const &dimension, Knot_ const &knot,
                                                       Multiplicity const &multiplicity, Tolerance_ const &tolerance) {
  return RemoveKnotMock(dimension, knot, multiplicity, tolerance);
}

ElevationInformation A2dParameterSpaceMock::ElevateDegree(Dimension const &dimension, Multiplicity const &multiplicity,
                                                           Tolerance_ const &tolerance) {
  return ElevateDegreeMock(dimension, multiplicity, tolerance);
}

ElevationInformation A2dParameterSpaceMock::ReduceDegree(Dimension const &dimension, Multiplicity const &multiplicity,
                                                          Tolerance_ const &tolerance) {
  return ReduceDegreeMock(dimension, multiplicity, tolerance);
}

A2dParameterSpaceMock::OutputInformation_ A2dParameterSpaceMock::Write(Precision const &precision) const {
  return WriteMock(precision);
}

#ifndef NDEBUG
void A2dParameterSpaceMock::ThrowIfParametricCoordinateIsOutsideScope(Dimension const &dimension,
    ScalarParametricCoordinate const &parametric_coordinate, Tolerance_ const &tolerance) const {
  ThrowIfParametricCoordinateIsOutsideScopeMock(dimension, parametric_coordinate, tolerance);
}
#endif

void A2dParameterSpaceMock::NurbsBookExe3_8() {
  using sources::utilities::string_operations::Write;

  constexpr ScalarIndex const kIndex0{};
  constexpr IndexLength const kNumberOfBasisFunctions{kLength4, kLength3}, kNonZeroBasisFunctionIndexLength{kLength3,
                                                                                                            kLength3};
  constexpr ParametricCoordinate_ const kParametricCoordinate{ScalarParametricCoordinate{0.75},
                                                              kParametricCoordinate0_5};
  constexpr Type const kMinus8_0{-8.0}, kMinus1_0{-1.0}, k0_0{}, k0_03125{0.03125}, k0_0625{0.0625}, k0_125{0.125},
      k0_15625{0.15625}, k0_25{0.25}, k0_3125{0.3125}, k0_5{0.5}, k0_625{0.625}, k1_0{1.0}, k2_0{2.0}, k8_0{8.0};
  Index_ const kBasisFunction0_0{kNumberOfBasisFunctions, {kIndex0, kIndex0}}, kBasisFunction1_0{
      kNumberOfBasisFunctions, {kIndex1, kIndex0}}, kBasisFunction2_0{kNumberOfBasisFunctions, {kIndex2, kIndex0}},
          kBasisFunction3_0{kNumberOfBasisFunctions, {kIndex3, kIndex0}}, kBasisFunction0_1{kNumberOfBasisFunctions,
              {kIndex0, kIndex1}}, kBasisFunction1_1{kNumberOfBasisFunctions, {kIndex1, kIndex1}}, kBasisFunction2_1{
                  kNumberOfBasisFunctions, {kIndex2, kIndex1}}, kBasisFunction3_1{kNumberOfBasisFunctions, {kIndex3,
                      kIndex1}}, kBasisFunction0_2{kNumberOfBasisFunctions, {kIndex0, kIndex2}}, kBasisFunction1_2{
                          kNumberOfBasisFunctions, {kIndex1, kIndex2}}, kBasisFunction2_2{kNumberOfBasisFunctions,
                              {kIndex2, kIndex2}}, kBasisFunction3_2{kNumberOfBasisFunctions, {kIndex3, kIndex2}};

  NurbsBookExe3_8KnotVectorsDegrees();
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  StrictMock<ANonZeroDegreeBSplineBasisFunctionMock> basis_function_for_dimension_one0;
  basis_function_for_dimension_one0.NurbsBookExa2_1_0_2();
  EXPECT_CALL(*this, First()).WillRepeatedly(Return(Index_::First(kNonZeroBasisFunctionIndexLength)));
  EXPECT_CALL(*this, Behind()).WillRepeatedly(Return(Index_::Behind(kNonZeroBasisFunctionIndexLength)));

  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(kNumberOfBasisFunctions));
  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(12));

  EXPECT_CALL(*this, FindFirstNonZeroBasisFunctionMock(kParametricCoordinate0, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBasisFunction0_0));
  EXPECT_CALL(*this, FindFirstNonZeroBasisFunctionMock(kParametricCoordinate1, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBasisFunction1_0));
  EXPECT_CALL(*this, FindFirstNonZeroBasisFunctionMock(kParametricCoordinate2, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBasisFunction0_0));
  EXPECT_CALL(*this, FindFirstNonZeroBasisFunctionMock(kParametricCoordinate3, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBasisFunction1_0));
  EXPECT_CALL(*this, FindFirstNonZeroBasisFunctionMock(kParametricCoordinate, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBasisFunction1_0));
  EXPECT_CALL(*this, DetermineBezierExtractionKnotsMock(kDimension0, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBezierInformation));
  EXPECT_CALL(*this, DetermineBezierExtractionKnotsMock(kDimension1, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(BezierInformation_{1, {}}));

  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction0_0, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction0_0, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_0, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_125 * basis_function_for_dimension_one0(kParametricCoordinate0_5)));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_0, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_0, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_0, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_0, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_0, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_625 * basis_function_for_dimension_one0(kParametricCoordinate0_5)));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_0, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_0, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_0, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_0, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_0, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_25 * basis_function_for_dimension_one0(kParametricCoordinate0_5)));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_0, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_0, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction0_1, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction0_1, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_1, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_0625));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_1, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_1, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_1, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_1, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_1, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_3125));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_1, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_1, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_1, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_1, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_1, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_125));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_1, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_1, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction0_2, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction0_2, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_2, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_03125));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_2, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_2, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_2, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction1_2, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_2, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_15625));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_2, kParametricCoordinate0, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_2, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_2, kParametricCoordinate2, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction2_2, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_2, kParametricCoordinate, Ge(0.0)))
      .WillRepeatedly(Return(k0_0625));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_2, kParametricCoordinate1, Ge(0.0)))
      .WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionMock(kBasisFunction3_2, kParametricCoordinate3, Ge(0.0)))
      .WillRepeatedly(Return(k1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_0, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(Type{-4.0}));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_0, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(Type{-2.0}));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_0, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k8_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate, kDerivative0_0,
                         Ge(0.0))).WillRepeatedly(Return(k0_125 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative0)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate, kDerivative1_0,
                         Ge(0.0))).WillRepeatedly(Return(k1_0 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative0)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(Type{4.0}));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate, kDerivative0_1,
                         Ge(0.0))).WillRepeatedly(Return(k0_125 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative1)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate, kDerivative1_1,
                         Ge(0.0))).WillRepeatedly(Return(k1_0 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative1)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_0, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(kMinus8_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate, kDerivative0_0,
                         Ge(0.0))).WillRepeatedly(Return(k0_625 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative0)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate, kDerivative1_0,
                         Ge(0.0))).WillRepeatedly(Return(kMinus1_0 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative0)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate, kDerivative0_1,
                         Ge(0.0))).WillRepeatedly(Return(k0_625 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative1)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate, kDerivative1_1,
                         Ge(0.0))).WillRepeatedly(Return(kMinus1_0 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative1)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_0, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_0, kParametricCoordinate, kDerivative0_0,
                         Ge(0.0))).WillRepeatedly(Return(k0_25 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative0)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_0, kParametricCoordinate, kDerivative1_0,
                         Ge(0.0))).WillRepeatedly(Return(k2_0 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative0)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_0, kParametricCoordinate, kDerivative0_1,
                         Ge(0.0))).WillRepeatedly(Return(k0_25 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative1)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_0, kParametricCoordinate, kDerivative1_1,
                         Ge(0.0))).WillRepeatedly(Return(k2_0 *
                                       basis_function_for_dimension_one0(kParametricCoordinate0_5, kDerivative1)));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_1, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_1, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k2_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_1, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(kMinus8_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate, kDerivative0_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0625));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_5));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_1, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k8_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate, kDerivative0_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_3125));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(Type{-0.5}));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_1, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_1, kParametricCoordinate, kDerivative0_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_125));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_1, kParametricCoordinate, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_1, kParametricCoordinate, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_1, kParametricCoordinate, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_2, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_2, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction0_2, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate, kDerivative0_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_03125));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_25));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_125));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction1_2, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate, kDerivative0_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_15625));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(Type{-0.25}));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate0, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(Type{0.625}));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate0, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(kMinus1_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction2_2, kParametricCoordinate0, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_2, kParametricCoordinate, kDerivative0_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_0625));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_2, kParametricCoordinate, kDerivative1_0,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_5));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_2, kParametricCoordinate, kDerivative0_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k0_25));
  EXPECT_CALL(*this, EvaluateBasisFunctionDerivativeMock(kBasisFunction3_2, kParametricCoordinate, kDerivative1_1,
                                                         Ge(0.0))).WillRepeatedly(Return(k2_0));

  EXPECT_CALL(*this, InsertKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8Bezier),
                            Return(kInsertionInformationInsertRemove)));
  EXPECT_CALL(*this, InsertKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8InsertRemove),
                            Return(kInsertionInformation)));
  EXPECT_CALL(*this, InsertKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity2, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8Subdivided),
                            Return(kInsertionInformationSubdivided)));
  EXPECT_CALL(*this, RemoveKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity_, IsGeAndLt(0.0, 1.0)))
      .WillRepeatedly(Return(InsertionInformation{}));
  EXPECT_CALL(*this, ReduceDegreeMock(kDimension1, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(InsertionInformation_{kIndex1, {kBinomialRatios}}));

  EXPECT_CALL(*this, Sample(kNumberOfParametricCoordinates)).WillRepeatedly(Return(ParametricCoordinates_{
      kParametricCoordinate0, kParametricCoordinate1, kParametricCoordinate2, kParametricCoordinate3}));
  EXPECT_CALL(*this, WriteMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{{{knot_vectors_[0]->Write(),
      knot_vectors_[1]->Write()}}, {Write<DegreesOutput>(degrees_)}, {Write<tuple_element_t<2, OutputInformation_>>(
                                                                          kNumberOfBasisFunctions)}}));

#ifndef NDEBUG
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(IsValidDimension, IsInScope, Ge(0.0)))
      .Times(AnyNumber());
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(IsValidDimension, ScalarParametricCoordinate{-0.5},
                                                                   Lt(0.5))).WillRepeatedly(Throw(OutOfRange("")));
#endif
}

void A2dParameterSpaceMock::NurbsBookExe3_8ElevateReduce() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe3_8IncreaseDecrease();
  degrees_ = Degrees_{Degree{3}, kDegree2};
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(IndexLength{Length{6}, kLength3}));
  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(18));

  EXPECT_CALL(*this, InsertKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8BezierElevateReduce),
                            Return(kInsertionInformationElevateReduce)));
}

void A2dParameterSpaceMock::NurbsBookExe3_8ElevatedTwice() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe3_8IncreasedTwice();
  degrees_ = Degrees_{Degree{4}, kDegree2};
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(IndexLength{Length{8}, kLength3}));
  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(24));

  EXPECT_CALL(*this, DetermineBezierExtractionKnotsMock(kDimension0, IsGe0_0AndLt0_5))
      .WillRepeatedly(Return(kBezierInformation));

  EXPECT_CALL(*this, InsertKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8BezierElevatedTwice),
                            Return(kInsertionInformationElevatedTwice)));

#ifndef NDEBUG
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(IsValidDimension, IsInScope, Ge(0.0)))
      .Times(AnyNumber());
#endif
}

void A2dParameterSpaceMock::NurbsBookExe3_8InsertRemove() {
  NurbsBookExe3_8InsertRemoveKnotVectorsDegreesBasisFunctions();

  EXPECT_CALL(*this, InsertKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8Subdivided),
                            Return(kInsertionInformationInsertRemove)));
  EXPECT_CALL(*this, RemoveKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8),
                            Return(kInsertionInformation)));
}

void A2dParameterSpaceMock::NurbsBookExe3_8KnotVector() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe3_8Perturbed();
  degrees_ = kDegrees2_2;
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(12));
}

void A2dParameterSpaceMock::NurbsBookExe3_8Subdivided() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe3_8Subdivided();
  degrees_ = kDegrees2_2;
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(NumberOfBasisFunctions_{kLength4, Length{5}}));
  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(20));

  EXPECT_CALL(*this, RemoveKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8InsertRemove),
                            Return(kInsertionInformationInsertRemove)));
  EXPECT_CALL(*this, RemoveKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity2, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8),
                            Return(kInsertionInformationSubdivided)));
}

void A2dParameterSpaceMock::NurbsBookExe3_8Unsuccessful() {
  NurbsBookExe3_8InsertRemoveKnotVectorsDegreesBasisFunctions();

  EXPECT_CALL(*this, RemoveKnotMock(kDimension1, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8InsertRemove),
                            Return(kInsertionInformation)));
}

void A2dParameterSpaceMock::NurbsBookExe4_4() {
  String const kOneString{sources::utilities::string_operations::Write(kIndex1)};

  NurbsBookExe4_4KnotVectorsDegrees();
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(4));

  EXPECT_CALL(*this, Sample(kNumberOfParametricCoordinates)).WillRepeatedly(Return(ParametricCoordinates_{
      kParametricCoordinate0, kParametricCoordinate1, kParametricCoordinate2, kParametricCoordinate3}));

  StrictMock<AKnotVectorMock> knot_vector;
  knot_vector.NurbsBookExe4_4();
  tuple_element_t<0, OutputInformation_>::value_type const knot_vector_written{knot_vector.Write()};
  EXPECT_CALL(*this, WriteMock(kPrecision_))
      .WillRepeatedly(Return(OutputInformation_{{knot_vector_written, knot_vector_written},
          sources::utilities::string_operations::Write<DegreesOutput>(degrees_), {kOneString, kOneString}}));

#ifndef NDEBUG
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(IsValidDimension, IsInScope, Ge(0.0)))
      .Times(AnyNumber());
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(IsValidDimension, ScalarParametricCoordinate{-0.5},
                                                                   Lt(0.5))).WillRepeatedly(Throw(OutOfRange("")));
#endif
}

void A2dParameterSpaceMock::NurbsBookExe4_4KnotVector() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe4_4Perturbed();
  degrees_ = kDegrees1_1;
  basis_functions_ = mock_b_spline_basis_functions::Empty();

  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(4));
}

void A2dParameterSpaceMock::SquareUnitFirstOrderBezier() {
  NurbsBookExe4_4KnotVectorsDegrees();
  basis_functions_ = mock_b_spline_basis_functions::NurbsBookExe4_4();
}

void A2dParameterSpaceMock::SquareUnitSecondOrderMaximallySmooth() {
  NurbsBookExe3_8KnotVectorsDegrees();
  basis_functions_ = mock_b_spline_basis_functions::NurbsBookExe3_8();
}

void A2dParameterSpaceMock::NurbsBookExe3_8Bezier() {
  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(IndexLength{Length{5}, kLength3}));

  EXPECT_CALL(*this, RemoveKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8),
                            Return(kInsertionInformationInsertRemove)));
  EXPECT_CALL(*this, ElevateDegreeMock(kDimension0, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8BezierElevateReduce),
                            Return(kElevationInformationOnce)));
  EXPECT_CALL(*this, ElevateDegreeMock(kDimension0, kMultiplicity2, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8BezierElevatedTwice),
                            Return(kElevationInformationTwice)));
}

void A2dParameterSpaceMock::NurbsBookExe3_8BezierElevateReduce() {
  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(IndexLength{Length{7}, kLength3}));

  EXPECT_CALL(*this, RemoveKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8ElevateReduce),
                            Return(kInsertionInformationElevateReduce)));
  EXPECT_CALL(*this, ElevateDegreeMock(kDimension0, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8BezierElevatedTwice),
                            Return(kElevationInformationElevateReduce)));
  EXPECT_CALL(*this, ReduceDegreeMock(kDimension0, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8Bezier),
                            Return(kElevationInformationOnce)));
}

void A2dParameterSpaceMock::NurbsBookExe3_8BezierElevatedTwice() {
  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(IndexLength{Length{9}, kLength3}));

  EXPECT_CALL(*this, RemoveKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8ElevatedTwice),
                            Return(kInsertionInformationElevatedTwice)));
  EXPECT_CALL(*this, ReduceDegreeMock(kDimension0, kMultiplicity_, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8BezierElevateReduce),
                            Return(kElevationInformationElevateReduce)));
  EXPECT_CALL(*this, ReduceDegreeMock(kDimension0, kMultiplicity2, IsGe0_0AndLt0_5))
      .WillRepeatedly(DoAll(InvokeWithoutArgs(this, &A2dParameterSpaceMock::NurbsBookExe3_8Bezier),
                            Return(kElevationInformationTwice)));
}

void A2dParameterSpaceMock::NurbsBookExe3_8InsertRemoveKnotVectorsDegreesBasisFunctions() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe3_8InsertRemove();
  degrees_ = kDegrees2_2;
  basis_functions_ = mock_b_spline_basis_functions::NurbsBookExe3_8InsertRemove();

  EXPECT_CALL(*this, GetNumberOfBasisFunctions()).WillRepeatedly(Return(NumberOfBasisFunctions_{kLength4, kLength4}));
  EXPECT_CALL(*this, GetTotalNumberOfBasisFunctions()).WillRepeatedly(Return(16));
}

void A2dParameterSpaceMock::NurbsBookExe3_8KnotVectorsDegrees() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe3_8();
  degrees_ = kDegrees2_2;
}

void A2dParameterSpaceMock::NurbsBookExe4_4KnotVectorsDegrees() {
  knot_vectors_ = mock_knot_vectors::NurbsBookExe4_4();
  degrees_ = kDegrees1_1;
}

}  // namespace splinelib::tests::parameter_spaces
