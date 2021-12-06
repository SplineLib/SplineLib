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

#include "Tests/VectorSpaces/vector_space_mock.hpp"

#include <cmath>

namespace splinelib::tests::vector_spaces {

namespace {

using Coordinate3d = A3dVectorSpaceMock::Coordinate_;
using ScalarCoordinate = Coordinate3d::value_type;
using testing::Assign, testing::InvokeWithoutArgs, testing::Return, testing::ReturnRef, testing::ReturnRefOfCopy;

constexpr ScalarCoordinate const k0_0{}, k1_0{1.0}, k1_5{1.5}, k2_0{2.0}, k2_5{2.5}, k2_75{2.75}, k3_0{3.0}, k3_5{3.5},
                                 k3_75{3.75}, k4_0{4.0}, k4_5{4.5}, k5_0{5.0}, k5_25{5.25}, k5_5{5.5}, k6_0{6.0},
                                 k6_25{6.25}, k7_0{7.0}, k7_5{7.5}, k9_0{9.0};
constexpr Coordinate3d const kCoordinate0_0{k0_0, k0_0, k0_0}, kCoordinate1_0{k3_0, k0_0, k3_0},
    kCoordinateElevatedOnce1_0{k2_0, k0_0, k2_0}, kCoordinateElevatedTwice1_0{k1_5, k0_0, k1_5}, kCoordinate2_0{k6_0,
    k0_0, k3_0}, kCoordinateBezier2_0{k4_5, k0_0, k3_0}, kCoordinateElevatedOnce2_0_0{k3_5, k0_0, k3_0},
    kCoordinateElevatedOnce2_0_1{k5_5, k0_0, k3_0}, kCoordinateElevatedTwice2_0_0_0{k3_75, k0_0, k3_0},
    kCoordinateElevatedTwice2_0_1_0{k2_75, k0_0, k2_5}, kCoordinateElevatedTwice2_0_0_1{k5_25, k0_0, k3_0},
    kCoordinate3_0{k9_0, k0_0, k0_0}, kCoordinateElevatedOnce3_0{k7_0, k0_0, k2_0}, kCoordinateElevatedTwice3_0_0{k7_5,
    k0_0, k1_5}, kCoordinateElevatedTwice3_0_1{k6_25, k0_0, k2_5}, kCoordinate0_1{k0_0, k2_0, k2_0},
    kCoordinateInserted0_1{k0_0, k1_0, k1_0}, kCoordinate1_1{k3_0, k2_0, k5_0}, kCoordinateElevatedOnce1_1{k2_0, k2_0,
    k4_0}, kCoordinateElevatedTwice1_1{k1_5, k2_0, k3_5}, kCoordinateInserted1_1{k3_0, k1_0, k4_0}, kCoordinate2_1{k6_0,
    k2_0, k5_0}, kCoordinateBezier2_1{k4_5, k2_0, k5_0}, kCoordinateElevatedOnce2_1_0{k3_5, k2_0, k5_0},
    kCoordinateElevatedOnce2_1_1{k5_5, k2_0, k5_0}, kCoordinateElevatedTwice2_1_0_0{k3_75, k2_0, k5_0},
    kCoordinateElevatedTwice2_1_1_0{k2_75, k2_0, k4_5}, kCoordinateElevatedTwice2_1_0_1{k5_25, k2_0, k5_0},
    kCoordinateInserted2_1{k6_0, k1_0, k4_0}, kCoordinate3_1{k9_0, k2_0, k2_0}, kCoordinateElevatedOnce3_1{k7_0, k2_0,
    k4_0}, kCoordinateElevatedTwice3_1_0{k7_5, k2_0, k3_5}, kCoordinateElevatedTwice3_1_1{k6_25, k2_0, k4_5},
    kCoordinateInserted3_1{k9_0, k1_0, k1_0}, kCoordinate0_2{k0_0, k4_0, k0_0}, kCoordinateInserted0_2{k0_0, k3_0,
    k1_0}, kCoordinateSubdivided0_2{k0_0, k2_0, k1_0}, kCoordinate1_2{k3_0, k4_0, k3_0}, kCoordinateElevatedOnce1_2{
    k2_0, k4_0, k2_0}, kCoordinateElevatedTwice1_2{k1_5, k4_0, k1_5}, kCoordinateInserted1_2{k3_0, k3_0, k4_0},
    kCoordinateSubdivided1_2{k3_0, k2_0, k4_0}, kCoordinate2_2{k6_0, k4_0, k3_0}, kCoordinateBezier2_2{k4_5, k4_0,
    k3_0}, kCoordinateElevatedOnce2_2_0{k3_5, k4_0, k3_0}, kCoordinateElevatedOnce2_2_1{k5_5, k4_0, k3_0},
    kCoordinateElevatedTwice2_2_0_0{k3_75, k4_0, k3_0}, kCoordinateElevatedTwice2_2_1_0{k2_75, k4_0, k2_5},
    kCoordinateElevatedTwice2_2_0_1{k5_25, k4_0, k3_0}, kCoordinateInserted2_2{k6_0, k3_0, k4_0},
    kCoordinateSubdivided2_2{k6_0, k2_0, k4_0}, kCoordinate3_2{k9_0, k4_0, k0_0}, kCoordinateElevatedOnce3_2{k7_0, k4_0,
    k2_0}, kCoordinateElevatedTwice3_2_0{k7_5, k4_0, k1_5}, kCoordinateElevatedTwice3_2_1{k6_25, k4_0, k2_5},
    kCoordinateInserted3_2{k9_0, k3_0, k1_0}, kCoordinateSubdivided3_2{k9_0, k2_0, k1_0}, kCoordinateSquare{k1_0, k1_0,
    k0_0};
constexpr Index const k0{}, k1{1}, k2{2}, k3{3}, k4{4}, k5{5}, k6{6}, k7{7}, k8{8}, k9{9}, k10{10}, k11{11}, k12{12},
    k13{13}, k14{14}, k15{15}, k16{16}, k17{17}, k18{18}, k19{19}, k20{20}, k21{21}, k22{22}, k23{23}, k24{24}, k25{25};
A3dVectorSpaceMock::Coordinates_ const kCoordinatesInsertRemove{kCoordinate0_0, kCoordinate1_0, kCoordinate2_0,
    kCoordinate3_0, kCoordinateInserted0_1, kCoordinateInserted1_1, kCoordinateInserted2_1, kCoordinateInserted3_1,
    kCoordinateInserted0_2, kCoordinateInserted1_2, kCoordinateInserted2_2, kCoordinateInserted3_2, kCoordinate0_2,
    kCoordinate1_2, kCoordinate2_2, kCoordinate3_2}, kCoordinatesSubdivided{kCoordinate0_0, kCoordinate1_0,
    kCoordinate2_0, kCoordinate3_0, kCoordinateInserted0_1, kCoordinateInserted1_1, kCoordinateInserted2_1,
    kCoordinateInserted3_1, kCoordinateSubdivided0_2, kCoordinateSubdivided1_2, kCoordinateSubdivided2_2,
    kCoordinateSubdivided3_2, kCoordinateInserted0_2, kCoordinateInserted1_2, kCoordinateInserted2_2,
    kCoordinateInserted3_2, kCoordinate0_2, kCoordinate1_2, kCoordinate2_2, kCoordinate3_2};

}  // namespace

Coordinate3d const & A3dVectorSpaceMock::operator[](Index const &coordinate) const {
  return OperatorSubscript(coordinate);
}

ScalarCoordinate A3dVectorSpaceMock::DetermineMaximumDistanceFromOrigin(Tolerance_ const &tolerance) const {
  return DetermineMaximumDistanceMock(tolerance);
}

A3dVectorSpaceMock::OutputInformation_ A3dVectorSpaceMock::Write(Precision const &precision) const {
  return WriteMock(precision);
}

void A3dVectorSpaceMock::NurbsBookExe3_8() {
  coordinates_.assign({kCoordinate0_0, kCoordinate1_0, kCoordinate2_0, kCoordinate3_0, kCoordinate0_1,
                       kCoordinate1_1, kCoordinate2_1, kCoordinate3_1, kCoordinate0_2, kCoordinate1_2,
                       kCoordinate2_2, kCoordinate3_2});

  EXPECT_CALL(*this, OperatorSubscript(k0)).WillRepeatedly(ReturnRef(kCoordinate0_0));
  EXPECT_CALL(*this, OperatorSubscript(k1)).WillRepeatedly(ReturnRef(kCoordinate1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).WillRepeatedly(ReturnRef(kCoordinate2_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k5)).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k6)).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).WillRepeatedly(ReturnRef(kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k9)).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k10)).WillRepeatedly(ReturnRef(kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k11)).WillRepeatedly(ReturnRef(kCoordinate3_2));

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(12));

  EXPECT_CALL(*this, DetermineMaximumDistanceMock(kEpsilon_)).WillRepeatedly(Return(ScalarCoordinate{std::sqrt(97.0)}));
  EXPECT_CALL(*this, WriteMock(kPrecision_)).WillRepeatedly(Return(OutputInformation_{
      sources::utilities::string_operations::Write<std::tuple_element_t<0, OutputInformation_>>(coordinates_,
                                                                                                kPrecision_)}));
}

void A3dVectorSpaceMock::NurbsBookExe3_8ElevatedTwice() {
  coordinates_.assign({kCoordinate0_0, kCoordinateElevatedTwice1_0, kCoordinateElevatedTwice2_0_1_0,
      kCoordinateElevatedTwice2_0_0_0, kCoordinateElevatedTwice2_0_0_1, kCoordinateElevatedTwice3_0_1,
          kCoordinateElevatedTwice3_0_0, kCoordinate3_0, kCoordinate0_1, kCoordinateElevatedTwice1_1,
              kCoordinateElevatedTwice2_1_1_0, kCoordinateElevatedTwice2_1_0_0, kCoordinateElevatedTwice2_1_0_1,
                  kCoordinateElevatedTwice3_1_1, kCoordinateElevatedTwice3_1_0, kCoordinate3_1, kCoordinate0_2,
                      kCoordinateElevatedTwice1_2, kCoordinateElevatedTwice2_2_1_0, kCoordinateElevatedTwice2_2_0_0,
                          kCoordinateElevatedTwice2_2_0_1, kCoordinateElevatedTwice3_2_1,
                              kCoordinateElevatedTwice3_2_0, kCoordinate3_2});

  EXPECT_CALL(*this, OperatorSubscript(k3)).WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_0_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_0_0_1));
  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(24));
}

void A3dVectorSpaceMock::NurbsBookExe3_8ElevateOnce() {
  NurbsBookExe3_8();

  Expectation_ const &bezier_first0 = EXPECT_CALL(*this, Insert(k2, kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(bezier_first0).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(bezier_first0).WillRepeatedly(ReturnRef(kCoordinate2_1));
  Expectation_ const &bezier_second0 = EXPECT_CALL(*this, Insert(k7, kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(bezier_second0).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(bezier_second0).WillRepeatedly(ReturnRef(kCoordinate2_2));
  Expectation_ const &bezier_third0 = EXPECT_CALL(*this, Insert(k12, kCoordinateBezier2_2)).After(bezier_second0);
  NurbsBookExe3_8Bezier(bezier_third0);

  Expectation_ const &insert_first0_0 = EXPECT_CALL(*this, Insert(k2, kCoordinateElevatedOnce2_0_0))
      .After(bezier_third0);
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinate2_0));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  Expectation_ const &insert_second0_0 = EXPECT_CALL(*this, Insert(k8, kCoordinateElevatedOnce2_1_0))
      .After(insert_first0_0);
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  Expectation_ const &insert_third0_0 = EXPECT_CALL(*this, Insert(k14, kCoordinateElevatedOnce2_2_0))
      .After(insert_second0_0);
  Expectation_ const &replace_first0 = EXPECT_CALL(*this, Replace(k1, kCoordinateElevatedOnce1_0))
      .After(insert_third0_0);
  Expectation_ const &replace_second0 = EXPECT_CALL(*this, Replace(k7, kCoordinateElevatedOnce1_1))
      .After(replace_first0);
  Expectation_ const &replace_third0 = EXPECT_CALL(*this, Replace(k13, kCoordinateElevatedOnce1_2))
      .After(replace_second0);

  Expectation_ const &insert_first0_1 = EXPECT_CALL(*this, Insert(k5, kCoordinateElevatedOnce3_0))
      .After(replace_third0);
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinate3_1));
  Expectation_ const &insert_second0_1 = EXPECT_CALL(*this, Insert(k12, kCoordinateElevatedOnce3_1))
      .After(insert_first0_1);
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(insert_second0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(insert_second0_1).WillRepeatedly(ReturnRef(kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k19)).After(insert_second0_1).WillRepeatedly(ReturnRef(kCoordinate3_2));
  Expectation_ const &insert_third0_1 = EXPECT_CALL(*this, Insert(k19, kCoordinateElevatedOnce3_2))
      .After(insert_second0_1);
  Expectation_ const &replace_first1 = EXPECT_CALL(*this, Replace(k4, kCoordinateElevatedOnce2_0_1))
      .After(insert_third0_1);
  Expectation_ const &replace_second1 = EXPECT_CALL(*this, Replace(k11, kCoordinateElevatedOnce2_1_1))
      .After(replace_first1);
  Expectation_ const &replace_third1 =  EXPECT_CALL(*this, Replace(k18, kCoordinateElevatedOnce2_2_1))
      .After(replace_second1);
  NurbsBookExe3_8BezierElevatedReducedOnce(replace_third1);

  Expectation_ const &b_spline_first = EXPECT_CALL(*this, Erase(k17)).After(replace_third1);
  Expectation_ const &b_spline_second = EXPECT_CALL(*this, Erase(k10)).After(b_spline_first);
  Expectation_ const &b_spline_third = EXPECT_CALL(*this, Erase(k3)).After(b_spline_second);
  NurbsBookExe3_8ElevateReduce(b_spline_third);

  Expectation_ const &bezier_first1 = EXPECT_CALL(*this, Insert(k3, kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(bezier_first1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(bezier_first1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_1));
  Expectation_ const &bezier_second1 = EXPECT_CALL(*this, Insert(k10, kCoordinateBezier2_1)).After(bezier_first1);
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(bezier_second1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_0));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(bezier_second1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_1));
  Expectation_ const &bezier_third1 = EXPECT_CALL(*this, Insert(k17, kCoordinateBezier2_2)).After(bezier_second1);
  NurbsBookExe3_8BezierElevatedReducedOnce(bezier_third1);

  Expectation_ const &insert_first1_0 = EXPECT_CALL(*this, Insert(k3, kCoordinateElevatedTwice2_0_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(insert_first1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(insert_first1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_0));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(insert_first1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_1));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(insert_first1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  Expectation_ const &insert_second1_0 = EXPECT_CALL(*this, Insert(k11, kCoordinateElevatedTwice2_1_0_0))
      .After(insert_first1_0);
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(insert_second1_0).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(insert_second1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_2));
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(insert_second1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_0));
  EXPECT_CALL(*this, OperatorSubscript(k19)).After(insert_second1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  Expectation_ const &insert_third1_0 = EXPECT_CALL(*this, Insert(k19, kCoordinateElevatedTwice2_2_0_0))
      .After(insert_second1_0);
  Expectation_ const &replace_first0_0 = EXPECT_CALL(*this, Replace(k2, kCoordinateElevatedTwice2_0_1_0))
      .After(insert_third1_0);
  Expectation_ const &replace_second0_0 = EXPECT_CALL(*this, Replace(k10, kCoordinateElevatedTwice2_1_1_0))
      .After(replace_first0_0);
  Expectation_ const &replace_third0_0 = EXPECT_CALL(*this, Replace(k18, kCoordinateElevatedTwice2_2_1_0))
      .After(replace_second0_0);
  Expectation_ const &replace_first0_1 = EXPECT_CALL(*this, Replace(k1, kCoordinateElevatedTwice1_0))
      .After(replace_third0_0);
  Expectation_ const &replace_second0_1 = EXPECT_CALL(*this, Replace(k9, kCoordinateElevatedTwice1_1))
      .After(replace_first0_1);
  Expectation_ const &replace_third0_1 = EXPECT_CALL(*this, Replace(k17, kCoordinateElevatedTwice1_2))
      .After(replace_second0_1);

  Expectation_ const &insert_first1_1 = EXPECT_CALL(*this, Insert(k7, kCoordinateElevatedTwice3_0_0))
      .After(replace_third0_1);
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(insert_first1_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_first1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_1));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(insert_first1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_1));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(insert_first1_1).WillRepeatedly(ReturnRef(kCoordinate3_1));
  Expectation_ const &insert_second1_1 = EXPECT_CALL(*this, Insert(k16, kCoordinateElevatedTwice3_1_0))
      .After(insert_first1_1);
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(insert_second1_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k23)).After(insert_second1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_1));
  EXPECT_CALL(*this, OperatorSubscript(k24)).After(insert_second1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_2));
  EXPECT_CALL(*this, OperatorSubscript(k25)).After(insert_second1_1).WillRepeatedly(ReturnRef(kCoordinate3_2));
  Expectation_ const &insert_third1_1 = EXPECT_CALL(*this, Insert(k25, kCoordinateElevatedTwice3_2_0))
      .After(insert_second1_1);
  Expectation_ const &replace_first1_0 = EXPECT_CALL(*this, Replace(k6, kCoordinateElevatedTwice3_0_1))
      .After(insert_third1_1);
  Expectation_ const &replace_second1_0 = EXPECT_CALL(*this, Replace(k15, kCoordinateElevatedTwice3_1_1))
      .After(replace_first1_0);
  Expectation_ const &replace_third1_0 = EXPECT_CALL(*this, Replace(k24, kCoordinateElevatedTwice3_2_1))
      .After(replace_second1_0);
  Expectation_ const &replace_first1_1 = EXPECT_CALL(*this, Replace(k5, kCoordinateElevatedTwice2_0_0_1))
      .After(replace_third1_0);
  Expectation_ const &replace_second1_1 = EXPECT_CALL(*this, Replace(k14, kCoordinateElevatedTwice2_1_0_1))
      .After(replace_first1_1);
  Expectation_ const &replace_third1_1 = EXPECT_CALL(*this, Replace(k23, kCoordinateElevatedTwice2_2_0_1))
      .After(replace_second1_1);
  NurbsBookExe3_8BezierElevatedTwiceMakeBSpline(replace_third1_1);
}

void A3dVectorSpaceMock::NurbsBookExe3_8ElevateReduce() {
  coordinates_.assign({kCoordinate0_0, kCoordinateElevatedOnce1_0, kCoordinateElevatedOnce2_0_0,
      kCoordinateElevatedOnce2_0_1, kCoordinateElevatedOnce3_0, kCoordinate3_0, kCoordinate0_1,
      kCoordinateElevatedOnce1_1, kCoordinateElevatedOnce2_1_0, kCoordinateElevatedOnce2_1_1,
      kCoordinateElevatedOnce3_1, kCoordinate3_1, kCoordinate0_2, kCoordinateElevatedOnce1_2,
      kCoordinateElevatedOnce2_2_0, kCoordinateElevatedOnce2_2_1, kCoordinateElevatedOnce3_2, kCoordinate3_2});

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(18));
}

void A3dVectorSpaceMock::NurbsBookExe3_8ElevateTwice() {
  NurbsBookExe3_8();

  Expectation_ const &bezier_first = EXPECT_CALL(*this, Insert(k2, kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(bezier_first).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(bezier_first).WillRepeatedly(ReturnRef(kCoordinate2_1));
  Expectation_ const &bezier_second = EXPECT_CALL(*this, Insert(k7, kCoordinateBezier2_1)).After(bezier_first);
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(bezier_second).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(bezier_second).WillRepeatedly(ReturnRef(kCoordinate2_2));
  Expectation_ const &bezier_third = EXPECT_CALL(*this, Insert(k12, kCoordinateBezier2_2)).After(bezier_second);
  NurbsBookExe3_8Bezier(bezier_third);

  Expectation_ const &insert_first0_0 = EXPECT_CALL(*this, Insert(k2, kCoordinateElevatedTwice2_0_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(insert_first0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  Expectation_ const &insert_second0_0 = EXPECT_CALL(*this, Insert(k8, kCoordinateElevatedTwice2_1_0_0))
      .After(insert_first0_0);
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_second0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  Expectation_ const &insert_third0_0 = EXPECT_CALL(*this, Insert(k14, kCoordinateElevatedTwice2_2_0_0))
      .After(insert_second0_0);
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(insert_third0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  Expectation_ const &insert_first0_1 = EXPECT_CALL(*this, Insert(k2, kCoordinateElevatedTwice2_0_1_0))
      .After(insert_third0_0);
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinate2_0));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(insert_first0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  Expectation_ const &insert_second0_1 = EXPECT_CALL(*this, Insert(k9, kCoordinateElevatedTwice2_1_1_0))
      .After(insert_first0_1);
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_second0_1).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(insert_second0_1).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(insert_second0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  Expectation_ const &insert_third0_1 = EXPECT_CALL(*this, Insert(k16, kCoordinateElevatedTwice2_2_1_0))
      .After(insert_first0_1);
  Expectation_ const &replace_first0 = EXPECT_CALL(*this, Replace(k1, kCoordinateElevatedTwice1_0))
      .After(insert_third0_1);
  Expectation_ const &replace_second0 = EXPECT_CALL(*this, Replace(k8, kCoordinateElevatedTwice1_1))
      .After(replace_first0);
  Expectation_ const &replace_third0 = EXPECT_CALL(*this, Replace(k15, kCoordinateElevatedTwice1_2))
      .After(replace_second0);

  Expectation_ const &insert_first1_0 = EXPECT_CALL(*this, Insert(k6, kCoordinateElevatedTwice3_0_0))
      .After(replace_third0);
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_first1_0).WillRepeatedly(ReturnRef(kCoordinate3_1));
  Expectation_ const &insert_second1_0 = EXPECT_CALL(*this, Insert(k14, kCoordinateElevatedTwice3_1_0))
      .After(insert_first1_0);
  EXPECT_CALL(*this, OperatorSubscript(k21)).After(insert_second1_0).WillRepeatedly(ReturnRef(kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(insert_second1_0).WillRepeatedly(ReturnRef(kCoordinate3_2));
  Expectation_ const &insert_third1_0 = EXPECT_CALL(*this, Insert(k22, kCoordinateElevatedTwice3_2_0))
      .After(insert_second1_0);
  Expectation_ const &insert_first1_1 = EXPECT_CALL(*this, Insert(k6, kCoordinateElevatedTwice3_0_1))
      .After(insert_third1_0);
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(insert_first1_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_first1_1).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(insert_first1_1).WillRepeatedly(ReturnRef(kCoordinate3_1));
  Expectation_ const &insert_second1_1 = EXPECT_CALL(*this, Insert(k15, kCoordinateElevatedTwice3_1_1))
      .After(insert_first1_1);
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(insert_second1_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k23)).After(insert_second1_1).WillRepeatedly(ReturnRef(kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k25)).After(insert_second1_1).WillRepeatedly(ReturnRef(kCoordinate3_2));
  Expectation_ const &insert_third1_1 = EXPECT_CALL(*this, Insert(k24, kCoordinateElevatedTwice3_2_1))
      .After(insert_second1_1);
  Expectation_ const &replace_first1 = EXPECT_CALL(*this, Replace(k5, kCoordinateElevatedTwice2_0_0_1))
      .After(insert_third1_1);
  Expectation_ const &replace_second1 = EXPECT_CALL(*this, Replace(k14, kCoordinateElevatedTwice2_1_0_1))
      .After(replace_first1);
  Expectation_ const &replace_third1 = EXPECT_CALL(*this, Replace(k23, kCoordinateElevatedTwice2_2_0_1))
      .After(replace_second1);
  NurbsBookExe3_8BezierElevatedTwiceMakeBSpline(replace_third1);
}

void A3dVectorSpaceMock::NurbsBookExe3_8Insert() {
  NurbsBookExe3_8();

  Expectation_ const &insert_first0 = EXPECT_CALL(*this, Insert(k8, kCoordinateInserted0_2));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(insert_first0).WillRepeatedly(ReturnRef(kCoordinate1_2));
  Expectation_ const &replace_first = EXPECT_CALL(*this, Replace(k4, kCoordinateInserted0_1)).After(insert_first0);
  Expectation_ const &insert_second0 = EXPECT_CALL(*this, Insert(k9, kCoordinateInserted1_2)).After(replace_first);
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(insert_second0).WillRepeatedly(ReturnRef(kCoordinate2_2));
  Expectation_ const &replace_second = EXPECT_CALL(*this, Replace(k5, kCoordinateInserted1_1)).After(insert_second0);
  Expectation_ const &insert_third0 = EXPECT_CALL(*this, Insert(k10, kCoordinateInserted2_2)).After(replace_second);
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_third0).WillRepeatedly(ReturnRef(kCoordinate3_2));
  Expectation_ const &replace_third = EXPECT_CALL(*this, Replace(k6, kCoordinateInserted2_1)).After(insert_third0);
  Expectation_ const &insert_fourth0 = EXPECT_CALL(*this, Insert(k11, kCoordinateInserted3_2)).After(replace_third);
  Expectation_ const &replace_fourth = EXPECT_CALL(*this, Replace(k7, kCoordinateInserted3_1)).After(insert_fourth0)
      .WillOnce(Assign(&coordinates_, kCoordinatesInsertRemove));
  NurbsBookExe3_8InsertRemove(replace_fourth);

  Expectation_ const &insert_first1 = EXPECT_CALL(*this, Insert(k8, kCoordinateSubdivided0_2)).After(replace_fourth);
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(insert_first1).WillRepeatedly(ReturnRef(kCoordinateInserted1_2));
  Expectation_ const &insert_second1 = EXPECT_CALL(*this, Insert(k9, kCoordinateSubdivided1_2)).After(insert_first1);
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(insert_second1).WillRepeatedly(ReturnRef(kCoordinateInserted2_2));
  Expectation_ const &insert_third1 = EXPECT_CALL(*this, Insert(k10, kCoordinateSubdivided2_2)).After(insert_second1);
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(insert_third1).WillRepeatedly(ReturnRef(kCoordinateInserted3_2));
  Expectation_ const &insert_fourth1 = EXPECT_CALL(*this, Insert(k11, kCoordinateSubdivided3_2)).After(insert_third1)
      .WillOnce(Assign(&coordinates_, kCoordinatesSubdivided));
  NurbsBookExe3_8Subdivided(insert_fourth1);
}

void A3dVectorSpaceMock::NurbsBookExe3_8InsertRemove() {
  coordinates_ = kCoordinatesInsertRemove;

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(16));
}

void A3dVectorSpaceMock::NurbsBookExe3_8Perturbed() {
  coordinates_.assign({Coordinate3d{k0_0, k0_0, ScalarCoordinate{0.0 + 1.1 * sources::vector_spaces::kEpsilon}},
      kCoordinate1_0, kCoordinate2_0, kCoordinate3_0, kCoordinate0_1, kCoordinate1_1, kCoordinate2_1,
          kCoordinate3_1, kCoordinate0_2, kCoordinate1_2, kCoordinate2_2, kCoordinate3_2});

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(12));
}

void A3dVectorSpaceMock::NurbsBookExe3_8ReduceOnce() {
  NurbsBookExe3_8ElevatedTwice();

  Expectation_ const &bezier_first0 = EXPECT_CALL(*this, Insert(k4, kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(bezier_first0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(bezier_first0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_1));
  Expectation_ const &bezier_second0 = EXPECT_CALL(*this, Insert(k13, kCoordinateBezier2_1)).After(bezier_first0);
  EXPECT_CALL(*this, OperatorSubscript(k21)).After(bezier_second0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(bezier_second0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_1));
  Expectation_ const &bezier_third0 = EXPECT_CALL(*this, Insert(k22, kCoordinateBezier2_2)).After(bezier_second0);
  NurbsBookExe3_8BezierElevatedTwice(bezier_third0);

  Expectation_ const &replace_first0_0 = EXPECT_CALL(*this, Replace(k23, kCoordinateElevatedOnce2_2_1))
      .After(bezier_third0);
  EXPECT_CALL(*this, OperatorSubscript(k23)).After(replace_first0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_1));
  Expectation_ const &replace_second0_0 = EXPECT_CALL(*this, Replace(k14, kCoordinateElevatedOnce2_1_1))
      .After(replace_first0_0);
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(replace_second0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_1));
  Expectation_ const &replace_third0_0 = EXPECT_CALL(*this, Replace(k5, kCoordinateElevatedOnce2_0_1))
      .After(replace_second0_0);
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(replace_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_1));
  Expectation_ const &replace_first0_1 = EXPECT_CALL(*this, Replace(k24, kCoordinateElevatedOnce3_2))
      .After(replace_third0_0);
  EXPECT_CALL(*this, OperatorSubscript(k24)).After(replace_first0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_2));
  Expectation_ const &replace_second0_1 = EXPECT_CALL(*this, Replace(k15, kCoordinateElevatedOnce3_1))
      .After(replace_first0_1);
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(replace_second0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_1));
  Expectation_ const &replace_third0_1 = EXPECT_CALL(*this, Replace(k6, kCoordinateElevatedOnce3_0))
      .After(replace_second0_1);
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(replace_third0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_0));
  Expectation_ const &erase_first0_0 = EXPECT_CALL(*this, Erase(k25)).After(replace_third0_1);
  Expectation_ const &erase_second0_0 = EXPECT_CALL(*this, Erase(k16)).After(erase_first0_0);
  Expectation_ const &erase_third0_0 = EXPECT_CALL(*this, Erase(k7)).After(erase_second0_0);
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice1_1));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice1_2));
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k19)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k20)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));

  Expectation_ const &replace_first1_0 = EXPECT_CALL(*this, Replace(k17, kCoordinateElevatedOnce1_2))
      .After(erase_third0_0);
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(replace_first1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_2));
  Expectation_ const &replace_second1_0 = EXPECT_CALL(*this, Replace(k9, kCoordinateElevatedOnce1_1))
      .After(replace_first1_0);
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(replace_second1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_1));
  Expectation_ const &replace_third1_0 = EXPECT_CALL(*this, Replace(k1, kCoordinateElevatedOnce1_0))
      .After(replace_second1_0);
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(replace_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_0));
  Expectation_ const &replace_first1_1 = EXPECT_CALL(*this, Replace(k18, kCoordinateElevatedOnce2_2_0))
      .After(replace_third1_0);
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(replace_first1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_0));
  Expectation_ const &replace_second1_1 = EXPECT_CALL(*this, Replace(k10, kCoordinateElevatedOnce2_1_0))
      .After(replace_first1_1);
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(replace_second1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_0));
  Expectation_ const &replace_third1_1 = EXPECT_CALL(*this, Replace(k2, kCoordinateElevatedOnce2_0_0))
      .After(replace_second1_1);
  EXPECT_CALL(*this, OperatorSubscript(k2)).After(replace_third1_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_0));
  Expectation_ const &erase_first0_1 = EXPECT_CALL(*this, Erase(k19)).After(replace_third1_1);
  Expectation_ const &erase_second0_1 = EXPECT_CALL(*this, Erase(k11)).After(erase_first0_1);
  Expectation_ const &erase_third0_1 = EXPECT_CALL(*this, Erase(k3)).After(erase_second0_1);
  NurbsBookExe3_8BezierElevatedReducedOnce(erase_third0_1);

  Expectation_ const &b_spline_first0 = EXPECT_CALL(*this, Erase(k17)).After(erase_third0_1);
  Expectation_ const &b_spline_second0 = EXPECT_CALL(*this, Erase(k10)).After(b_spline_first0);
  Expectation_ const &b_spline_third0 = EXPECT_CALL(*this, Erase(k3)).After(b_spline_second0);
  NurbsBookExe3_8ElevateReduce(b_spline_third0);

  Expectation_ const &bezier_first1 = EXPECT_CALL(*this, Insert(k3, kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(bezier_first1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(bezier_first1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_1));
  Expectation_ const &bezier_second1 = EXPECT_CALL(*this, Insert(k10, kCoordinateBezier2_1)).After(bezier_first1);
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(bezier_second1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_0));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(bezier_second1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_1));
  Expectation_ const &bezier_third1 = EXPECT_CALL(*this, Insert(k17, kCoordinateBezier2_2)).After(bezier_second1);
  NurbsBookExe3_8BezierElevatedReducedOnce(bezier_third1);

  Expectation_ const &replace_first0 = EXPECT_CALL(*this, Replace(k18, kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(replace_first0).WillRepeatedly(ReturnRef(kCoordinate2_2));
  Expectation_ const &replace_second0 = EXPECT_CALL(*this, Replace(k11, kCoordinate2_1)).After(replace_first0);
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(replace_second0).WillRepeatedly(ReturnRef(kCoordinate2_1));
  Expectation_ const &replace_third0 = EXPECT_CALL(*this, Replace(k4, kCoordinate2_0)).After(replace_second0);
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(replace_third0).WillRepeatedly(ReturnRef(kCoordinate2_0));
  Expectation_ const &erase_first1_0 = EXPECT_CALL(*this, Erase(k19)).After(replace_third0);
  Expectation_ const &erase_second1_0 = EXPECT_CALL(*this, Erase(k12)).After(erase_first1_0);
  Expectation_ const &erase_third1_0 = EXPECT_CALL(*this, Erase(k5)).After(erase_second1_0);
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(erase_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(erase_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(erase_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_0));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));

  Expectation_ const &replace_first1 = EXPECT_CALL(*this, Replace(k13, kCoordinate1_2)).After(erase_third1_0);
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(replace_first1).WillRepeatedly(ReturnRef(kCoordinate1_2));
  Expectation_ const &replace_second1 = EXPECT_CALL(*this, Replace(k7, kCoordinate1_1)).After(replace_first1);
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(replace_second1).WillRepeatedly(ReturnRef(kCoordinate1_1));
  Expectation_ const &replace_third1 = EXPECT_CALL(*this, Replace(k1, kCoordinate1_0)).After(replace_second1);
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(replace_third1).WillRepeatedly(ReturnRef(kCoordinate1_0));
  Expectation_ const &erase_first1_1 = EXPECT_CALL(*this, Erase(k14)).After(replace_third1);
  Expectation_ const &erase_second1_1 = EXPECT_CALL(*this, Erase(k8)).After(erase_first1_1);
  Expectation_ const &erase_third1_1 = EXPECT_CALL(*this, Erase(k2)).After(erase_second1_1);
  NurbsBookExe3_8BezierReducedTwiceMakeBSpline(erase_third1_1);
}

void A3dVectorSpaceMock::NurbsBookExe3_8ReduceTwice() {
  NurbsBookExe3_8ElevatedTwice();

  Expectation_ const &bezier_first = EXPECT_CALL(*this, Insert(k4, kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(bezier_first)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(bezier_first)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_1));
  Expectation_ const &bezier_second = EXPECT_CALL(*this, Insert(k13, kCoordinateBezier2_1)).After(bezier_first);
  EXPECT_CALL(*this, OperatorSubscript(k21)).After(bezier_second)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(bezier_second)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_1));
  Expectation_ const &bezier_third = EXPECT_CALL(*this, Insert(k22, kCoordinateBezier2_2)).After(bezier_second);
  NurbsBookExe3_8BezierElevatedTwice(bezier_third);

  Expectation_ const &replace_first0_0 = EXPECT_CALL(*this, Replace(k23, kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k23)).After(replace_first0_0).WillRepeatedly(ReturnRef(kCoordinate2_2));
  Expectation_ const &replace_second0_0 = EXPECT_CALL(*this, Replace(k14, kCoordinate2_1)).After(replace_first0_0);
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(replace_second0_0).WillRepeatedly(ReturnRef(kCoordinate2_1));
  Expectation_ const &replace_third0_0 = EXPECT_CALL(*this, Replace(k5, kCoordinate2_0)).After(replace_second0_0);
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(replace_third0_0).WillRepeatedly(ReturnRef(kCoordinate2_0));
  Expectation_ const &erase_first0_0 = EXPECT_CALL(*this, Erase(k24)).After(replace_third0_0);
  Expectation_ const &erase_second0_0 = EXPECT_CALL(*this, Erase(k15)).After(erase_first0_0);
  Expectation_ const &erase_third0_0 = EXPECT_CALL(*this, Erase(k6)).After(erase_second0_0);
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k20)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k21)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(erase_third0_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_2_0));
  EXPECT_CALL(*this, OperatorSubscript(k23)).After(erase_third0_0).WillRepeatedly(ReturnRef(kCoordinate3_2));
  Expectation_ const &erase_first0_1 = EXPECT_CALL(*this, Erase(k22)).After(erase_third0_0);
  Expectation_ const &erase_second0_1 = EXPECT_CALL(*this, Erase(k14)).After(erase_first0_1);
  Expectation_ const &erase_third0_1 = EXPECT_CALL(*this, Erase(k6)).After(erase_second0_1);
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(erase_third0_1).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(erase_third0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice1_1));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(erase_third0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(erase_third0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(erase_third0_1).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(erase_third0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice1_2));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(erase_third0_1)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(erase_third0_1).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));

  Expectation_ const &replace_first0_1 = EXPECT_CALL(*this, Replace(k15, kCoordinate1_2)).After(erase_third0_1);
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(replace_first0_1).WillRepeatedly(ReturnRef(kCoordinate1_2));
  Expectation_ const &replace_second0_1 = EXPECT_CALL(*this, Replace(k8, kCoordinate1_1)).After(replace_first0_1);
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(replace_second0_1).WillRepeatedly(ReturnRef(kCoordinate1_1));
  Expectation_ const &replace_third0_1 = EXPECT_CALL(*this, Replace(k1, kCoordinate1_0)).After(replace_second0_1);
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(replace_third0_1).WillRepeatedly(ReturnRef(kCoordinate1_0));
  Expectation_ const &erase_first1_0 = EXPECT_CALL(*this, Erase(k16)).After(replace_third0_1);
  Expectation_ const &erase_second1_0 = EXPECT_CALL(*this, Erase(k9)).After(erase_first1_0);
  Expectation_ const &erase_third1_0 = EXPECT_CALL(*this, Erase(k2)).After(erase_second1_0);
  EXPECT_CALL(*this, OperatorSubscript(k2)).After(erase_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_0_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(erase_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(erase_third1_0)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(erase_third1_0).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  Expectation_ const &erase_first1_1 = EXPECT_CALL(*this, Erase(k14)).After(erase_third1_0);
  Expectation_ const &erase_second1_1 = EXPECT_CALL(*this, Erase(k8)).After(erase_first1_1);
  Expectation_ const &erase_third1_1 = EXPECT_CALL(*this, Erase(k2)).After(erase_second1_1);
  NurbsBookExe3_8BezierReducedTwiceMakeBSpline(erase_third1_1);
}

void A3dVectorSpaceMock::NurbsBookExe3_8Remove() {
  NurbsBookExe3_8Subdivided();

  Expectation_ const &erase_first0 = EXPECT_CALL(*this, Erase(k11));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(erase_first0).WillRepeatedly(ReturnRef(kCoordinateInserted2_2));
  Expectation_ const &erase_second0 = EXPECT_CALL(*this, Erase(k10)).After(erase_first0);
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(erase_second0).WillRepeatedly(ReturnRef(kCoordinateInserted1_2));
  Expectation_ const &erase_third0 = EXPECT_CALL(*this, Erase(k9)).After(erase_second0);
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(erase_third0).WillRepeatedly(ReturnRef(kCoordinateInserted0_2));
  Expectation_ const &erase_fourth0 = EXPECT_CALL(*this, Erase(k8)).After(erase_third0)
      .WillOnce(Assign(&coordinates_, kCoordinatesInsertRemove));
  NurbsBookExe3_8InsertRemove(erase_fourth0);

  Expectation_ const &replace_first = EXPECT_CALL(*this, Replace(k7, kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(replace_first).WillRepeatedly(ReturnRef(kCoordinate3_1));
  Expectation_ const &erase_first1 = EXPECT_CALL(*this, Erase(k11)).After(replace_first);
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(erase_first1).WillRepeatedly(ReturnRef(kCoordinate2_2));
  Expectation_ const &replace_second = EXPECT_CALL(*this, Replace(k6, kCoordinate2_1)).After(erase_first1);
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(replace_second).WillRepeatedly(ReturnRef(kCoordinate2_1));
  Expectation_ const &erase_second1 = EXPECT_CALL(*this, Erase(k10)).After(replace_second);
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(erase_second1).WillRepeatedly(ReturnRef(kCoordinate1_2));
  Expectation_ const &replace_third = EXPECT_CALL(*this, Replace(k5, kCoordinate1_1)).After(erase_second1);
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(replace_third).WillRepeatedly(ReturnRef(kCoordinate1_1));
  Expectation_ const &erase_third1 = EXPECT_CALL(*this, Erase(k9)).After(replace_third);
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(erase_third1).WillRepeatedly(ReturnRef(kCoordinate0_2));
  Expectation_ const &replace_fourth = EXPECT_CALL(*this, Replace(k4, kCoordinate0_1)).After(erase_third1);
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(replace_fourth).WillRepeatedly(ReturnRef(kCoordinate0_1));
  EXPECT_CALL(*this, Erase(k8)).After(replace_fourth).WillOnce(InvokeWithoutArgs(this,
                                                                                 &A3dVectorSpaceMock::NurbsBookExe3_8));
}

void A3dVectorSpaceMock::NurbsBookExe3_8Subdivided() {
  coordinates_ = kCoordinatesSubdivided;

  EXPECT_CALL(*this, OperatorSubscript(k4)).WillRepeatedly(ReturnRef(kCoordinateInserted0_1));
  EXPECT_CALL(*this, OperatorSubscript(k5)).WillRepeatedly(ReturnRef(kCoordinateInserted1_1));
  EXPECT_CALL(*this, OperatorSubscript(k6)).WillRepeatedly(ReturnRef(kCoordinateInserted2_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).WillRepeatedly(ReturnRef(kCoordinateInserted3_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).WillRepeatedly(ReturnRef(kCoordinateSubdivided0_2));
  EXPECT_CALL(*this, OperatorSubscript(k9)).WillRepeatedly(ReturnRef(kCoordinateSubdivided1_2));
  EXPECT_CALL(*this, OperatorSubscript(k10)).WillRepeatedly(ReturnRef(kCoordinateSubdivided2_2));
  EXPECT_CALL(*this, OperatorSubscript(k11)).WillRepeatedly(ReturnRef(kCoordinateSubdivided3_2));
  EXPECT_CALL(*this, OperatorSubscript(k12)).WillRepeatedly(ReturnRef(kCoordinateInserted0_2));
  EXPECT_CALL(*this, OperatorSubscript(k13)).WillRepeatedly(ReturnRef(kCoordinateInserted1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).WillRepeatedly(ReturnRef(kCoordinateInserted2_2));
  EXPECT_CALL(*this, OperatorSubscript(k15)).WillRepeatedly(ReturnRef(kCoordinateInserted3_2));

  EXPECT_CALL(*this, GetNumberOfCoordinates()).WillRepeatedly(Return(20));
}

void A3dVectorSpaceMock::NurbsBookExe3_8Unsuccessful() {
  NurbsBookExe3_8InsertRemove();

  EXPECT_CALL(*this, OperatorSubscript(k3)).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k7)).WillRepeatedly(ReturnRef(kCoordinateInserted3_1));
  EXPECT_CALL(*this, OperatorSubscript(k11)).WillRepeatedly(ReturnRef(kCoordinateInserted3_2));
  EXPECT_CALL(*this, OperatorSubscript(k15)).WillRepeatedly(ReturnRef(kCoordinate3_2));

  Expectation_ const &unremovable = EXPECT_CALL(*this, Replace(k7, kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(unremovable)
      .WillRepeatedly(ReturnRef(kCoordinate0_0));
}

void A3dVectorSpaceMock::NurbsBookExe4_4() {
  EXPECT_CALL(*this, OperatorSubscript(k0)).WillRepeatedly(ReturnRefOfCopy(Coordinate3d{k0_0, k0_0, k1_0}));
  EXPECT_CALL(*this, OperatorSubscript(k1)).WillRepeatedly(ReturnRefOfCopy(Coordinate3d{k0_0, k1_0, k3_0}));
  EXPECT_CALL(*this, OperatorSubscript(k2)).WillRepeatedly(ReturnRefOfCopy(Coordinate3d{k2_0, k1_0, k1_0}));
  EXPECT_CALL(*this, OperatorSubscript(k3)).WillRepeatedly(ReturnRefOfCopy(Coordinate3d{k2_0, k0_0, k3_0}));
}

void A3dVectorSpaceMock::SquareUnit04() {
  coordinates_.assign({kCoordinate0_0, Coordinate3d{k1_0, k0_0, k0_0}, Coordinate3d{k0_0, k1_0, k0_0},
                       kCoordinateSquare});
}

void A3dVectorSpaceMock::SquareUnit12() {
  constexpr Coordinate const kOneOverThree{1.0 / 3.0}, k0_5{0.5}, kTwoOverThree{2.0 / 3.0};

  coordinates_.assign({kCoordinate0_0, Coordinate3d{kOneOverThree, k0_0, k0_0}, Coordinate3d{kTwoOverThree, k0_0, k0_0},
      Coordinate3d{k1_0, k0_0, k0_0}, Coordinate3d{k0_0, k0_5, k0_0}, Coordinate3d{kOneOverThree, k0_5, k0_0},
          Coordinate3d{kTwoOverThree, k0_5, k0_0}, Coordinate3d{k1_0, k0_5, k0_0}, Coordinate3d{k0_0, k1_0, k0_0},
              Coordinate3d{kOneOverThree, k1_0, k0_0}, Coordinate3d{kTwoOverThree, k1_0, k0_0}, kCoordinateSquare});
}

void A3dVectorSpaceMock::NurbsBookExe3_8Bezier(Expectation_ const &expectation) {
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate2_0));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate1_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate2_1));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate2_2));
}

void A3dVectorSpaceMock::NurbsBookExe3_8BezierElevatedReducedOnce(Expectation_ const &expectation) {
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_0));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_1));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_1));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_1));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce1_2));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_0));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k18)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_2_1));
  EXPECT_CALL(*this, OperatorSubscript(k19)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_2));
  EXPECT_CALL(*this, OperatorSubscript(k20)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_2));
}

void A3dVectorSpaceMock::NurbsBookExe3_8BezierElevatedTwice(Expectation_ const &expectation) {
  EXPECT_CALL(*this, OperatorSubscript(k0)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate0_0));
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedTwice1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_0_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_0_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_0));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_0_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_1));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_1_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_1_1));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_1_0));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_1));
  EXPECT_CALL(*this, OperatorSubscript(k21)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k22)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateBezier2_2));
  EXPECT_CALL(*this, OperatorSubscript(k23)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice2_2_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k24)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_2_1));
  EXPECT_CALL(*this, OperatorSubscript(k25)).After(expectation)
      .WillRepeatedly(ReturnRef(kCoordinateElevatedTwice3_2_0));
  EXPECT_CALL(*this, OperatorSubscript(Index{26})).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_2));
}

void A3dVectorSpaceMock::NurbsBookExe3_8BezierElevatedTwiceMakeBSpline(Expectation_ const &expectation) {
  NurbsBookExe3_8BezierElevatedTwice(expectation);

  Expectation_ const &b_spline_first = EXPECT_CALL(*this, Erase(k22)).After(expectation);
  Expectation_ const &b_spline_second = EXPECT_CALL(*this, Erase(k13)).After(b_spline_first);
  EXPECT_CALL(*this, Erase(k4)).After(b_spline_second)
      .WillOnce(InvokeWithoutArgs(this, &A3dVectorSpaceMock::NurbsBookExe3_8ElevatedTwice));
}

void A3dVectorSpaceMock::NurbsBookExe3_8BezierReducedTwiceMakeBSpline(Expectation_ const &expectation) {
  NurbsBookExe3_8Bezier(expectation);

  Expectation_ const &b_spline_first1 = EXPECT_CALL(*this, Erase(k12)).After(expectation);
  Expectation_ const &b_spline_second1 = EXPECT_CALL(*this, Erase(k7)).After(b_spline_first1);
  EXPECT_CALL(*this, Erase(k2)).After(b_spline_second1)
      .WillOnce(InvokeWithoutArgs(this, &A3dVectorSpaceMock::NurbsBookExe3_8));
}

void A3dVectorSpaceMock::NurbsBookExe3_8ElevateReduce(Expectation_ const &expectation) {
  coordinates_.assign({kCoordinate0_0, kCoordinateElevatedOnce1_0, kCoordinateElevatedOnce2_0_0,
      kCoordinateElevatedOnce2_0_1, kCoordinateElevatedOnce3_0, kCoordinate3_0, kCoordinate0_1,
      kCoordinateElevatedOnce1_1, kCoordinateElevatedOnce2_1_0, kCoordinateElevatedOnce2_1_1,
      kCoordinateElevatedOnce3_1, kCoordinate3_1, kCoordinate0_2, kCoordinateElevatedOnce1_2,
      kCoordinateElevatedOnce2_2_0, kCoordinateElevatedOnce2_2_1, kCoordinateElevatedOnce3_2, kCoordinate3_2});

  EXPECT_CALL(*this, OperatorSubscript(k2)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_0_1));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce2_1_1));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_1));
  EXPECT_CALL(*this, OperatorSubscript(k16)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateElevatedOnce3_2));
  EXPECT_CALL(*this, OperatorSubscript(k17)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_2));
}

void A3dVectorSpaceMock::NurbsBookExe3_8InsertRemove(Expectation_ const &expectation) {
  EXPECT_CALL(*this, OperatorSubscript(k0)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate0_0));
  EXPECT_CALL(*this, OperatorSubscript(k1)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate2_0));
  EXPECT_CALL(*this, OperatorSubscript(k3)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_0));
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted0_1));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted1_1));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted2_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted3_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted0_2));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted1_2));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted2_2));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted3_2));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate0_2));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate2_2));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(expectation).WillRepeatedly(ReturnRef(kCoordinate3_2));
}

void A3dVectorSpaceMock::NurbsBookExe3_8Subdivided(Expectation_ const &expectation) {
  EXPECT_CALL(*this, OperatorSubscript(k4)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted0_1));
  EXPECT_CALL(*this, OperatorSubscript(k5)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted1_1));
  EXPECT_CALL(*this, OperatorSubscript(k6)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted2_1));
  EXPECT_CALL(*this, OperatorSubscript(k7)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted3_1));
  EXPECT_CALL(*this, OperatorSubscript(k8)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateSubdivided0_2));
  EXPECT_CALL(*this, OperatorSubscript(k9)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateSubdivided1_2));
  EXPECT_CALL(*this, OperatorSubscript(k10)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateSubdivided2_2));
  EXPECT_CALL(*this, OperatorSubscript(k11)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateSubdivided3_2));
  EXPECT_CALL(*this, OperatorSubscript(k12)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted0_2));
  EXPECT_CALL(*this, OperatorSubscript(k13)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted1_2));
  EXPECT_CALL(*this, OperatorSubscript(k14)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted2_2));
  EXPECT_CALL(*this, OperatorSubscript(k15)).After(expectation).WillRepeatedly(ReturnRef(kCoordinateInserted3_2));
}

namespace {

using Coordinate4d = A4dVectorSpaceMock::Coordinate_;

constexpr Coordinate4d const kCoordinate4d1_0{k0_0, k1_0, k3_0, k1_0}, kCoordinate4d0_1{k2_0, k1_0, k1_0, k1_0},
                             kCoordinate4d1_1{k2_0, k0_0, k3_0, k1_0};

}  // namespace

Coordinate4d const & A4dVectorSpaceMock::operator[](Index const &coordinate) const {
  return OperatorSubscript(coordinate);
}

void A4dVectorSpaceMock::NurbsBookExe4_4() {
  constexpr Coordinate_ const kCoordinate4d0_0{k0_0, k0_0, k2_0, k2_0};

  coordinates_.assign({kCoordinate4d0_0, kCoordinate4d1_0, kCoordinate4d0_1, kCoordinate4d1_1});

  EXPECT_CALL(*this, OperatorSubscript(k0)).WillRepeatedly(ReturnRefOfCopy(kCoordinate4d0_0));
  EXPECT_CALL(*this, OperatorSubscript(k1)).WillRepeatedly(ReturnRef(kCoordinate4d1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).WillRepeatedly(ReturnRef(kCoordinate4d0_1));
  EXPECT_CALL(*this, OperatorSubscript(k3)).WillRepeatedly(ReturnRef(kCoordinate4d1_1));
}

void A4dVectorSpaceMock::NurbsBookExe4_4NonRational() {
  constexpr Coordinate_ const kCoordinate4d0_0{k0_0, k0_0, k1_0, k1_0};

  coordinates_.assign({kCoordinate4d0_0, kCoordinate4d1_0, kCoordinate4d0_1, kCoordinate4d1_1});

  EXPECT_CALL(*this, OperatorSubscript(k0)).WillRepeatedly(ReturnRefOfCopy(kCoordinate4d0_0));
  EXPECT_CALL(*this, OperatorSubscript(k1)).WillRepeatedly(ReturnRef(kCoordinate4d1_0));
  EXPECT_CALL(*this, OperatorSubscript(k2)).WillRepeatedly(ReturnRef(kCoordinate4d0_1));
  EXPECT_CALL(*this, OperatorSubscript(k3)).WillRepeatedly(ReturnRef(kCoordinate4d1_1));
}

void A4dVectorSpaceMock::SquareUnit04() {
  coordinates_.assign({Coordinate_{k0_0, k0_0, k0_0, k2_0}, Coordinate_{k2_0, k0_0, k0_0, k2_0},
                       Coordinate_{k0_0, k2_0, k0_0, k2_0}, Coordinate_{k2_0, k2_0, k0_0, k2_0}});
}

}  // namespace splinelib::tests::vector_spaces
