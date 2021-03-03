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
#include "Sources/ParameterSpaces/non_zero_degree_b_spline_basis_function.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/numeric_operations.hpp"
#include "Tests/ParameterSpaces/knot_vector_mock.hpp"

namespace splinelib::tests::parameter_spaces {

using sources::parameter_spaces::NonZeroDegreeBSplineBasisFunction;
using sources::utilities::numeric_operations::IsEqual;

// Test basis function N_{0,2} from NURBS book Exa. 2.1.
class NonZeroDegreeBSplineBasisFunctionSuite : public testing::Test {
 protected:
  using KnotVector_ = testing::StrictMock<AKnotVectorMock>;
  using Tolerance_ = sources::parameter_spaces::Tolerance;
  using Type_ = NonZeroDegreeBSplineBasisFunction::Type_;

  constexpr static Degree const kDegree2_{2};
  constexpr static KnotSpan const kKnotSpan0_{};
  constexpr static Tolerance_ const &kEpsilon_ = sources::parameter_spaces::kEpsilon;
  constexpr static Tolerance_ const kTolerance_{1.2 * kEpsilon_}, kToleranceDegree_{kDegree2_.Get() * kTolerance_};
  constexpr static ParametricCoordinate const kParametricCoordinate0_0_{}, kParametricCoordinate0_25_{0.25},
                                              kPerturbation_{1.1 * kEpsilon_};
  constexpr static ParametricCoordinate const &kParametricCoordinate0_0Perturbed_ = (kParametricCoordinate0_0_ -
      kPerturbation_), &kParametricCoordinate0_25Perturbed_ = (kParametricCoordinate0_25_ + kPerturbation_);
  constexpr static Type_ const k0_0_{};

  NonZeroDegreeBSplineBasisFunctionSuite();

  KnotVector_ knot_vector_;
  NonZeroDegreeBSplineBasisFunction basis_function_;
};

NonZeroDegreeBSplineBasisFunctionSuite::NonZeroDegreeBSplineBasisFunctionSuite() {
  knot_vector_.NurbsBookExa2_1();
  basis_function_ = NonZeroDegreeBSplineBasisFunction{knot_vector_, kKnotSpan0_, kDegree2_};
}

TEST_F(NonZeroDegreeBSplineBasisFunctionSuite, IsEqualAndOperatorEqual) {
  NonZeroDegreeBSplineBasisFunction basis_function;
  ASSERT_NO_THROW(basis_function = NonZeroDegreeBSplineBasisFunction(knot_vector_, kKnotSpan0_, kDegree2_));
  EXPECT_TRUE(IsEqual(basis_function, basis_function_));
  EXPECT_TRUE(basis_function == basis_function_);

  KnotVector_ knot_vector;
  ASSERT_NO_THROW(knot_vector.NurbsBookExa2_1Perturbed());
  NonZeroDegreeBSplineBasisFunction basis_function_knot_vector;
  ASSERT_NO_THROW(basis_function_knot_vector = NonZeroDegreeBSplineBasisFunction(knot_vector, kKnotSpan0_, kDegree2_));
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_));
  EXPECT_FALSE(basis_function_knot_vector == basis_function_);
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_, kTolerance_));
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_, kToleranceDegree_));
  ASSERT_NO_THROW(basis_function_knot_vector = NonZeroDegreeBSplineBasisFunction(knot_vector, kKnotSpan0_, kDegree2_,
                                                                                 kTolerance_));
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_));
  EXPECT_FALSE(basis_function_knot_vector == basis_function_);
  EXPECT_FALSE(IsEqual(basis_function_knot_vector, basis_function_, kTolerance_));
  EXPECT_TRUE(IsEqual(basis_function_knot_vector, basis_function_, kToleranceDegree_));

  NonZeroDegreeBSplineBasisFunction basis_function_knot_span;
  ASSERT_NO_THROW(basis_function_knot_span = NonZeroDegreeBSplineBasisFunction(knot_vector_, KnotSpan{1}, kDegree2_));
  EXPECT_FALSE(IsEqual(basis_function_knot_span, basis_function_));
  EXPECT_FALSE(basis_function_knot_span == basis_function_);

  NonZeroDegreeBSplineBasisFunction basis_function_degree;
  ASSERT_NO_THROW(basis_function_degree = NonZeroDegreeBSplineBasisFunction(knot_vector_, kKnotSpan0_, Degree{1}));
  EXPECT_FALSE(IsEqual(basis_function_degree, basis_function_));
  EXPECT_FALSE(basis_function_degree == basis_function_);
}

TEST_F(NonZeroDegreeBSplineBasisFunctionSuite, EvaluateDependingOnInvertPotentialZero) {
  Type_ evaluated;
  EXPECT_TRUE(IsEqual(evaluated = basis_function_(kParametricCoordinate0_25_), Type_{0.5625}));
  EXPECT_FALSE(IsEqual(basis_function_(kParametricCoordinate0_25Perturbed_), evaluated));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_25Perturbed_), evaluated, kToleranceDegree_));

  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_), k0_0_));
  EXPECT_FALSE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kTolerance_),
                       basis_function_(kParametricCoordinate0_0_), kTolerance_));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kTolerance_),
                      basis_function_(kParametricCoordinate0_0_), kToleranceDegree_));
}

TEST_F(NonZeroDegreeBSplineBasisFunctionSuite, EvaluateDerivativeDependingOnInvertPotentialZero) {
  constexpr Derivative kDerivative{1};

  Type_ derivative;
  EXPECT_TRUE(IsEqual(derivative = basis_function_(kParametricCoordinate0_25_, kDerivative), Type_{-1.5}));
  EXPECT_FALSE(IsEqual(basis_function_(kParametricCoordinate0_25Perturbed_, kDerivative), derivative));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_25Perturbed_, kDerivative), derivative,
                      kToleranceDegree_));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_25_, Derivative{}),
                      basis_function_(kParametricCoordinate0_25_)));

  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kDerivative), k0_0_));
  EXPECT_FALSE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kDerivative, kTolerance_),
                       basis_function_(kParametricCoordinate0_0_, kDerivative), kTolerance_));
  EXPECT_TRUE(IsEqual(basis_function_(kParametricCoordinate0_0Perturbed_, kDerivative, kTolerance_),
                      basis_function_(kParametricCoordinate0_0_, kDerivative), kToleranceDegree_));
}

}  // namespace splinelib::tests::parameter_spaces
