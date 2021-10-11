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

#include "Tests/Splines/nurbs_mock.hpp"

#include <utility>

#include "Sources/Utilities/std_container_operations.hpp"
#include "Tests/ParameterSpaces/parameter_space_mock.hpp"
#include "Tests/Splines/b_spline_mock.hpp"
#include "Tests/VectorSpaces/weighted_vector_space_mock.hpp"

namespace splinelib::tests::splines {

void A2d3dNurbsMock::SquareUnitFirstOrderBezier() {
  using testing::StrictMock;
  using HomogeneousBSpline = StrictMock<splines::A2d4dBSplineMock>;
  using WeightedVectorSpace = StrictMock<vector_spaces::A3dWeightedVectorSpaceMock>;
  using std::make_shared, std::move;

  SharedPointer<WeightedVectorSpace> weighted_vector_space{make_shared<WeightedVectorSpace>()};
  weighted_vector_space->SquareUnit04(); weighted_vector_space_ = move(weighted_vector_space);
  SharedPointer<HomogeneousBSpline> homogeneous_b_spline{make_shared<HomogeneousBSpline>()};
  homogeneous_b_spline->SquareUnitFirstOrderBezier(); homogeneous_b_spline_ = move(homogeneous_b_spline);
}

}  // namespace splinelib::tests::splines
