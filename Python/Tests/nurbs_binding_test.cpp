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

#include <utility>

#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include "Python/Sources/nurbs_binding.hpp"
#include "Tests/Splines/nurbs_mock.hpp"

namespace splinelib::python::tests {

inline pybind11::scoped_interpreter const guard{};

using sources::Nurbs;

// Test NURBS binding.
class NurbsBindingSuite : public testing::Test {
 protected:
  using Nurbs_ = Nurbs<2, 3>;
  using CoordinatePython_ = Nurbs_::CoordinatePython_;
  using Coordinates_ = Nurbs_::CoordinatesPython_;
  using Degrees_ = Nurbs_::DegreesPython_;
  using Knot_ = Nurbs_::KnotPython_;
  using KnotVector_ = Nurbs_::KnotVectorPython_;
  using KnotVectors_ = Nurbs_::KnotVectorsPython_;
  using ScalarCoordinate_ = Nurbs_::ScalarCoordinatePython_;
  using Weights_ = Nurbs_::WeightsPython_;
  using CoordinateCpp_ = ScalarCoordinate_[3];
  using Degree_ = Degrees_::value_type;
  using Weight_ = Nurbs_::WeightPython_;

  constexpr inline static Degree_ const kDegree1_{1}, kDegreesRaw_[2]{kDegree1_, kDegree1_};
  constexpr inline static Knot_ const kKnot1_0_{1.0};
  constexpr inline static ScalarCoordinate_ const kScalarCoordinate0_0_{0.0}, kScalarCoordinate1_0_{1.0};
  constexpr inline static Weight_ const kWeight2_0_{2.0};
  inline static CoordinatePython_ const kCoordinate0_{3, (CoordinateCpp_){kScalarCoordinate0_0_, kScalarCoordinate0_0_,
      kScalarCoordinate0_0_}}, kCoordinate1_{3, (CoordinateCpp_){kScalarCoordinate1_0_, kScalarCoordinate0_0_,
          kScalarCoordinate0_0_}}, kCoordinate2_{3, (CoordinateCpp_){kScalarCoordinate0_0_, kScalarCoordinate1_0_,
              kScalarCoordinate0_0_}}, kCoordinate3_{3, (CoordinateCpp_){kScalarCoordinate1_0_, kScalarCoordinate1_0_,
                  kScalarCoordinate0_0_}};
  Degrees_ degrees_;
  KnotVector_ knot_vector_;
  KnotVectors_ knot_vectors_;
  Coordinates_ coordinates_;
  Weights_ weights_;
  Nurbs_ nurbs_;

  NurbsBindingSuite();
};

NurbsBindingSuite::NurbsBindingSuite() {
  constexpr static Knot_ const kKnot0_0{0.0};

  knot_vector_ = KnotVector_(4);
  knot_vector_[0] = kKnot0_0; knot_vector_[1] = kKnot0_0; knot_vector_[2] = kKnot1_0_; knot_vector_[3] = kKnot1_0_;
  knot_vectors_ = KnotVectors_(2);
  knot_vectors_[0] = knot_vector_; knot_vectors_[1] = knot_vector_;
  degrees_ = Degrees_(2, kDegreesRaw_);
  coordinates_ = Coordinates_(4);
  coordinates_[0] = kCoordinate0_; coordinates_[1] = kCoordinate1_;
  coordinates_[2] = kCoordinate2_; coordinates_[3] = kCoordinate3_;
  weights_ = Weights_(4);
  weights_[0] = kWeight2_0_; weights_[1] = kWeight2_0_; weights_[2] = kWeight2_0_; weights_[3] = kWeight2_0_;

  nurbs_ = Nurbs_(knot_vectors_, degrees_, coordinates_, weights_);
}

TEST_F(NurbsBindingSuite, ParameterizedConstructor) {
  testing::StrictMock<splinelib::tests::splines::A2d3dNurbsMock> nurbs_mock;
  nurbs_mock.SquareUnitFirstOrderBezier();
  EXPECT_TRUE(nurbs_ == nurbs_mock);

  EXPECT_EQ((*nurbs_.knot_vectors_[0])[2].Get(), 1.0);
  EXPECT_EQ((*nurbs_.degrees_)[0].Get(), 1);
  EXPECT_EQ((*nurbs_.homogeneous_coordinates_)[0][1].Get(), 0.0);
  EXPECT_EQ((*nurbs_.homogeneous_coordinates_)[0][3].Get(), 2.0);
}

#ifndef NDEBUG
TEST_F(NurbsBindingSuite, ThrowIfTooFewOrTooManyKnotVectorsAndWrongNumberOfOrWronglyShapedDegreesOrCoordinates) {
  using CoordinateWrongNumber = ScalarCoordinate_[2];
  using DegreesWrongNumber = Degree_[1];
  using std::move;

  KnotVectors_ knot_vectors(1);
  knot_vectors[0] = knot_vector_;
  EXPECT_THROW(Nurbs_(move(knot_vectors), degrees_, coordinates_, weights_), DomainError);

  EXPECT_THROW(Nurbs_(knot_vectors_, move(Degrees_(1, move(DegreesWrongNumber{kDegree1_}))), coordinates_, weights_),
               DomainError);
  Degrees_ degrees_shape({1, 2}, kDegreesRaw_);
  EXPECT_THROW(Nurbs_(knot_vectors_, move(degrees_shape), coordinates_, weights_), DomainError);

  Coordinates_ coordinates_wrong_number(4);
  coordinates_wrong_number[0] = CoordinatePython_(2, move(CoordinateWrongNumber{kScalarCoordinate0_0_,
                                                                                kScalarCoordinate0_0_}));
  coordinates_wrong_number[1] = kCoordinate1_;
  coordinates_wrong_number[2] = kCoordinate2_;
  coordinates_wrong_number[3] = kCoordinate3_;
  EXPECT_THROW(Nurbs_(knot_vectors_, degrees_, move(coordinates_wrong_number), weights_), DomainError);
  Coordinates_ coordinates_shape(4);
  coordinates_shape[0] = kCoordinate0_;
  coordinates_shape[1] = kCoordinate1_;
  coordinates_shape[2] = kCoordinate2_;
  coordinates_shape[3] = CoordinatePython_({3, 1}, move(CoordinateCpp_{kScalarCoordinate1_0_, kScalarCoordinate1_0_,
                                                                       kScalarCoordinate0_0_}));
  EXPECT_THROW(Nurbs_(knot_vectors_, degrees_, move(coordinates_shape), weights_), DomainError);
}
#endif

}  // namespace splinelib::python::tests
