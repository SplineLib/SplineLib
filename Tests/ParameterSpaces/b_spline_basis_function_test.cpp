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
#include "Sources/ParameterSpaces/b_spline_basis_function.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Tests/ParameterSpaces/knot_vector_mock.hpp"

namespace splinelib::tests::parameter_spaces::b_spline_basis_function {

using sources::parameter_spaces::BSplineBasisFunction;

// Test basis functions N_{2,0} and N_{0,2} from NURBS book Exa. 2.1.
TEST(BSplineBasisFunctionSuite, IsEqualAndOperatorEqual) {
  using KnotVector = testing::StrictMock<AKnotVectorMock>;

  constexpr Degree const kDegree0{}, kDegree2{2};
  constexpr KnotSpan const kKnotSpan0{}, kKnotSpan1{1}, kKnotSpan2{2};
  constexpr sources::parameter_spaces::Tolerance const kTolerance{1.2 * sources::parameter_spaces::kEpsilon};

  KnotVector knot_vector, knot_vector_perturbed;
  knot_vector.NurbsBookExa2_1();
  knot_vector_perturbed.NurbsBookExa2_1Perturbed();

  BSplineBasisFunction const *basis_function_2_0{}, *basis_function_0_2{};
  ASSERT_NO_THROW(basis_function_2_0 = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan2, kDegree0));
  ASSERT_NO_THROW(basis_function_0_2 = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan0, kDegree2));

  BSplineBasisFunction *basis_function_2_0_equal{};
  ASSERT_NO_THROW(basis_function_2_0_equal = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan2, kDegree0));
  EXPECT_TRUE(IsEqual(*basis_function_2_0_equal, *basis_function_2_0));
  EXPECT_TRUE(*basis_function_2_0_equal == *basis_function_2_0);
  BSplineBasisFunction *basis_function_2_0_knot_vector{};
  ASSERT_NO_THROW(basis_function_2_0_knot_vector = BSplineBasisFunction::CreateDynamic(knot_vector_perturbed,
                                                                                       kKnotSpan2, kDegree0));
  EXPECT_FALSE(IsEqual(*basis_function_2_0_knot_vector, *basis_function_2_0));
  EXPECT_FALSE(*basis_function_2_0_knot_vector == *basis_function_2_0);
  EXPECT_FALSE(IsEqual(*basis_function_2_0_knot_vector, *basis_function_2_0, kTolerance));
  ASSERT_NO_THROW(basis_function_2_0_knot_vector =
                  BSplineBasisFunction::CreateDynamic(knot_vector_perturbed, kKnotSpan2, kDegree0, kTolerance));
  EXPECT_TRUE(IsEqual(*basis_function_2_0_knot_vector, *basis_function_2_0, kTolerance));
  BSplineBasisFunction *basis_function_2_0_knot_span{};
  ASSERT_NO_THROW(basis_function_2_0_knot_span = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan1,
                                                                                     kDegree0));
  EXPECT_FALSE(IsEqual(*basis_function_2_0_knot_span, *basis_function_2_0));
  EXPECT_FALSE(*basis_function_2_0_knot_span == *basis_function_2_0);

  BSplineBasisFunction *basis_function_0_2_equal{};
  ASSERT_NO_THROW(basis_function_0_2_equal = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan0, kDegree2));
  EXPECT_TRUE(IsEqual(*basis_function_0_2_equal, *basis_function_0_2));
  EXPECT_TRUE(*basis_function_0_2_equal == *basis_function_0_2);
  BSplineBasisFunction *basis_function_0_2_knot_vector{};
  ASSERT_NO_THROW(basis_function_0_2_knot_vector = BSplineBasisFunction::CreateDynamic(knot_vector_perturbed,
                                                                                       kKnotSpan0, kDegree2));
  EXPECT_FALSE(IsEqual(*basis_function_0_2_knot_vector, *basis_function_0_2));
  EXPECT_FALSE(*basis_function_0_2_knot_vector == *basis_function_0_2);
  EXPECT_FALSE(IsEqual(*basis_function_0_2_knot_vector, *basis_function_0_2, kTolerance));
  ASSERT_NO_THROW(basis_function_0_2_knot_vector =
                  BSplineBasisFunction::CreateDynamic(knot_vector_perturbed, kKnotSpan0, kDegree2, kTolerance));
  EXPECT_TRUE(IsEqual(*basis_function_0_2_knot_vector, *basis_function_0_2, kTolerance));
  BSplineBasisFunction *basis_function_0_2_knot_span{};
  ASSERT_NO_THROW(basis_function_0_2_knot_span = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan1,
                                                                                     kDegree2));
  // N_{1,2} == N_{0,2} is true for BSplineBasisFunctions corresponding to {0.0, 0.0, 0.0, 1.0, 1.0, 1.0}.
  EXPECT_TRUE(IsEqual(*basis_function_0_2_knot_span, *basis_function_0_2));
  EXPECT_TRUE(*basis_function_0_2_knot_span == *basis_function_0_2);
  BSplineBasisFunction *basis_function_0_2_degree{};
  ASSERT_NO_THROW(basis_function_0_2_degree = BSplineBasisFunction::CreateDynamic(knot_vector, kKnotSpan0, Degree{1}));
  EXPECT_FALSE(IsEqual(*basis_function_0_2_degree, *basis_function_0_2));
  EXPECT_FALSE(*basis_function_0_2_degree == *basis_function_0_2);
}

}  // namespace splinelib::tests::parameter_spaces::b_spline_basis_function
