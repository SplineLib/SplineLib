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

#include "Tests/ParameterSpaces/knot_vector_mock.hpp"

#include "Sources/Utilities/std_container_operations.hpp"

namespace splinelib::tests::parameter_spaces {

namespace {

MATCHER_P2(IsGeAndLt, minimum, supremum, "") {
  return ((minimum <= arg) && (arg < supremum));
}

using Knots = AKnotVectorMock::Knots_;
using sources::utilities::string_operations::Write, testing::AtMost, testing::DoAll, testing::Ge,
      testing::InvokeWithoutArgs, testing::Return, testing::ReturnRef;

constexpr Index const kIndex0{}, kIndex1{1}, kIndex2{2}, kIndex3{3}, kIndex4{4}, kIndex5{5}, kIndex6{6}, kIndex7{7},
                      kIndex8{8}, kIndex9{9}, kIndex10{10}, kIndex11{11}, kIndex12{12}, kIndex13{13}, kIndex14{14},
                      kIndex15{15}, kIndex16{16};
constexpr KnotSpan const kKnotSpan3{3};
constexpr Multiplicity const kMultiplicity0{}, kMultiplicity2{2}, kMultiplicity3{3}, kMultiplicity4{4};
constexpr sources::parameter_spaces::Tolerance const &kEpsilon = sources::parameter_spaces::kEpsilon,
                                                     &kPerturbation = (1.1 * kEpsilon);
constexpr ParametricCoordinate const k0_0{}, kPerturbed{1.1 * kEpsilon}, k0_5{0.5}, k1_0{1.0}, k2_0{2.0}, k3_0{3.0},
                                     k4_0{4.0}, k5_0{5.0};
constexpr ParametricCoordinate const &k1_0Perturbed = (k1_0 + kPerturbed), &k5_0Perturbed = (k5_0 + kPerturbed);
Knots const kUniqueKnots2_1{k0_0, k1_0}, kUniqueKnots2_2{k0_0, k1_0, k2_0, k3_0, k4_0, k5_0},
            kUniqueKnots3_8{k0_0, k0_5, k1_0};
String const &kZero = Write(k0_0), &kOne = Write(k1_0);
IsGeAndLtMatcherP2<double, double> const &IsGe0_0AndLtPerturbation = IsGeAndLt(0.0, kPerturbation),
    &IsGe0_0AndLt0_5 = IsGeAndLt(0.0, 0.5), &IsGe0_0AndLt1_0Perturbed = IsGeAndLt(0.0, 1.0 - kPerturbation),
    &IsGe0_0AndLt1_0 = IsGeAndLt(0.0, 1.0), &IsGe0_0AndLt2_0 = IsGeAndLt(0.0, 2.0),
    &IsGe0_0AndLt3_0 = IsGeAndLt(0.0, 3.0), &IsGe0_0AndLt4_0 = IsGeAndLt(0.0, 4.0),
    &IsGe0_0AndLt5_0 = IsGeAndLt(0.0, 5.0);

}  // namespace

typename AKnotVectorMock::Knot_ const & AKnotVectorMock::operator[](Index const &index) const {
  return OperatorSubscript(index);
}

bool AKnotVectorMock::DoesParametricCoordinateEqualBack(ParametricCoordinate const &parametric_coordinate,
                                                        Tolerance_ const &tolerance) const {
  return DoesParametricCoordinateEqualBackMock(parametric_coordinate, tolerance);
}

bool AKnotVectorMock::DoesParametricCoordinateEqualFrontOrBack(ParametricCoordinate const &parametric_coordinate,
                                                               Tolerance_ const &tolerance) const {
  return DoesParametricCoordinateEqualFrontOrBackMock(parametric_coordinate, tolerance);
}

KnotSpan AKnotVectorMock::FindSpan(ParametricCoordinate const &parametric_coordinate, Tolerance_ const &tolerance) const
{  // NOLINT(whitespace/braces)
  return FindSpanMock(parametric_coordinate, tolerance);
}

Multiplicity AKnotVectorMock::DetermineMultiplicity(ParametricCoordinate const &knot, Tolerance_ const &tolerance) const
{  // NOLINT(whitespace/braces)
  return DetermineMultiplicityMock(knot, tolerance);
}

Knots AKnotVectorMock::GetUniqueKnots(Tolerance_ const &tolerance) const {
  return GetUniqueKnotsMock(tolerance);
}

void AKnotVectorMock::Insert(ParametricCoordinate knot, Multiplicity const &multiplicity, Tolerance_ const &tolerance) {
  InsertMock(knot, multiplicity, tolerance);
}

Multiplicity AKnotVectorMock::Remove(ParametricCoordinate const &parametric_coordinate,
                                     Multiplicity const &multiplicity, Tolerance_ const &tolerance) {
  return RemoveMock(parametric_coordinate, multiplicity, tolerance);
}

void AKnotVectorMock::IncreaseMultiplicities(Multiplicity const &multiplicity, Tolerance_ const &tolerance) {
  IncreaseMultiplicitiesMock(multiplicity, tolerance);
}

void AKnotVectorMock::DecreaseMultiplicities(Multiplicity const &multiplicity, Tolerance_ const &tolerance) {
  DecreaseMultiplicitiesMock(multiplicity, tolerance);
}

typename AKnotVectorMock::OutputInformation_ AKnotVectorMock::Write(Precision const &precision) const {
  return WriteMock(precision);
}

#ifndef NDEBUG
void AKnotVectorMock::ThrowIfParametricCoordinateIsOutsideScope(ParametricCoordinate const &parametric_coordinate,
                                                                Tolerance_ const &tolerance) const {
  ThrowIfParametricCoordinateIsOutsideScopeMock(parametric_coordinate, tolerance);
}
#endif

void AKnotVectorMock::NurbsBookExa2_1() {
  knots_.assign({k0_0, k0_0, k0_0, k1_0, k1_0, k1_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(6));
  EXPECT_CALL(*this, GetFront).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, GetBack).WillRepeatedly(ReturnRef(k1_0));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, FindSpanMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(KnotSpan{2}));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity0));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt1_0)).WillRepeatedly(Return(kUniqueKnots2_1));

  EXPECT_CALL(*this, InsertMock(k0_5, kMultiplicity_, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExe3_8_0));
  EXPECT_CALL(*this, InsertMock(k0_5, kMultiplicity2, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExe3_8_0Subdivided));
  EXPECT_CALL(*this, RemoveMock(k0_5, kMultiplicity_, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity0));

  EXPECT_CALL(*this, WriteMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{kZero, kZero, kZero, kOne, kOne,
                                                                                      kOne}));

#ifndef NDEBUG
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(k0_5, Ge(0.0))).Times(AtMost(3));
#endif
}

void AKnotVectorMock::NurbsBookExa2_1Perturbed() {
  constexpr static ParametricCoordinate const k0_0Perturbed{k0_0 + kPerturbed};

  knots_.assign({k0_0, k0_0, k0_0Perturbed, k1_0Perturbed, k1_0, k1_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0Perturbed));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k1_0Perturbed));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(6));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0Perturbed, IsGe0_0AndLt1_0Perturbed))
      .WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0Perturbed, IsGe0_0AndLtPerturbation))
      .WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0Perturbed, Ge(kPerturbation)))
      .WillRepeatedly(Return(true));
}

void AKnotVectorMock::NurbsBookExa2_2() {
  using sources::utilities::string_operations::Write, testing::Throw;

  constexpr ParametricCoordinate const kMinus0_5{-0.5};
  String const &kFour = Write(k4_0), &kFive = Write(k5_0);

  knots_.assign({k0_0, k0_0, k0_0, k1_0, k2_0, k3_0, k4_0, k4_0, k5_0, k5_0, k5_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex6)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex7)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex8)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex9)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex10)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(11));
  EXPECT_CALL(*this, GetFront).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, GetBack).WillRepeatedly(ReturnRef(k5_0));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt5_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, IsGe0_0AndLt4_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k2_0, IsGe0_0AndLt3_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k2_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
#ifndef NDEBUG
  EXPECT_CALL(*this, FindSpanMock(kMinus0_5, Ge(0.0))).WillRepeatedly(Throw(OutOfRange("")));
#endif
  EXPECT_CALL(*this, FindSpanMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kKnotSpan3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity0));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k2_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k3_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k5_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
#ifndef NDEBUG
  EXPECT_CALL(*this, DetermineMultiplicityMock(k5_0Perturbed, IsGe0_0AndLtPerturbation))
      .WillRepeatedly(Throw(OutOfRange("")));
#endif
  EXPECT_CALL(*this, DetermineMultiplicityMock(k5_0Perturbed, Ge(kPerturbation)))
      .WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt1_0)).WillRepeatedly(Return(kUniqueKnots2_2));

  EXPECT_CALL(*this, IncreaseMultiplicitiesMock(kMultiplicity_, IsGe0_0AndLt1_0))
      .WillRepeatedly(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_2IncreasedOnce));
  EXPECT_CALL(*this, IncreaseMultiplicitiesMock(kMultiplicity2, IsGe0_0AndLt1_0))
      .WillRepeatedly(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_2IncreasedTwice));

  EXPECT_CALL(*this, WriteMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{kZero, kZero, kZero, kOne,
                                                 Write(k2_0), Write(k3_0), kFour, kFour, kFive, kFive, kFive}));

#ifndef NDEBUG
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(kMinus0_5, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(Throw(OutOfRange("")));
  EXPECT_CALL(*this, ThrowIfParametricCoordinateIsOutsideScopeMock(k0_0, Ge(0.0))).Times(AtMost(1));
#endif
}

void AKnotVectorMock::NurbsBookExa2_2IncreasedOnce() {
  knots_.assign({k0_0, k0_0, k0_0, k0_0, k1_0, k1_0, k2_0, k2_0, k3_0, k3_0, k4_0, k4_0, k4_0, k5_0, k5_0, k5_0, k5_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex6)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex7)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex8)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex9)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex10)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex11)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex12)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex13)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex14)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex15)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex16)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(17));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt5_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, IsGe0_0AndLt4_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k2_0, IsGe0_0AndLt3_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k2_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity4));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k2_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k3_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k5_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity4));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt1_0)).WillRepeatedly(Return(kUniqueKnots2_2));

  EXPECT_CALL(*this, IncreaseMultiplicitiesMock(kMultiplicity_, IsGe0_0AndLt1_0))
      .WillRepeatedly(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_2IncreasedTwice));
  EXPECT_CALL(*this, DecreaseMultiplicitiesMock(kMultiplicity_, IsGe0_0AndLt1_0))
      .WillRepeatedly(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_2));
}

void AKnotVectorMock::NurbsBookExa2_2IncreasedTwice() {
  constexpr Multiplicity const kMultiplicity5{5};

  knots_.assign({k0_0, k0_0, k0_0, k0_0, k0_0, k1_0, k1_0, k1_0, k2_0, k2_0, k2_0, k3_0, k3_0, k3_0, k4_0, k4_0, k4_0,
                 k4_0, k5_0, k5_0, k5_0, k5_0, k5_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex6)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex7)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex8)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex9)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex10)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex11)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex12)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex13)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex14)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex15)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex16)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{17})).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{18})).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{19})).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{20})).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{21})).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{22})).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(23));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt5_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, IsGe0_0AndLt4_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k2_0, IsGe0_0AndLt3_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k2_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity5));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k2_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k3_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity4));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k5_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity5));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt1_0)).WillRepeatedly(Return(kUniqueKnots2_2));

  EXPECT_CALL(*this, DecreaseMultiplicitiesMock(kMultiplicity_, IsGe0_0AndLt1_0))
      .WillRepeatedly(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_2IncreasedOnce));
  EXPECT_CALL(*this, DecreaseMultiplicitiesMock(kMultiplicity2, IsGe0_0AndLt1_0))
      .WillRepeatedly(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_2));
}

void AKnotVectorMock::NurbsBookExa2_2Interior() {
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k2_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k2_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k3_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt1_0)).WillRepeatedly(Return(kUniqueKnots2_2));
}

void AKnotVectorMock::NurbsBookExa2_2Perturbed() {
  using testing::AllOf, testing::Lt;

  knots_.assign({k0_0, k0_0, k0_0, k1_0Perturbed, k2_0, k3_0, k4_0, k4_0, k5_0Perturbed, k5_0, k5_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k1_0Perturbed));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k2_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k3_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex6)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex7)).WillRepeatedly(ReturnRef(k4_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex8)).WillRepeatedly(ReturnRef(k5_0Perturbed));
  EXPECT_CALL(*this, OperatorSubscript(kIndex9)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex10)).WillRepeatedly(ReturnRef(k5_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(11));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt5_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, IsGe0_0AndLt4_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0Perturbed, AllOf(Ge(0.0), Lt(4.0 - kPerturbation))))
      .WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k2_0, IsGe0_0AndLt3_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k5_0Perturbed, Ge(kPerturbation)))
      .WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0Perturbed, IsGe0_0AndLt1_0))
      .WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k2_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k3_0, IsGe0_0AndLt2_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k5_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0Perturbed, IsGe0_0AndLt1_0Perturbed))
      .WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k2_0, IsGe0_0AndLt1_0Perturbed)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k3_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k4_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k5_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLtPerturbation))
      .WillRepeatedly(Return(Knots_{k0_0, k1_0Perturbed, k2_0, k3_0, k4_0, k5_0Perturbed, k5_0}));
  EXPECT_CALL(*this, GetUniqueKnotsMock(AllOf(Ge(kPerturbation), Lt(1.0 - kPerturbation))))
      .WillRepeatedly(Return(Knots_{k0_0, k1_0Perturbed, k2_0, k3_0, k4_0, k5_0}));
}

void AKnotVectorMock::NurbsBookExa2_2Unclamped() {
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt1_0)).WillRepeatedly(Return(kUniqueKnots2_2));
}

void AKnotVectorMock::NurbsBookExe3_8_0() {
  knots_.assign({k0_0, k0_0, k0_0, k0_5, k1_0, k1_0, k1_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k0_5));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex6)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(7));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, FindSpanMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kKnotSpan3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity_));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt0_5)).WillRepeatedly(Return(kUniqueKnots3_8));

  EXPECT_CALL(*this, InsertMock(k0_5, kMultiplicity_, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExe3_8_0Subdivided));
  EXPECT_CALL(*this, RemoveMock(k0_5, kMultiplicity_, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(DoAll(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_1), Return(kMultiplicity_)));

  EXPECT_CALL(*this, WriteMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{kZero, kZero,
                                                 sources::utilities::string_operations::Write(k0_5), kOne, kOne}));
}

void AKnotVectorMock::NurbsBookExe3_8_0IncreaseDecrease() {
  knots_.assign({k0_0, k0_0, k0_0, k0_0, k0_5, k0_5, k1_0, k1_0, k1_0, k1_0});
}

void AKnotVectorMock::NurbsBookExe3_8_0IncreasedTwice() {
  knots_.assign({k0_0, k0_0, k0_0, k0_0, k0_0, k0_5, k0_5, k0_5, k1_0, k1_0, k1_0, k1_0, k1_0});
}

void AKnotVectorMock::NurbsBookExe3_8_0Subdivided() {
  knots_.assign({k0_0, k0_0, k0_0, k0_5, k0_5, k1_0, k1_0, k1_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k0_5));
  EXPECT_CALL(*this, OperatorSubscript(kIndex4)).WillRepeatedly(ReturnRef(k0_5));
  EXPECT_CALL(*this, OperatorSubscript(kIndex5)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex6)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex7)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(8));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, FindSpanMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(KnotSpan{4}));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_5, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt0_5)).WillRepeatedly(Return(kMultiplicity3));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt0_5)).WillRepeatedly(Return(kUniqueKnots3_8));

  EXPECT_CALL(*this, RemoveMock(k0_5, kMultiplicity_, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(DoAll(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExe3_8_0), Return(kMultiplicity_)));
  EXPECT_CALL(*this, RemoveMock(k0_5, kMultiplicity2, IsGe0_0AndLt0_5)).Times(AtMost(1))
      .WillOnce(DoAll(InvokeWithoutArgs(this, &AKnotVectorMock::NurbsBookExa2_1), Return(kMultiplicity2)));
}

void AKnotVectorMock::NurbsBookExe4_4() {
  knots_.assign({k0_0, k0_0, k1_0, k1_0});

  EXPECT_CALL(*this, OperatorSubscript(kIndex0)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex1)).WillRepeatedly(ReturnRef(k0_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex2)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, OperatorSubscript(kIndex3)).WillRepeatedly(ReturnRef(k1_0));
  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(4));

  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(false));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k0_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DoesParametricCoordinateEqualFrontOrBackMock(k1_0, Ge(0.0))).WillRepeatedly(Return(true));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k0_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, DetermineMultiplicityMock(k1_0, IsGe0_0AndLt1_0)).WillRepeatedly(Return(kMultiplicity2));
  EXPECT_CALL(*this, GetUniqueKnotsMock(IsGe0_0AndLt0_5)).WillRepeatedly(Return(kUniqueKnots2_1));

  EXPECT_CALL(*this, DecreaseMultiplicitiesMock(kMultiplicity0, IsGe0_0AndLt0_5)).Times(AtMost(1));

  EXPECT_CALL(*this, WriteMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{kZero, kZero, kOne, kOne}));
}

void AKnotVectorMock::NurbsBookExe4_4Perturbed() {
  knots_.assign({k0_0, k0_0, k1_0Perturbed, k1_0});

  EXPECT_CALL(*this, GetSize).WillRepeatedly(Return(4));
}

namespace mock_knot_vectors {

namespace {

using KnotVector = testing::StrictMock<AKnotVectorMock>;
using std::make_shared;

}  // namespace

KnotVectors Empty() {
  SharedPointer<KnotVector> knot_vector{make_shared<KnotVector>()};
  return KnotVectors{knot_vector, knot_vector};
}

KnotVectors NurbsBookExa2_2() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExa2_2();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExa2_1();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExa2_2IncreasedOnce() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExa2_2IncreasedOnce();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExa2_1();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExa2_2IncreasedTwice() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExa2_2IncreasedTwice();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExa2_1();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExa2_2Inserted() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExa2_2();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExe3_8_0();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExa2_2Subdivided() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExa2_2();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExe3_8_0Subdivided();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExe3_8() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExe3_8_0();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExa2_1();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExe3_8IncreaseDecrease() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExe3_8_0IncreaseDecrease();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExa2_1();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExe3_8IncreasedTwice() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExe3_8_0IncreasedTwice();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExa2_1();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExe3_8InsertRemove() {
  SharedPointer<KnotVector> knot_vector{make_shared<KnotVector>()}; knot_vector->NurbsBookExe3_8_0();
  return KnotVectors{knot_vector, knot_vector};
}

KnotVectors NurbsBookExe3_8Perturbed() {
  SharedPointer<KnotVector> knot_vector0 = make_shared<KnotVector>(); knot_vector0->NurbsBookExe3_8_0();
  SharedPointer<KnotVector> knot_vector1 = make_shared<KnotVector>(); knot_vector1->NurbsBookExa2_1Perturbed();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExe3_8Subdivided() {
  SharedPointer<KnotVector> knot_vector0{make_shared<KnotVector>()}; knot_vector0->NurbsBookExe3_8_0();
  SharedPointer<KnotVector> knot_vector1{make_shared<KnotVector>()}; knot_vector1->NurbsBookExe3_8_0Subdivided();
  return KnotVectors{knot_vector0, knot_vector1};
}

KnotVectors NurbsBookExe4_4() {
  SharedPointer<KnotVector> knot_vector{make_shared<KnotVector>()}; knot_vector->NurbsBookExe4_4();
  return KnotVectors{knot_vector, knot_vector};
}

KnotVectors NurbsBookExe4_4Perturbed() {
  SharedPointer<KnotVector> knot_vector0 = make_shared<KnotVector>(); knot_vector0->NurbsBookExe4_4();
  SharedPointer<KnotVector> knot_vector1 = make_shared<KnotVector>(); knot_vector1->NurbsBookExe4_4Perturbed();
  return KnotVectors{knot_vector0, knot_vector1};
}

}  // namespace mock_knot_vectors

}  // namespace splinelib::tests::parameter_spaces
