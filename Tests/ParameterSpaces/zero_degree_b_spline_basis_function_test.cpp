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
#include "Sources/ParameterSpaces/zero_degree_b_spline_basis_function.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/numeric_operations.hpp"
#include "Tests/ParameterSpaces/knot_vector_mock.hpp"

namespace splinelib::tests::parameter_spaces {

using sources::parameter_spaces::ZeroDegreeBSplineBasisFunction;
using sources::utilities::numeric_operations::IsEqual;

// Test basis function N_{2,0} from NURBS book Exa. 2.1.
class ZeroDegreeBSplineBasisFunctionSuite : public testing::Test {
 protected:
  using KnotVector_ = testing::StrictMock<AKnotVectorMock>;
  using Type_ = ZeroDegreeBSplineBasisFunction::Type_;

  constexpr static KnotSpan const kKnotSpan2_{2};
  constexpr static sources::parameter_spaces::Tolerance const &kEpsilon_ = sources::parameter_spaces::kEpsilon,
                                                              &kTolerance_ = (1.2 * kEpsilon_);
  constexpr static ParametricCoordinate const kParametricCoordinate0_0_{}, kParametricCoordinate0_25_{0.25},
                                              kPerturbation_{1.1 * kEpsilon_};
  constexpr static ParametricCoordinate const &kParametricCoordinate0_0Perturbed_ = (kParametricCoordinate0_0_ -
      kPerturbation_), &kParametricCoordinate0_25Perturbed_ = (kParametricCoordinate0_25_ + kPerturbation_);
  constexpr static Type_ const k0_0_{};

  ZeroDegreeBSplineBasisFunctionSuite();

  KnotVector_ knot_vector_;
  ZeroDegreeBSplineBasisFunction basis_function_;
};

ZeroDegreeBSplineBasisFunctionSuite::ZeroDegreeBSplineBasisFunctionSuite() {
  knot_vector_.NurbsBookExa2_1();
  basis_function_ = ZeroDegreeBSplineBasisFunction{knot_vector_, kKnotSpan2_};
}

TEST_F(ZeroDegreeBSplineBasisFunctionSuite, IsEqualAndOperatorEqual) {
  ZeroDegreeBSplineBasisFunction basis_function;
  ASSERT_NO_THROW(basis_function = ZeroDegreeBSplineBasisFunction(knot_vector_, kKnotSpan2_));
  EXPECT_TRUE(IsEqual(basis_function, basis_function_));
  EXPECT_TRUE(basis_function == basis_function_);

  KnotVector_ knot_vector;
  ASSERT_NO_THROW(knot_vector.NurbsBookExa2_1Perturbed());
  ZeroDegreeBSplineBasisFunction basis_function_knot_vector;
  ASSERT_NO_THROW(basis_function_knot_vector = ZeroDegreeBSplineBasisFunction(knot_vector, kKnotSpan2_));
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_));
  EXPECT_FALSE(basis_function_knot_vector == basis_function_);
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_, kTolerance_));
  ASSERT_NO_THROW(basis_function_knot_vector = ZeroDegreeBSplineBasisFunction(knot_vector, kKnotSpan2_, kTolerance_));
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_));
  EXPECT_FALSE(basis_function_knot_vector == basis_function_);
  EXPECT_TRUE(IsEqual(basis_function_knot_vector, basis_function_, kTolerance_));

  ZeroDegreeBSplineBasisFunction basis_function_knot_span;
  ASSERT_NO_THROW(basis_function_knot_span = ZeroDegreeBSplineBasisFunction(knot_vector_, KnotSpan{1}));
  EXPECT_FALSE(IsEqual(basis_function_knot_span, basis_function_));
  EXPECT_FALSE(basis_function_knot_span == basis_function_);
}

TEST_F(ZeroDegreeBSplineBasisFunctionSuite, Evaluate) {
  Type_ evaluated;
  EXPECT_TRUE(IsEqual(evaluated = basis_function_(kParametricCoordinate0_25_), Type_{1.0}));
  // N_{2,0} is constant.
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_25Perturbed_), evaluated));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_), k0_0_));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kTolerance_),
                      basis_function_(kParametricCoordinate0_0_), kTolerance_));
}

TEST_F(ZeroDegreeBSplineBasisFunctionSuite, EvaluateDerivative) {
  constexpr Derivative kDerivative{1};

  Type_ derivative;
  EXPECT_TRUE(IsEqual(derivative = basis_function_(kParametricCoordinate0_25_, kDerivative), Type_{}));
  // Derivatives of N_{2,0} are constant.
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_25Perturbed_, kDerivative), derivative));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_25_, Derivative{}),
                      basis_function_(kParametricCoordinate0_25_)));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kDerivative), k0_0_));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kDerivative, kTolerance_),
                      basis_function_(kParametricCoordinate0_0_, kDerivative), kTolerance_));
}

}  // namespace splinelib::tests::parameter_spaces
