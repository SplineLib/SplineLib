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

#include "Tests/ParameterSpaces/zero_degree_b_spline_basis_function_mock.hpp"

namespace splinelib::tests::parameter_spaces {

namespace {

using Type = AZeroDegreeBSplineBasisFunctionMock::Type_;

}  // namespace

Type AZeroDegreeBSplineBasisFunctionMock::operator()(ParametricCoordinate const &parametric_coordinate,
                                                     Tolerance_ const &tolerance) const {
  return Evaluate(parametric_coordinate, tolerance);
}

Type AZeroDegreeBSplineBasisFunctionMock::operator()(ParametricCoordinate const &parametric_coordinate,
                                                     Derivative const &derivative, Tolerance_ const &tolerance) const {
  return EvaluateDerivative(parametric_coordinate, derivative, tolerance);
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_1_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_1_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_2_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_2_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_1_3_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_1_3_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_1_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_1_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_2_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_2_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_3_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_3_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_4_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_4_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_4_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_5_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_5_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_6_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_6_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_6_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_7_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_7_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2_8_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2_8_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_8_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_11_0() {
  ABSplineBasisFunctionMock::NurbsBookExa2_2ElevatedOnce_11_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_1_0() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_1_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_2_0() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_2_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_3_0() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_3_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_3_0() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_3_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0_4_0() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0_4_0();
}

void AZeroDegreeBSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_0() {
  ABSplineBasisFunctionMock::NurbsBookExe3_8_0Subdivided_4_0();
}

}  // namespace splinelib::tests::parameter_spaces
