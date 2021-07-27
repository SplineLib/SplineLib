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

#include "Tests/Splines/b_spline_mock.hpp"

#include <cmath>
#include <utility>

#include "Sources/Utilities/std_container_operations.hpp"
#include "Tests/ParameterSpaces/parameter_space_mock.hpp"
#include "Tests/VectorSpaces/vector_space_mock.hpp"

namespace splinelib::tests::splines {

namespace {

using testing::StrictMock;
using Coordinate3d = A2d3dBSplineMock::Coordinate_;
using Derivative = A2d3dBSplineMock::Derivative_;
using ParameterSpace = StrictMock<parameter_spaces::A2dParameterSpaceMock>;
using ScalarDerivative = Derivative::value_type;
using VectorSpace3d = StrictMock<vector_spaces::A3dVectorSpaceMock>;
using sources::utilities::std_container_operations::Add, sources::utilities::std_container_operations::Multiply,
      sources::utilities::std_container_operations::Subtract, std::make_shared, std::move, testing::Ge, testing::Return;

constexpr Index const kIndex0{}, kIndex1{1}, kIndex2{2}, kIndex3{3};
constexpr ParametricCoordinate const kParametricCoordinate0_5{0.5};
constexpr A2d3dBSplineMock::ParametricCoordinate_ const kParametricCoordinate{kParametricCoordinate0_5,
                                                                              kParametricCoordinate0_5};
constexpr ScalarDerivative const kDerivative1{1}, kDerivative2{2};
constexpr Derivative kDerivative1_1{kDerivative1, kDerivative1}, kDerivative2_2{kDerivative2, kDerivative2};

}  // namespace

Coordinate3d A2d3dBSplineMock::operator()(ParametricCoordinate_ const &parametric_coordinate,
                                          Tolerance const &tolerance) const {
  return Evaluate(parametric_coordinate, tolerance);
}

Coordinate3d A2d3dBSplineMock::operator()(ParametricCoordinate_ const &parametric_coordinate,
                                          Derivative_ const &derivative, Tolerance const &tolerance) const {
  return EvaluateDerivative(parametric_coordinate, derivative, tolerance);
}

A2d3dBSplineMock::Coordinates_
A2d3dBSplineMock::Sample(NumberOfParametricCoordinates_ const &number_of_parametric_coordinates,
                         Tolerance const &tolerance) const {
  return SampleMock(number_of_parametric_coordinates, tolerance);
}

void A2d3dBSplineMock::NurbsBookExe4_4() {
  constexpr NumberOfParametricCoordinates_::value_type const kLength3{3};

  SharedPointer<ParameterSpace> parameter_space{make_shared<ParameterSpace>()};
  parameter_space->NurbsBookExe4_4(); parameter_space_ = parameter_space;
  SharedPointer<VectorSpace3d> vector_space_pointer{make_shared<VectorSpace3d>()};
  vector_space_pointer->NurbsBookExe4_4();
  VectorSpace_ const &vector_space = *vector_space_pointer;
  vector_space_ = move(vector_space_pointer);

  Coordinate_ const &kCoordinate0 = vector_space[kIndex0], &kCoordinate1 = vector_space[kIndex1],
                    &kCoordinate2 = vector_space[kIndex2], &kCoordinate3 = vector_space[kIndex3],
                    &kCoordinate = Multiply(Add(kCoordinate0, kCoordinate1, kCoordinate2, kCoordinate3), 0.25);

  EXPECT_CALL(*this, Evaluate(kParametricCoordinate, Ge(0.0))).WillRepeatedly(Return(kCoordinate));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_1, Ge(0.0)))
      .WillRepeatedly(Return(Subtract(Add(kCoordinate0, kCoordinate3), kCoordinate1, kCoordinate2)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_2, Ge(0.0)))
      .WillRepeatedly(Return(Coordinate_{}));

  EXPECT_CALL(*this, SampleMock({{kLength3, kLength3}}, kEpsilon)).WillRepeatedly(Return(A2d3dBSplineMock::Coordinates_{
      kCoordinate0, Multiply(Add(kCoordinate0, kCoordinate1), 0.5), kCoordinate1, Multiply(Add(kCoordinate0,
          kCoordinate2), 0.5), kCoordinate, Multiply(Add(kCoordinate1, kCoordinate3), 0.5), kCoordinate2,
              Multiply(Add(kCoordinate2, kCoordinate3), 0.5), kCoordinate3}));
}

void A2d3dBSplineMock::SquareUnitSecondOrderMaximallySmooth() {
  SharedPointer<ParameterSpace> parameter_space{make_shared<ParameterSpace>()};
  parameter_space->SquareUnitSecondOrderMaximallySmooth(); parameter_space_ = parameter_space;
  SharedPointer<VectorSpace3d> vector_space{make_shared<VectorSpace3d>()};
  vector_space->SquareUnit12(); vector_space_ = vector_space;
}

namespace {

using Coordinate4d = A2d4dBSplineMock::Coordinate_;
using VectorSpace4d = StrictMock<vector_spaces::A4dVectorSpaceMock>;

constexpr Coordinate4d::value_type kCoordinate0_0{};
constexpr Coordinate4d const kCoordinateOrigin{kCoordinate0_0, kCoordinate0_0, kCoordinate0_0, kCoordinate0_0};
constexpr ScalarDerivative const kDerivative0{};
constexpr Derivative const kDerivative0_0{kDerivative0, kDerivative0}, kDerivative1_0{kDerivative1, kDerivative0},
    kDerivative2_0{kDerivative2, kDerivative0}, kDerivative0_1{kDerivative0, kDerivative1}, kDerivative2_1{kDerivative2,
        kDerivative1}, kDerivative0_2{kDerivative0, kDerivative2}, kDerivative1_2{kDerivative1, kDerivative2};

}  // namespace

Coordinate4d A2d4dBSplineMock::operator()(ParametricCoordinate_ const &parametric_coordinate,
                                          Tolerance const &tolerance) const {
  return Evaluate(parametric_coordinate, tolerance);
}

Coordinate4d A2d4dBSplineMock::operator()(ParametricCoordinate_ const &parametric_coordinate,
                                          Derivative_ const &derivative, Tolerance const &tolerance) const {
  return EvaluateDerivative(parametric_coordinate, derivative, tolerance);
}

void A2d4dBSplineMock::InsertKnot(Dimension const &dimension, Knot_ knot, Multiplicity const &multiplicity,
                                  Tolerance const &tolerance) const {
  InsertKnotMock(dimension, move(knot), multiplicity, tolerance);
}

Multiplicity A2d4dBSplineMock::RemoveKnot(Dimension const &dimension, Knot_ const &knot,
    Tolerance const &tolerance_removal, Multiplicity const &multiplicity, Tolerance const &tolerance) const {
  return RemoveKnotMock(dimension, knot, tolerance_removal, multiplicity, tolerance);
}

void A2d4dBSplineMock::ElevateDegree(Dimension const &dimension, Multiplicity const &multiplicity,
                                     Tolerance const &tolerance) const {
  ElevateDegreeMock(dimension, multiplicity, tolerance);
}

bool A2d4dBSplineMock::ReduceDegree(Dimension const &dimension, Tolerance const &tolerance_reduction,
                                    Multiplicity const &multiplicity, Tolerance const &tolerance) const {
  return ReduceDegreeMock(dimension, tolerance_reduction, multiplicity, tolerance);
}

void A2d4dBSplineMock::NurbsBookExe4_4() {
  using testing::AtMost;

  constexpr Dimension const kDimension0{};
  constexpr ParametricCoordinate const kParametricCoordinate0_0{}, kParametricCoordinate1_0{1.0};
  constexpr ParametricCoordinate_ const kParametricCoordinate0{kParametricCoordinate0_0, kParametricCoordinate0_0};

  SharedPointer<ParameterSpace> parameter_space{make_shared<ParameterSpace>()};
  parameter_space->NurbsBookExe4_4(); parameter_space_ = parameter_space;
  SharedPointer<VectorSpace4d> vector_space_pointer{make_shared<VectorSpace4d>()};
  vector_space_pointer->NurbsBookExe4_4();
  VectorSpace_ const &vector_space = *vector_space_pointer;
  vector_space_ = move(vector_space_pointer);

  Coordinate_ const &kCoordinate0 = vector_space[kIndex0], &kCoordinate1 = vector_space[kIndex1],
                    &kCoordinate2 = vector_space[kIndex2], &kCoordinate3 = vector_space[kIndex3],
                    &kCoordinate = Multiply(Add(kCoordinate0, kCoordinate1, kCoordinate2, kCoordinate3), 0.25),
                    &kCoordinateDerivative1_1 = Subtract(Add(kCoordinate0, kCoordinate3), kCoordinate1, kCoordinate2);
  EXPECT_CALL(*this, Evaluate(kParametricCoordinate, Ge(0.0))).WillRepeatedly(Return(kCoordinate));
  EXPECT_CALL(*this, Evaluate(kParametricCoordinate0, Ge(0.0))).WillRepeatedly(Return(kCoordinate0));
  EXPECT_CALL(*this, Evaluate(ParametricCoordinate_{kParametricCoordinate1_0, kParametricCoordinate0_0}, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinate1));
  EXPECT_CALL(*this, Evaluate(ParametricCoordinate_{kParametricCoordinate0_0, kParametricCoordinate1_0}, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinate2));
  EXPECT_CALL(*this, Evaluate(ParametricCoordinate_{kParametricCoordinate1_0, kParametricCoordinate1_0}, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinate3));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate0, kDerivative0_0, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinate0));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate0, kDerivative1_0, Ge(0.0)))
      .WillRepeatedly(Return(Subtract(kCoordinate1, kCoordinate0)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate0, kDerivative0_1, Ge(0.0)))
      .WillRepeatedly(Return(Subtract(kCoordinate2, kCoordinate0)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate0, kDerivative1_1, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateDerivative1_1));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative0_0, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinate));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_0, Ge(0.0)))
      .WillRepeatedly(Return(Multiply(Add(Subtract(kCoordinate1, kCoordinate0), Subtract(kCoordinate3, kCoordinate2)),
                                      0.5)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_0, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative0_1, Ge(0.0)))
      .WillRepeatedly(Return(Multiply(Add(Subtract(kCoordinate2, kCoordinate0), Subtract(kCoordinate3, kCoordinate1)),
                                      0.5)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_1, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateDerivative1_1));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_1, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative0_2, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_2, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_2, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));

  EXPECT_CALL(*this, InsertKnotMock(kDimension0, kParametricCoordinate0_5, kMultiplicity_, Ge(0.0))).Times(AtMost(1));
  EXPECT_CALL(*this, RemoveKnotMock(kDimension0, kParametricCoordinate0_5, kEpsilon * (1.0 / (1.0 + std::sqrt(13.0))),
                                    kMultiplicity_, Ge(0.0))).Times(AtMost(1)).WillRepeatedly(Return(Multiplicity{}));
  EXPECT_CALL(*this, ElevateDegreeMock(kDimension0, kMultiplicity_, Ge(0.0))).Times(AtMost(1));
  EXPECT_CALL(*this, ReduceDegreeMock(kDimension0, Ge(0.0), kMultiplicity_, Ge(0.0))).WillRepeatedly(Return(false));
}

void A2d4dBSplineMock::NurbsBookExe4_4KnotVector() {
  SharedPointer<ParameterSpace> parameter_space{make_shared<ParameterSpace>()};
  parameter_space->NurbsBookExe4_4KnotVector(); parameter_space_ = move(parameter_space);
  SharedPointer<VectorSpace4d> vector_space{make_shared<VectorSpace4d>()};
  vector_space->NurbsBookExe4_4(); vector_space_ = move(vector_space);
}

void A2d4dBSplineMock::NurbsBookExe4_4BSpline() {
  SharedPointer<ParameterSpace> parameter_space{make_shared<ParameterSpace>()};
  parameter_space->NurbsBookExe4_4(); parameter_space_ = parameter_space;
  SharedPointer<VectorSpace4d> vector_space_pointer{make_shared<VectorSpace4d>()};
  vector_space_pointer->NurbsBookExe4_4NonRational();
  VectorSpace_ const &vector_space = *vector_space_pointer;
  vector_space_ = move(vector_space_pointer);

  Coordinate_ const &kCoordinate0 = vector_space[kIndex0], &kCoordinate1 = vector_space[kIndex1],
                    &kCoordinate2 = vector_space[kIndex2], &kCoordinate3 = vector_space[kIndex3],
                    &kCoordinate = Multiply(Add(kCoordinate0, kCoordinate1, kCoordinate2, kCoordinate3), 0.25);

  EXPECT_CALL(*this, Evaluate(kParametricCoordinate, Ge(0.0))).WillRepeatedly(Return(kCoordinate));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative0_0, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinate));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_0, Ge(0.0)))
      .WillRepeatedly(Return(Multiply(Add(Subtract(kCoordinate1, kCoordinate0), Subtract(kCoordinate3, kCoordinate2)),
                                      0.5)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_0, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative0_1, Ge(0.0)))
      .WillRepeatedly(Return(Multiply(Add(Subtract(kCoordinate2, kCoordinate0), Subtract(kCoordinate3, kCoordinate1)),
                                      0.5)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_1, Ge(0.0)))
      .WillRepeatedly(Return(Subtract(Add(kCoordinate0, kCoordinate3), kCoordinate1, kCoordinate2)));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_1, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative0_2, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative1_2, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
  EXPECT_CALL(*this, EvaluateDerivative(kParametricCoordinate, kDerivative2_2, Ge(0.0)))
      .WillRepeatedly(Return(kCoordinateOrigin));
}

void A2d4dBSplineMock::SquareUnitFirstOrderBezier() {
  SharedPointer<ParameterSpace> parameter_space{make_shared<ParameterSpace>()};
  parameter_space->SquareUnitFirstOrderBezier(); parameter_space_ = parameter_space;
  SharedPointer<VectorSpace4d> vector_space{make_shared<VectorSpace4d>()};
  vector_space->SquareUnit04(); vector_space_ = vector_space;
}

}  // namespace splinelib::tests::splines
