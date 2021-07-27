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

#include "Tests/ParameterSpaces/non_zero_degree_b_spline_basis_function_mock.hpp"

#include "Sources/Utilities/std_container_operations.hpp"
#include "Tests/ParameterSpaces/zero_degree_b_spline_basis_function_mock.hpp"

namespace splinelib::tests::parameter_spaces {

namespace {

using testing::StrictMock;
using NonZeroDegreeBSplineBasisFunction_ = StrictMock<ANonZeroDegreeBSplineBasisFunctionMock>;
using ZeroDegreeBSplineBasisFunction_ = StrictMock<AZeroDegreeBSplineBasisFunctionMock>;
using Type = NonZeroDegreeBSplineBasisFunction_::Type_;
using std::make_shared, testing::Ge, testing::Return;

constexpr Type const kMinus1_0{-1.0}, k0_0{}, k0_5{0.5}, k1_0{1.0}, k2_0{2.0};
constexpr Derivative const kDerivative0{}, kDerivative1{1};

}  // namespace

Type ANonZeroDegreeBSplineBasisFunctionMock::operator()(ParametricCoordinate const &parametric_coordinate,
                                                        Tolerance_ const &tolerance) const {
  return Evaluate(parametric_coordinate, tolerance);
}

Type ANonZeroDegreeBSplineBasisFunctionMock::operator()(ParametricCoordinate const &parametric_coordinate,
    Derivative const &derivative, Tolerance_ const &tolerance) const {
  return EvaluateDerivative(parametric_coordinate, derivative, tolerance);
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_0_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_0_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_1_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_1_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_1_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_1_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_1_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_2_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_2_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_2_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_2_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_3_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_3_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_3_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_3_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_3_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_0_2() {
  constexpr ParametricCoordinate const kParametricCoordinate0_5{0.5};
  constexpr Type_ const k0_25{0.25};

  ABSplineBasisFunctionMock::NurbsBookExa2_1_0_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_0_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_1_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;

  EXPECT_CALL(*this, Evaluate(kParametricCoordinate0_5, Ge(0.0))).WillRepeatedly(Return(k0_25));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate0_5, kDerivative0, Ge(0.0))).WillRepeatedly(Return(k0_25));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate0_5, kDerivative1, Ge(0.0)))
      .WillRepeatedly(Return(kMinus1_0));
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_1_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_1_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_1_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_2_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_2_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_2_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_1_2_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_1_3_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_0_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_0_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_1_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_1_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_1_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_1_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_1_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_2_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_2_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_2_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_2_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_3_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_3_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_3_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_3_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_3_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_1_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_2_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_4_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_4_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_4_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_5_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_4_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_3_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_5_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_5_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_5_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_6_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_5_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_3_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_6_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_6_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_6_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_6_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_7_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_6_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_7_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_7_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_8_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_7_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_4_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_8_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_8_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_8_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_8_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_8_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_8_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_5_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_9_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_5_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_11_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_7_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_12_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_1();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_7_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_8_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_13_1() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_8_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_8_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_8_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_0_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_0_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_0_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_1_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_0_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_0_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_1_2() {
  constexpr ParametricCoordinate const kParametricCoordinate1_0{1.0};

  ABSplineBasisFunctionMock::NurbsBookExa2_2_1_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_5; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_1_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_2_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;

  EXPECT_CALL(*this, Evaluate(kParametricCoordinate1_0, Ge(0.0))).WillRepeatedly(Return(k0_5));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate1_0, kDerivative0, Ge(0.0))).WillRepeatedly(Return(k0_5));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate1_0, kDerivative1, Ge(0.0)))
      .WillRepeatedly(Return(kMinus1_0));
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_1_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_0_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_0_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_2_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_2_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_2_2();
  left_denominator_inverse_ = k0_5; right_denominator_inverse_ = k0_5; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_2_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_3_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_2_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_0_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_2_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_3_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_3_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_3_2();
  left_denominator_inverse_ = k0_5; right_denominator_inverse_ = k0_5; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_3_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_4_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_3_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_1_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_3_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_4_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_4_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_4_2();
  left_denominator_inverse_ = k0_5; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_4_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_5_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_4_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_5_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_5_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_5_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_5_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_6_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_5_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_5_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_5_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_6_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_6_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_6_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_6_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_7_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_6_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_7_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_7_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2_7_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2_8_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_7_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_4_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_7_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_8_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_8_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_9_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_9_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_9_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_10_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_10_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_11_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_12_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_12_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_12_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_13_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_13_2() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_13_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_13_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_13_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_3();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_0_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_1_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_1_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_1_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_2_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_2_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_2_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_5; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_2_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_3_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_3_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_2_3();
  left_denominator_inverse_ = k0_5; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_3_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_4_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_5; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_4_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_5_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_5_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_3();
  left_denominator_inverse_ = k0_5; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_5_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_6_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_5; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_6_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_7_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_7_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_3();
  left_denominator_inverse_ = k0_5; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_7_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_8_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_8_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_9_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_9_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_9_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_9_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_10_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_10_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_11_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_11_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_12_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_12_3() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_3();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_12_2();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExa2_2ElevatedOnce_13_2();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_0_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_0_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_1_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_1_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}
void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_1_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_1_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_1_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_2_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_2_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_1();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_2_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_3_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_2_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_2_1();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_2_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_3_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_3_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_1();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_3_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_3_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_3_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_4_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_4_1();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_4_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_1() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_1();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<ZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_4_0();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<ZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                     make_shared<ZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_4_0();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_0_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_0_2();
  left_denominator_inverse_ = k0_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_0_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_1_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_1_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_1_2();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k1_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_1_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_2_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_1_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_1_2();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_1_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_2_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_2_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_2();
  left_denominator_inverse_ = k1_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_2_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_3_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_2_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_2();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_2_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_3_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_3_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_2();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0_3_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_4_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_3_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_2();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k2_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_3_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_4_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_2() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_2();
  left_denominator_inverse_ = k2_0; right_denominator_inverse_ = k0_0; SetLeftAndRightQuotientDerivative();
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> left_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  left_lower_degree_basis_function->NurbsBookExe3_8_0Subdivided_4_1();
  left_lower_degree_basis_function_ = left_lower_degree_basis_function;
  SharedPointer<NonZeroDegreeBSplineBasisFunction_> right_lower_degree_basis_function{
                                                        make_shared<NonZeroDegreeBSplineBasisFunction_>()};
  right_lower_degree_basis_function->NurbsBookExe3_8_0_4_1();
  right_lower_degree_basis_function_ = right_lower_degree_basis_function;
}

void ANonZeroDegreeBSplineBasisFunctionMock::SetLeftAndRightQuotientDerivative() {
  Degree::Type_ const &degree_value = degree_.Get();
  left_quotient_derivative_ = (degree_value * left_denominator_inverse_);
  right_quotient_derivative_ = (degree_value * right_denominator_inverse_);
}

}  // namespace splinelib::tests::parameter_spaces
