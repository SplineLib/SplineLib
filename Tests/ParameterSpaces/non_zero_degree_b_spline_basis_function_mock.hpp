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

#ifndef TESTS_PARAMETERSPACES_NON_ZERO_DEGREE_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_
#define TESTS_PARAMETERSPACES_NON_ZERO_DEGREE_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/ParameterSpaces/non_zero_degree_b_spline_basis_function.hpp"
#include "Tests/ParameterSpaces/b_spline_basis_function_mock.hpp"

namespace splinelib::tests::parameter_spaces {

class ANonZeroDegreeBSplineBasisFunctionMock : public ABSplineBasisFunctionMock,
                                               public sources::parameter_spaces::NonZeroDegreeBSplineBasisFunction {
 public:
  MOCK_METHOD(Type_, Evaluate, (ParametricCoordinate const &, Tolerance_ const &), (const));
  Type_ operator()(ParametricCoordinate const &parametric_coordinate, Tolerance_ const &tolerance = kEpsilon_) const
      final;
  MOCK_METHOD(Type_, EvaluateDerivative, (ParametricCoordinate const &, Derivative const &, Tolerance_ const &),
              (const));
  Type_ operator()(ParametricCoordinate const &parametric_coordinate, Derivative const &derivative,
                   Tolerance_ const &tolerance = kEpsilon_) const final;

  // See NURBS book Exa. 2.1.
  void NurbsBookExa2_1_0_1() final;  // N0_1(u) = 0
  void NurbsBookExa2_1_1_1() final;  // N1_1(u) = 1-u in [0,1]
  void NurbsBookExa2_1_2_1() final;  // N2_1(u) = u in [0,1]
  void NurbsBookExa2_1_3_1() final;  // N3_1(u) = 0

  void NurbsBookExa2_1_0_2() final;  // N0_2(u) = (1-u)^2 in [0,1]
  void NurbsBookExa2_1_1_2() final;  // N1_2(u) = 2u-2u^2 in [0,1]
  void NurbsBookExa2_1_2_2() final;  // N2_2(u) = u^2 in [0,1]

  // See NURBS book Exa. 2.2.
  void NurbsBookExa2_2_0_1() final;  // N0_1(u) = 0
  void NurbsBookExa2_2_1_1() final;  // N1_1(u) = 1-u in [0,1)
  void NurbsBookExa2_2_2_1() final;  // N2_1(u) = u in [0,1); 2-u in [1,2)
  void NurbsBookExa2_2_3_1() final;  // N3_1(u) = u-1 in [1,2); 3-u in [2,3)
  void NurbsBookExa2_2ElevatedOnce_3_1();  // N3_1(u) = u in [0,1)
  void NurbsBookExa2_2_4_1() final;  // N4_1(u) = u-2 in [2,3); 4-u in [3,4)
  void NurbsBookExa2_2ElevatedOnce_4_1() final;  // N4_1(u) = 2-u in [1,2)
  void NurbsBookExa2_2_5_1() final;  // N5_1(u) = u-3 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_5_1();  // N5_1(u) = u-1 in [1,2)
  void NurbsBookExa2_2_6_1() final;  // N6_1(u) = 5-u in [4,5]
  void NurbsBookExa2_2ElevatedOnce_6_1() final;  // N6_1(u) = 3-u in [2,3)
  void NurbsBookExa2_2_7_1() final;  // N7_1(u) = u-4 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_7_1();  // N7_1(u) = u-2 in [2,3)
  void NurbsBookExa2_2_8_1() final;  // N8_1(u) = 0
  void NurbsBookExa2_2ElevatedOnce_8_1() final;  // N8_1(u) = 4-u in [3,4)
  void NurbsBookExa2_2ElevatedOnce_9_1();  // N9_1(u) = u-3 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_10_1() final;  // N10_1(u) = 0
  void NurbsBookExa2_2ElevatedOnce_11_1();  // N11_1(u) = 5-u in [4,5]
  void NurbsBookExa2_2ElevatedOnce_12_1();  // N12_1(u) = u-4 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_13_1();  // N13_1(u) = N14_1(u) = 0

  void NurbsBookExa2_2_0_2() final;  // N0_2(u) = (1-u)^2 in [0,1)
  void NurbsBookExa2_2ElevatedOnce_0_2() final;  // N0_2(u) = 0
  void NurbsBookExa2_2_1_2() final;  // N1_2(u) = 2u-3u^2/2 in [0,1); (2-u)^2/2 in [1,2)
  void NurbsBookExa2_2ElevatedOnce_1_2();  // N1_2(u) = (1-u)^2 in [0,1)
  void NurbsBookExa2_2_2_2() final;  // N2_2(u) = u^2/2 in [0,1); -3/2+3u-u^2 in [1,2); (3-u)^2/2 in [2,3)
  void NurbsBookExa2_2ElevatedOnce_2_2();  // N2_2(u) = 2(u-u^2) in [0,1)
  void NurbsBookExa2_2_3_2() final;  // N3_2(u) = (u-1)^2/2 in [1,2); -11/2+5u-u^2 in [2,3); (4-u)^2/2 in [2,3)
  void NurbsBookExa2_2ElevatedOnce_3_2();  // N3_2(u) = u^2 in [0,1); (2-u)^2 in [1,2)
  void NurbsBookExa2_2_4_2() final;  // N4_2(u) = (u-2)^2/2 in [2,3); -16+10u-3u^2/2 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_4_2() final;  // N4_2(u) = 6u-2u^2-4 in [1,2)
  void NurbsBookExa2_2_5_2() final;  // N5_2(u) = (u-3)^2 in [3,4); (5-u)^2 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_5_2() final;  // N5_2(u) = (u-1)^2 in [1,2); (3-u)^2 in [2,3)
  void NurbsBookExa2_2_6_2() final;  // N6_2(u) = 2(u-4)(5-u), u in [4,5]
  void NurbsBookExa2_2ElevatedOnce_6_2() final;  // N6_2(u) = (10u-2u^2-12) in [2,3)
  void NurbsBookExa2_2_7_2() final;  // N7_2(u) = (u-4)^2 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_7_2();  // N7_2(u) = (u-2)^2 in [2,3); (4-u)^2 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_8_2() final;  // N8_2(u) = 14u-2u^2-24 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_9_2();  // N9_2(u) = (u-3)^2 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_10_2();  // N10_2(u) = (5-u)^2 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_11_2();  // N11_2(u) = 18u-2u^2-40 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_12_2();  // N12_2(u) = (u-4)^2 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_13_2() final;  // N13_2(u) = 0

  void NurbsBookExa2_2ElevatedOnce_0_3() final;  // N0_3(u) = (1-u)^3 in [0,1)
  void NurbsBookExa2_2ElevatedOnce_1_3();  // N1_3(u) = 3(u^3-2u^2+u) in [0,1)
  void NurbsBookExa2_2ElevatedOnce_2_3() final;  // N2_3(u) = 3u^2-5/2u^3 in [0,1); (2-u)^3/2 in [1,2)
  void NurbsBookExa2_2ElevatedOnce_3_3();  // N3_3(u) = u^3/2 in [0,1); 5u^3/2-12u^2+18u-8 in [1,2)
  void NurbsBookExa2_2ElevatedOnce_4_3() final;  // N4_3(u) = 21u^2/2-5u^3/2-27/2u+11/2 in [1,2); (3-u)^3/2 in [2,3)
  void NurbsBookExa2_2ElevatedOnce_5_3();  // N5_3(u) = (u-1)^3/2 in [1,2); 5u^3/2-39u^2/2+99u/2-81/2 in [2,3)
  void NurbsBookExa2_2ElevatedOnce_6_3() final;  // N6_3(u) = 18u^2-5u^3/2-42u+32 in [2,3); (4-u)^3/2 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_7_3();  // N7_3(u) = (u-2)^3/2 in [2,3); 5u^3/2-27u^2+96u-112 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_8_3() final;  // N8_3(u) = 30u^2-3u^3-99u+108 in [3,4)
  void NurbsBookExa2_2ElevatedOnce_9_3() final;  // N9_3(u) = (u-3)^3 in [3,4); (5-u)^3 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_10_3() final;  // N10_3(u) = 3u^3-42u^2+195u-300 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_11_3();  // N11_3(u) = 39u^2-3u^3-168u+240 in [4,5]
  void NurbsBookExa2_2ElevatedOnce_12_3();  // N12_3(u) = (u-4)^3 in [4,5]

  // See NURBS book Exe. 3.8.
  void NurbsBookExe3_8_0_0_1() final;  // N0_1(u) = 0
  void NurbsBookExe3_8_0_1_1() final;  // N1_1(u) = 1-2u in [0,0.5)
  void NurbsBookExe3_8_0_2_1() final;  // N2_1(u) = 2u in [0,0.5); 2(1-u), u in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_2_1() final;  // N2_1(u) = 2u in [0,0.5)
  void NurbsBookExe3_8_0_3_1() final;  // N3_1(u) = 2u-1 in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_3_1();  // N3_1(u) = 2(1-u) in [0.5,1]
  void NurbsBookExe3_8_0_4_1() final;  // N4_1(u) = 0
  void NurbsBookExe3_8_0Subdivided_4_1() final;  // N4_1(u) = 2u-1 in [0.5,1]

  void NurbsBookExe3_8_0_0_2() final;  // N0_2(u) = (1-2u)^2 in [0,0.5)
  void NurbsBookExe3_8_0_1_2() final;  // N1_2(u) = 4u-6u^2 in [0,0.5); 2(1-u)^2 in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_1_2() final;  // N1_2(u) = 4u-8u^2 in [0,0.5)
  void NurbsBookExe3_8_0_2_2() final;  // N2_2(u) = 2u^2 in [0,0.5); -2+8u-6u^2 in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_2_2();  // N2_2(u) = 4u^2 in [0,0.5); 4(1-u)^2 in [0.5,1]
  void NurbsBookExe3_8_0_3_2() final;  // N3_2(u) = (2u-1)^2 ,u in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_3_2();  // N3_2(u) = 2(2u-1)(2-2u) in [0.5,1]
  void NurbsBookExe3_8_0Subdivided_4_2();  // N4_2(u) = (2u-1)^2 in [0.5,1]

 private:
  void SetLeftAndRightQuotientDerivative();
};

}  // namespace splinelib::tests::parameter_spaces

#endif  // TESTS_PARAMETERSPACES_NON_ZERO_DEGREE_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_
