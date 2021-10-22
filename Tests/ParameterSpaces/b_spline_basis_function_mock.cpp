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

#include "Tests/ParameterSpaces/b_spline_basis_function_mock.hpp"

#include "Sources/Utilities/std_container_operations.hpp"
#include "Tests/ParameterSpaces/non_zero_degree_b_spline_basis_function_mock.hpp"

namespace splinelib::tests::parameter_spaces {

namespace {

constexpr Degree const kDegree0{}, kDegree1{1}, kDegree2{2}, kDegree3{3};
constexpr ParametricCoordinate const k0_0{}, k0_5{0.5}, k1_0{1.0}, k2_0{2.0}, k3_0{3.0}, k4_0{4.0}, k5_0{5.0};

}  // namespace

void ABSplineBasisFunctionMock::NurbsBookExa2_1_1_0() {
  degree_ = kDegree0; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_2_0() {
  degree_ = kDegree0; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_3_0() {
  degree_ = kDegree0; start_knot_ = k1_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_0_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_1_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_2_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_3_1() {
  degree_ = kDegree1; start_knot_ = k1_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_0_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_1_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_1_2_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_1_0() {
  degree_ = kDegree0; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_2_0() {
  degree_ = kDegree0; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_3_0() {
  degree_ = kDegree0; start_knot_ = k1_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_4_0() {
  degree_ = kDegree0; start_knot_ = k2_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_0() {
  degree_ = kDegree0; start_knot_ = k1_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_5_0() {
  degree_ = kDegree0; start_knot_ = k3_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}


void ABSplineBasisFunctionMock::NurbsBookExa2_2_6_0() {
  degree_ = kDegree0; start_knot_ = k4_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_0() {
  degree_ = kDegree0; start_knot_ = k2_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_7_0() {
  degree_ = kDegree0; start_knot_ = k4_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_8_0() {
  degree_ = kDegree0; start_knot_ = k5_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_0() {
  degree_ = kDegree0; start_knot_ = k3_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_11_0() {
  degree_ = kDegree0; start_knot_ = k4_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_0_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_1_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_2_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_3_1() {
  degree_ = kDegree1; start_knot_ = k1_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_4_1() {
  degree_ = kDegree1; start_knot_ = k2_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_1() {
  degree_ = kDegree1; start_knot_ = k1_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_5_1() {
  degree_ = kDegree1; start_knot_ = k3_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_6_1() {
  degree_ = kDegree1; start_knot_ = k4_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_1() {
  degree_ = kDegree1; start_knot_ = k2_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_7_1() {
  degree_ = kDegree1; start_knot_ = k4_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_8_1() {
  degree_ = kDegree1; start_knot_ = k5_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_1() {
  degree_ = kDegree1; start_knot_ = k3_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_1() {
  degree_ = kDegree1; start_knot_ = k4_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_0_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_1_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_2_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_3_2() {
  degree_ = kDegree2; start_knot_ = k1_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_4_2() {
  degree_ = kDegree2; start_knot_ = k2_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_2() {
  degree_ = kDegree2; start_knot_ = k1_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_5_2() {
  degree_ = kDegree2; start_knot_ = k3_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_5_2() {
  degree_ = kDegree2; start_knot_ = k1_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_6_2() {
  degree_ = kDegree2; start_knot_ = k4_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_2() {
  degree_ = kDegree2; start_knot_ = k2_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2_7_2() {
  degree_ = kDegree2; start_knot_ = k4_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_2() {
  degree_ = kDegree2; start_knot_ = k3_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_13_2() {
  degree_ = kDegree2; start_knot_ = k5_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_0_3() {
  degree_ = kDegree3; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_2_3() {
  degree_ = kDegree3; start_knot_ = k0_0; end_knot_ = k2_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_3() {
  degree_ = kDegree3; start_knot_ = k1_0; end_knot_ = k3_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_3() {
  degree_ = kDegree3; start_knot_ = k2_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_3() {
  degree_ = kDegree3; start_knot_ = k3_0; end_knot_ = k4_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_9_3() {
  degree_ = kDegree3; start_knot_ = k3_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_10_3() {
  degree_ = kDegree3; start_knot_ = k4_0; end_knot_ = k5_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_1_0() {
  degree_ = kDegree0; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_0() {
  degree_ = kDegree0; start_knot_ = k0_0; end_knot_ = k0_5; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_0() {
  degree_ = kDegree0; start_knot_ = k0_5; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_3_0() {
  degree_ = kDegree0; start_knot_ = k0_5; end_knot_ = k0_5; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_4_0() {
  degree_ = kDegree0; start_knot_ = k1_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_0() {
  degree_ = kDegree0; start_knot_ = k0_5; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_0_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k0_0; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_1_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k0_5; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_2_1() {
  degree_ = kDegree1; start_knot_ = k0_0; end_knot_ = k0_5; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_1() {
  degree_ = kDegree1; start_knot_ = k0_5; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_4_1() {
  degree_ = kDegree1; start_knot_ = k1_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_1() {
  degree_ = kDegree1; start_knot_ = k0_5; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_0_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k0_5; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_1_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_1_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k0_5; end_knot_equals_last_knot_ = false;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_2() {
  degree_ = kDegree2; start_knot_ = k0_0; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

void ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_2() {
  degree_ = kDegree2; start_knot_ = k0_5; end_knot_ = k1_0; end_knot_equals_last_knot_ = true;
}

namespace mock_b_spline_basis_functions {

namespace {

using BSplineBasisFunctionsDimension = typename BSplineBasisFunctions::value_type;
using NonZeroDegreeBSplineBasisFunction = testing::StrictMock<ANonZeroDegreeBSplineBasisFunctionMock>;
using std::make_shared;

}  // namespace

BSplineBasisFunctions Empty() {
  return BSplineBasisFunctions{{{}, {}}};
}

BSplineBasisFunctions NurbsBookExa2_2() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_0_2->NurbsBookExa2_2_0_2(); basis_functions_0.push_back(basis_function0_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_1_2->NurbsBookExa2_2_1_2(); basis_functions_0.push_back(basis_function0_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_2_2->NurbsBookExa2_2_2_2(); basis_functions_0.push_back(basis_function0_2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_3_2->NurbsBookExa2_2_3_2(); basis_functions_0.push_back(basis_function0_3_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_4_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_4_2->NurbsBookExa2_2_4_2(); basis_functions_0.push_back(basis_function0_4_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_5_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_5_2->NurbsBookExa2_2_5_2(); basis_functions_0.push_back(basis_function0_5_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_6_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_6_2->NurbsBookExa2_2_6_2(); basis_functions_0.push_back(basis_function0_6_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_7_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_7_2->NurbsBookExa2_2_7_2(); basis_functions_0.push_back(basis_function0_7_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_0_2->NurbsBookExa2_1_0_2(); basis_functions_1.push_back(basis_function1_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_1_2->NurbsBookExa2_1_1_2(); basis_functions_1.push_back(basis_function1_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_2_2->NurbsBookExa2_1_2_2(); basis_functions_1.push_back(basis_function1_2_2);
  return basis_functions;
}

BSplineBasisFunctions NurbsBookExa2_2ElevatedOnce() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_0_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_0_3->NurbsBookExa2_2ElevatedOnce_0_3(); basis_functions_0.push_back(basis_function0_0_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_1_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_1_3->NurbsBookExa2_2ElevatedOnce_1_3(); basis_functions_0.push_back(basis_function0_1_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_2_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_2_3->NurbsBookExa2_2ElevatedOnce_2_3(); basis_functions_0.push_back(basis_function0_2_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_3_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_3_3->NurbsBookExa2_2ElevatedOnce_3_3(); basis_functions_0.push_back(basis_function0_3_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_4_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_4_3->NurbsBookExa2_2ElevatedOnce_4_3(); basis_functions_0.push_back(basis_function0_4_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_5_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_5_3->NurbsBookExa2_2ElevatedOnce_5_3(); basis_functions_0.push_back(basis_function0_5_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_6_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_6_3->NurbsBookExa2_2ElevatedOnce_6_3(); basis_functions_0.push_back(basis_function0_6_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_7_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_7_3->NurbsBookExa2_2ElevatedOnce_7_3(); basis_functions_0.push_back(basis_function0_7_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_8_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_8_3->NurbsBookExa2_2ElevatedOnce_8_3(); basis_functions_0.push_back(basis_function0_8_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_9_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_9_3->NurbsBookExa2_2ElevatedOnce_9_3(); basis_functions_0.push_back(basis_function0_9_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_10_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_10_3->NurbsBookExa2_2ElevatedOnce_10_3(); basis_functions_0.push_back(basis_function0_10_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_11_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_11_3->NurbsBookExa2_2ElevatedOnce_11_3(); basis_functions_0.push_back(basis_function0_11_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_12_3{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_12_3->NurbsBookExa2_2ElevatedOnce_12_3(); basis_functions_0.push_back(basis_function0_12_3);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_0_2->NurbsBookExa2_1_0_2(); basis_functions_1.push_back(basis_function1_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_1_2->NurbsBookExa2_1_1_2(); basis_functions_1.push_back(basis_function1_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_2_2->NurbsBookExa2_1_2_2(); basis_functions_1.push_back(basis_function1_2_2);
  return basis_functions;
}

BSplineBasisFunctions NurbsBookExa2_2Inserted() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_0_2->NurbsBookExa2_2_0_2(); basis_functions_0.push_back(basis_function0_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_1_2->NurbsBookExa2_2_1_2(); basis_functions_0.push_back(basis_function0_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_2_2->NurbsBookExa2_2_2_2(); basis_functions_0.push_back(basis_function0_2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_3_2->NurbsBookExa2_2_3_2(); basis_functions_0.push_back(basis_function0_3_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_4_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_4_2->NurbsBookExa2_2_4_2(); basis_functions_0.push_back(basis_function0_4_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_5_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_5_2->NurbsBookExa2_2_5_2(); basis_functions_0.push_back(basis_function0_5_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_6_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_6_2->NurbsBookExa2_2_6_2(); basis_functions_0.push_back(basis_function0_6_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_7_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_7_2->NurbsBookExa2_2_7_2(); basis_functions_0.push_back(basis_function0_7_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_0_2->NurbsBookExe3_8_0_0_2(); basis_functions_1.push_back(basis_function1_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_1_2->NurbsBookExe3_8_0_1_2(); basis_functions_1.push_back(basis_function1_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_2_2->NurbsBookExe3_8_0_2_2(); basis_functions_1.push_back(basis_function1_2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_3_2->NurbsBookExe3_8_0_3_2(); basis_functions_1.push_back(basis_function1_3_2);
  return basis_functions;
}

BSplineBasisFunctions NurbsBookExa2_2Subdivided() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_0_2->NurbsBookExa2_2_0_2(); basis_functions_0.push_back(basis_function0_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_1_2->NurbsBookExa2_2_1_2(); basis_functions_0.push_back(basis_function0_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_2_2->NurbsBookExa2_2_2_2(); basis_functions_0.push_back(basis_function0_2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_3_2->NurbsBookExa2_2_3_2(); basis_functions_0.push_back(basis_function0_3_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_4_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_4_2->NurbsBookExa2_2_4_2(); basis_functions_0.push_back(basis_function0_4_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_5_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_5_2->NurbsBookExa2_2_5_2(); basis_functions_0.push_back(basis_function0_5_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_6_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_6_2->NurbsBookExa2_2_6_2(); basis_functions_0.push_back(basis_function0_6_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_7_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_7_2->NurbsBookExa2_2_7_2(); basis_functions_0.push_back(basis_function0_7_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_0_2->NurbsBookExe3_8_0_0_2(); basis_functions_1.push_back(basis_function1_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_1_2->NurbsBookExe3_8_0Subdivided_1_2(); basis_functions_1.push_back(basis_function1_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_2_2->NurbsBookExe3_8_0Subdivided_2_2(); basis_functions_1.push_back(basis_function1_2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_3_2->NurbsBookExe3_8_0Subdivided_3_2(); basis_functions_1.push_back(basis_function1_3_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_4_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_4_2->NurbsBookExe3_8_0Subdivided_4_2(); basis_functions_1.push_back(basis_function1_4_2);
  return basis_functions;
}

BSplineBasisFunctions NurbsBookExe3_8() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_0_2->NurbsBookExe3_8_0_0_2(); basis_functions_0.push_back(basis_function0_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_1_2->NurbsBookExe3_8_0_1_2(); basis_functions_0.push_back(basis_function0_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_2_2->NurbsBookExe3_8_0_2_2(); basis_functions_0.push_back(basis_function0_2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_3_2->NurbsBookExe3_8_0_3_2(); basis_functions_0.push_back(basis_function0_3_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_0_2->NurbsBookExa2_1_0_2(); basis_functions_1.push_back(basis_function1_0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_1_2->NurbsBookExa2_1_1_2(); basis_functions_1.push_back(basis_function1_1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_2_2->NurbsBookExa2_1_2_2(); basis_functions_1.push_back(basis_function1_2_2);
  return basis_functions;
}

BSplineBasisFunctions NurbsBookExe3_8InsertRemove() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_2->NurbsBookExe3_8_0_0_2();
  basis_functions_0.push_back(basis_function0_2);
  basis_functions_1.push_back(basis_function0_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_2->NurbsBookExe3_8_0_1_2();
  basis_functions_0.push_back(basis_function1_2);
  basis_functions_1.push_back(basis_function1_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function2_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function2_2->NurbsBookExe3_8_0_2_2();
  basis_functions_0.push_back(basis_function2_2);
  basis_functions_1.push_back(basis_function2_2);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function3_2{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function3_2->NurbsBookExe3_8_0_3_2();
  basis_functions_0.push_back(basis_function3_2);
  basis_functions_1.push_back(basis_function3_2);
  return basis_functions;
}

BSplineBasisFunctions NurbsBookExe4_4() {
  BSplineBasisFunctions basis_functions;
  BSplineBasisFunctionsDimension &basis_functions_0 = basis_functions[0], &basis_functions_1 = basis_functions[1];
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function0_1{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function0_1->NurbsBookExa2_1_1_1();
  basis_functions_0.push_back(basis_function0_1);
  basis_functions_1.push_back(basis_function0_1);
  SharedPointer<NonZeroDegreeBSplineBasisFunction> basis_function1_1{
                                                       make_shared<NonZeroDegreeBSplineBasisFunction>()};
  basis_function1_1->NurbsBookExa2_1_2_1();
  basis_functions_0.push_back(basis_function1_1);
  basis_functions_1.push_back(basis_function1_1);
  return basis_functions;
}

}  // namespace mock_b_spline_basis_functions

}  // namespace splinelib::tests::parameter_spaces
