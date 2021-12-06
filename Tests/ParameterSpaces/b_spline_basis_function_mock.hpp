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

#ifndef TESTS_PARAMETERSPACES_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_
#define TESTS_PARAMETERSPACES_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/ParameterSpaces/b_spline_basis_function.hpp"

namespace splinelib::tests::parameter_spaces {

class ABSplineBasisFunctionMock : public virtual sources::parameter_spaces::BSplineBasisFunction {
 public:
  ~ABSplineBasisFunctionMock() override = default;

  // See NURBS book Exa 2.1.
  virtual void NurbsBookExa2_1_1_0();  // N0_0(u) = N1_0(u) = 0
  virtual void NurbsBookExa2_1_2_0();  // N2_0(u) = 1 in [0,1]
  virtual void NurbsBookExa2_1_3_0();  // N3_0(u) = N4_0(u) = 0

  virtual void NurbsBookExa2_1_0_1();  // N0_1(u) = 0
  virtual void NurbsBookExa2_1_1_1();  // N1_1(u) = 1-u in [0,1]
  virtual void NurbsBookExa2_1_2_1();  // N2_1(u) = u in [0,1]
  virtual void NurbsBookExa2_1_3_1();  // N3_1(u) = 0
  virtual void NurbsBookExa2_1_0_2();  // N0_2(u) = (1-u)^2 in [0,1]
  virtual void NurbsBookExa2_1_1_2();  // N1_2(u) = 2u-2u^2 in [0,1]
  virtual void NurbsBookExa2_1_2_2();  // N2_2(u) = u^2 in [0,1]

  // See NURBS book Exa. 2.2.
  virtual void NurbsBookExa2_2_1_0();  // N0_0(u) = N1_0(u) = 0
  virtual void NurbsBookExa2_2_2_0();  // N2_0(u) = 1 in [0,1)
  virtual void NurbsBookExa2_2_3_0();  // N3_0(u) = 1 in [1,2)
  virtual void NurbsBookExa2_2_4_0();  // N4_0(u) = 1 in [2,3)
  virtual void NurbsBookExa2_2ElevatedOnce_4_0();  // N4_0(u) = 0
  virtual void NurbsBookExa2_2_5_0();  // N5_0(u) = 1 in [3,4)
  virtual void NurbsBookExa2_2_6_0();  // N6_0(u) = 0
  virtual void NurbsBookExa2_2ElevatedOnce_6_0();  // N6_0(u) = 0
  virtual void NurbsBookExa2_2_7_0();  // N7_0(u) = 1 in [4,5]
  virtual void NurbsBookExa2_2_8_0();  // N8_0(u) = N9_0(u) = 0
  virtual void NurbsBookExa2_2ElevatedOnce_8_0();  // N8_0(u) = 0
  virtual void NurbsBookExa2_2ElevatedOnce_11_0();  // N10_0(u) = N11_0(u) = 0

  virtual void NurbsBookExa2_2_0_1();  // N0_1(u) = 0
  virtual void NurbsBookExa2_2_1_1();  // N1_1(u) = 1-u in [0,1)
  virtual void NurbsBookExa2_2_2_1();  // N2_1(u) = u in [0,1); 2-u in [1,2)
  virtual void NurbsBookExa2_2_3_1();  // N3_1(u) = u-1 in [1,2); 3-u in [2,3)
  virtual void NurbsBookExa2_2_4_1();  // N4_1(u) = u-2 in [2,3); 4-u in [3,4)
  virtual void NurbsBookExa2_2ElevatedOnce_4_1();  // N4_1(u) = 2-u in [1,2)
  virtual void NurbsBookExa2_2_5_1();  // N5_1(u) = u-3 in [3,4)
  virtual void NurbsBookExa2_2_6_1();  // N6_1(u) = 5-u in [4,5]
  virtual void NurbsBookExa2_2ElevatedOnce_6_1();  // N6_1(u) = 3-u in [2,3)
  virtual void NurbsBookExa2_2_7_1();  // N7_1(u) = u-4 in [4,5]
  virtual void NurbsBookExa2_2_8_1();  // N8_1(u) = 0
  virtual void NurbsBookExa2_2ElevatedOnce_8_1();  // N8_1(u) = 4-u in [3,4)
  virtual void NurbsBookExa2_2ElevatedOnce_10_1();  // N10_1(u) = 0
  virtual void NurbsBookExa2_2_0_2();  // N0_2(u) = (1-u)^2 in [0,1)
  virtual void NurbsBookExa2_2ElevatedOnce_0_2();  // N0_2(u) = 0
  virtual void NurbsBookExa2_2_1_2();  // N1_2(u) = 2u-3u^2/2 in [0,1); (2-u)^2/2 in [1,2)
  virtual void NurbsBookExa2_2_2_2();  // N2_2(u) = u^2/2 in [0,1); -3/2+3u-u^2 in [1,2); (3-u)^2/2 in [2,3)
  virtual void NurbsBookExa2_2_3_2();  // N3_2(u) = (u-1)^2/2 in [1,2); -11/2+5u-u^2 in [2,3); (4-u)^2/2 in [3,4)
  virtual void NurbsBookExa2_2_4_2();  // N4_2(u) = (u-2)^2/2 in [2,3); -16+10u-3u^2/2 in [3,4)
  virtual void NurbsBookExa2_2ElevatedOnce_4_2();  // N4_2(u) = 6u-2u^2-4 in [1,2)
  virtual void NurbsBookExa2_2_5_2();  // N5_2(u) = (u-3)^2 in [3,4); (5-u)^2 in [4,5]
  virtual void NurbsBookExa2_2ElevatedOnce_5_2();  // N5_2(u) = (u-1)^2 in [1,2); (3-u)^2 in [2,3)
  virtual void NurbsBookExa2_2_6_2();  // N6_2(u) = 2(u-4)(5-u), u in [4,5]
  virtual void NurbsBookExa2_2ElevatedOnce_6_2();  // N6_2(u) = (10u-2u^2-12) in [2,3)
  virtual void NurbsBookExa2_2_7_2();  // N7_2(u) = (u-4)^2 in [4,5]
  virtual void NurbsBookExa2_2ElevatedOnce_8_2();  // N8_2(u) = 14u-2u^2-24 in [3,4)
  virtual void NurbsBookExa2_2ElevatedOnce_13_2();  // N13_2(u) = 0
  virtual void NurbsBookExa2_2ElevatedOnce_0_3();  // N0_3(u) = (1-u)^3 in [0,1)
  virtual void NurbsBookExa2_2ElevatedOnce_2_3();  // N2_3(u) = 3u^2-5/2u^3 in [0,1); (2-u)^3/2 in [1,2)
  virtual void NurbsBookExa2_2ElevatedOnce_4_3();  // N4_3(u) = 21u^2/2-5u^3/2-27/2u+11/2 in [1,2); (3-u)^3/2 in [2,3)
  virtual void NurbsBookExa2_2ElevatedOnce_6_3();  // N6_3(u) = 18u^2-5u^3/2-42u+32 in [2,3); (4-u)^3/2 in [3,4)
  virtual void NurbsBookExa2_2ElevatedOnce_8_3();  // N8_3(u) = 30u^2-3u^3-99u+108 in [3,4)
  virtual void NurbsBookExa2_2ElevatedOnce_9_3();  // N9_3(u) = (u-3)^3 in [3,4); (5-u)^3 in [4,5]
  virtual void NurbsBookExa2_2ElevatedOnce_10_3();  // N10_3(u) = 3u^3-42u^2+195u-300 in [4,5]

  // See NURBS book Exe 3.8.
  virtual void NurbsBookExe3_8_0_1_0();  // N0_0(u) = N1_0(u) = 0
  virtual void NurbsBookExe3_8_0_2_0();  // N2_0(u) = 1 in [0,0.5)
  virtual void NurbsBookExe3_8_0_3_0();  // N3_0(u) = 1 in [0.5,1]
  virtual void NurbsBookExe3_8_0Subdivided_3_0();  // N3_0(u) = 0
  virtual void NurbsBookExe3_8_0_4_0();  // N4_0(u) = N5_0(u) = 0
  virtual void NurbsBookExe3_8_0Subdivided_4_0();  // N4_0(u) = 1 in [0.5,1]

  virtual void NurbsBookExe3_8_0_0_1();  // N0_1(u) = 0
  virtual void NurbsBookExe3_8_0_1_1();  // N1_1(u) = 1-2u in [0,0.5)
  virtual void NurbsBookExe3_8_0_2_1();  // N2_1(u) = 2u in [0,0.5); 2(1-u), u in [0.5,1]
  virtual void NurbsBookExe3_8_0Subdivided_2_1();  // N2_1(u) = 2u in [0,0.5)
  virtual void NurbsBookExe3_8_0_3_1();  // N3_1(u) = 2u-1 in [0.5,1]
  virtual void NurbsBookExe3_8_0_4_1();  // N4_1(u) = 0
  virtual void NurbsBookExe3_8_0Subdivided_4_1();  // N4_1(u) = 2u-1 in [0.5,1]
  virtual void NurbsBookExe3_8_0_0_2();  // N0_2(u) = (1-2u)^2 in [0,0.5)
  virtual void NurbsBookExe3_8_0_1_2();  // N1_2(u) = 4u-6u^2 in [0,0.5); 2(1-u)^2 in [0.5,1]
  virtual void NurbsBookExe3_8_0Subdivided_1_2();  // N1_2(u) = 2u-4u^2 in [0,0.5)
  virtual void NurbsBookExe3_8_0_2_2();  // N2_2(u) = 2u^2 in [0,0.5); -2+8u-6u^2 in [0.5,1]
  virtual void NurbsBookExe3_8_0_3_2();  // N3_2(u) = (2u-1)^2 in [0.5,1]

 protected:
  using Tolerance_ = sources::parameter_spaces::Tolerance;

  constexpr static Tolerance_ const kEpsilon_ = sources::parameter_spaces::kEpsilon;
};

namespace mock_b_spline_basis_functions {

using BSplineBasisFunctions = sources::parameter_spaces::BSplineBasisFunctions<2>;

BSplineBasisFunctions Empty();
BSplineBasisFunctions NurbsBookExa2_2();
BSplineBasisFunctions NurbsBookExa2_2ElevatedOnce();
BSplineBasisFunctions NurbsBookExa2_2Inserted();
BSplineBasisFunctions NurbsBookExa2_2Subdivided();
BSplineBasisFunctions NurbsBookExe3_8();
BSplineBasisFunctions NurbsBookExe3_8InsertRemove();
BSplineBasisFunctions NurbsBookExe4_4();

}  // namespace mock_b_spline_basis_functions

}  // namespace splinelib::tests::parameter_spaces

#endif  // TESTS_PARAMETERSPACES_B_SPLINE_BASIS_FUNCTION_MOCK_HPP_
