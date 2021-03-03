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

#ifndef TESTS_PARAMETERSPACES_ZERO_DEGREE_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_
#define TESTS_PARAMETERSPACES_ZERO_DEGREE_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/ParameterSpaces/zero_degree_b_spline_basis_function.hpp"
#include "Tests/ParameterSpaces/b_spline_basis_function_mock.hpp"

namespace splinelib::tests::parameter_spaces {

class AZeroDegreeBSplineBasisFunctionMock : public ABSplineBasisFunctionMock,
                                            public sources::parameter_spaces::ZeroDegreeBSplineBasisFunction {
 public:
  MOCK_METHOD(Type_, Evaluate, (ParametricCoordinate const &, Tolerance_ const &), (const));
  Type_ operator()(ParametricCoordinate const &parametric_coordinate, Tolerance_ const &tolerance = kEpsilon_) const
      final;
  MOCK_METHOD(Type_, EvaluateDerivative, (ParametricCoordinate const &, Derivative const &, Tolerance_ const &),
              (const));
  Type_ operator()(ParametricCoordinate const &parametric_coordinate, Derivative const &derivative,
                   Tolerance_ const &tolerance = kEpsilon_) const final;

  // See NURBS book Exa. 2.1.s
  void NurbsBookExa2_1_1_0() final;  // N0_0(u) = N1_0(u) = 0
  void NurbsBookExa2_1_2_0() final;  // N2_0(u) = 1, u in [0,1]
  void NurbsBookExa2_1_3_0() final;  // N3_0(u) = N4_0(u) = 0

  // See NURBS book Exa. 2.2.
  void NurbsBookExa2_2_1_0() final;  // N0_0(u) = N1_0(u) = 0
  void NurbsBookExa2_2_2_0() final;  // N2_0(u) = 1, u in [0,1)
  void NurbsBookExa2_2_3_0() final;  // N3_0(u) = 1, u in [1,2)
  void NurbsBookExa2_2_4_0() final;  // N4_0(u) = 1, u in [2,3)
  void NurbsBookExa2_2ElevatedOnce_4_0() final;  // N4_0(u) = 0
  void NurbsBookExa2_2_5_0() final;  // N5_0(u) = 1, u in [3,4)
  void NurbsBookExa2_2_6_0() final;  // N6_0(u) = 0
  void NurbsBookExa2_2ElevatedOnce_6_0() final;  // N6_0(u) = 0
  void NurbsBookExa2_2_7_0() final;  // N7_0(u) = 1, u in [4,5]
  void NurbsBookExa2_2_8_0() final;  // N8_0(u) = N9_0(u) = 0
  void NurbsBookExa2_2ElevatedOnce_8_0() final;  // N8_0(u) = 0
  void NurbsBookExa2_2ElevatedOnce_11_0() final;  // N10_0(u) = N11_0(u) = 0

  // See NURBS book Exe 3.8.
  void NurbsBookExe3_8_0_1_0() final;  // N0_0(u) = N1_0(u) = 0
  void NurbsBookExe3_8_0_2_0() final;  // N2_0(u) = 1, u in [0,0.5)
  void NurbsBookExe3_8_0_3_0() final;  // N3_0(u) = 1, u in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_3_0() final;  // N3_0(u) = 0
  void NurbsBookExe3_8_0_4_0() final;  // N4_0(u) = N5_0(u) = 0
  void NurbsBookExe3_8_0Subdivided_4_0() final;  // N4_0(u) = 1 in [0.5,1]
};

}  // namespace splinelib::tests::parameter_spaces

#endif  // TESTS_PARAMETERSPACES_ZERO_DEGREE_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_
