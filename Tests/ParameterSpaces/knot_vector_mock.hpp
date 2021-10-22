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

#ifndef TESTS_PARAMETERSPACES_KNOT_VECTOR_MOCK_HPP_
#define TESTS_PARAMETERSPACES_KNOT_VECTOR_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/ParameterSpaces/knot_vector.hpp"

namespace splinelib::tests::parameter_spaces {

class AKnotVectorMock : public sources::parameter_spaces::KnotVector {
 private:
  using Tolerance_ = sources::parameter_spaces::Tolerance;

  constexpr static Multiplicity const &kMultiplicity_ = sources::parameter_spaces::kMultiplicity;
  constexpr static Precision const &kPrecision_ = sources::parameter_spaces::kPrecision;
  constexpr static Tolerance_ const &kEpsilon_ = sources::parameter_spaces::kEpsilon;

 public:
  MOCK_METHOD(Knot_ const &, OperatorSubscript, (Index const &), (const));
  Knot_ const & operator[](Index const &index) const final;

  MOCK_METHOD(int, GetSize, (), (const final));
  MOCK_METHOD(Knot_ const &, GetFront, (), (const final));
  MOCK_METHOD(Knot_ const &, GetBack, (), (const final));

  MOCK_METHOD(bool, DoesParametricCoordinateEqualBackMock, (ParametricCoordinate const &, Tolerance_ const &), (const));
  bool DoesParametricCoordinateEqualBack(ParametricCoordinate const &parametric_coordinate,
                                         Tolerance_ const &tolerance = kEpsilon_) const final;
  MOCK_METHOD(bool, DoesParametricCoordinateEqualFrontOrBackMock, (ParametricCoordinate const &, Tolerance_ const &),
              (const));
  bool DoesParametricCoordinateEqualFrontOrBack(ParametricCoordinate const &parametric_coordinate,
                                                Tolerance_ const &tolerance = kEpsilon_) const final;
  MOCK_METHOD(KnotSpan, FindSpanMock, (ParametricCoordinate const &, Tolerance_ const &), (const));
  KnotSpan FindSpan(ParametricCoordinate const &parametric_coordinate, Tolerance_ const &tolerance = kEpsilon_) const
      final;
  MOCK_METHOD(Multiplicity, DetermineMultiplicityMock, (ParametricCoordinate const &, Tolerance_ const &), (const));
  Multiplicity DetermineMultiplicity(ParametricCoordinate const &knot, Tolerance_ const &tolerance = kEpsilon_) const;
  MOCK_METHOD(Knots_, GetUniqueKnotsMock, (Tolerance_ const &), (const));
  Knots_ GetUniqueKnots(Tolerance_ const &tolerance = kEpsilon_) const final;

  MOCK_METHOD(void, InsertMock, (ParametricCoordinate, Multiplicity const &, Tolerance_ const &), (const));
  void Insert(ParametricCoordinate knot, Multiplicity const &multiplicity, Tolerance_ const &tolerance = kEpsilon_)
      final;
  MOCK_METHOD(Multiplicity, RemoveMock, (ParametricCoordinate const &, Multiplicity const &, Tolerance_ const &), ());
  Multiplicity Remove(ParametricCoordinate const &knot, Multiplicity const &multiplicity = kMultiplicity_,
                      Tolerance_ const &tolerance = kEpsilon_) final;
  MOCK_METHOD(void, IncreaseMultiplicitiesMock, (Multiplicity const &, Tolerance_ const &), ());
  void IncreaseMultiplicities(Multiplicity const &multiplicity = kMultiplicity_,
                              Tolerance_ const &tolerance = kEpsilon_) final;
  MOCK_METHOD(void, DecreaseMultiplicitiesMock, (Multiplicity const &, Tolerance_ const &), ());
  void DecreaseMultiplicities(Multiplicity const &multiplicity = kMultiplicity_,
                              Tolerance_ const &tolerance = kEpsilon_) final;

  MOCK_METHOD(OutputInformation_, WriteMock, (Precision const &), (const));
  OutputInformation_ Write(Precision const &precision = kPrecision_) const final;

#ifndef NDEBUG
  MOCK_METHOD(void, ThrowIfParametricCoordinateIsOutsideScopeMock, (ParametricCoordinate const &, Tolerance_ const &),
              (const));
  void ThrowIfParametricCoordinateIsOutsideScope(ParametricCoordinate const &parametric_coordinate,
                                                 Tolerance_ const &tolerance = kEpsilon_) const final;
#endif

  void NurbsBookExa2_1();  // {0.0, 0.0, 0.0, 1.0, 1.0, 1.0} (cf. NURBS book Exa. 2.1)
  void NurbsBookExa2_1Perturbed();  // {0.0, 0.0, 0.0 + (1.1 * eps), 1.0 + (1.1 * eps), 1.0, 1.0}
  void NurbsBookExa2_2();  // {0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 4.0, 5.0, 5.0, 5.0} (cf. NURBS book Exa. 2.2)
  // {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 2.0, 2.0, 3.0, 3.0, 4.0, 4.0, 4.0, 5.0, 5.0, 5.0, 5.0}
  void NurbsBookExa2_2IncreasedOnce();
  // {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0, 4.0, 5.0, 5.0, 5.0, 5.0, 5.0}
  void NurbsBookExa2_2IncreasedTwice();
  void NurbsBookExa2_2Interior();  // {0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 4.0, 4.0, 5.0, 5.0, 5.0}
  // {0.0, 0.0, 0.0, (1.0 + 1.1 * eps), 2.0, 3.0, 4.0, 4.0, (5.0 + 1.1 * eps), 5.0, 5.0}
  void NurbsBookExa2_2Perturbed();
  void NurbsBookExa2_2Unclamped();  // {0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 4.0, 5.0, 5.0, 5.0}
  void NurbsBookExe3_8_0();  // {0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 1.0} (cf. NURBS book Exe. 3.8 U)
  void NurbsBookExe3_8_0IncreaseDecrease();  // {0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0}
  void NurbsBookExe3_8_0IncreasedTwice();  // {0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0}
  void NurbsBookExe3_8_0Subdivided();  // {0.0, 0.0, 0.0, 0.5, 0.5, 1.0, 1.0, 1.0}
  void NurbsBookExe4_4();  // {0.0, 0.0, 1.0, 1.0} (cf. NURBS book Exe. 4.4)
  void NurbsBookExe4_4Perturbed();  // {0.0, 0.0, 1.0 + (1.1 * eps), 1.0}
};

namespace mock_knot_vectors {

using KnotVectors = sources::parameter_spaces::KnotVectors<2>;

KnotVectors Empty();
KnotVectors NurbsBookExa2_2();
KnotVectors NurbsBookExa2_2IncreasedOnce();
KnotVectors NurbsBookExa2_2IncreasedTwice();
KnotVectors NurbsBookExa2_2Inserted();
KnotVectors NurbsBookExa2_2Subdivided();
KnotVectors NurbsBookExe3_8();
KnotVectors NurbsBookExe3_8IncreaseDecrease();
KnotVectors NurbsBookExe3_8IncreasedTwice();
KnotVectors NurbsBookExe3_8InsertRemove();
KnotVectors NurbsBookExe3_8Perturbed();
KnotVectors NurbsBookExe3_8Subdivided();
KnotVectors NurbsBookExe4_4();
KnotVectors NurbsBookExe4_4Perturbed();

}  // namespace mock_knot_vectors

}  // namespace splinelib::tests::parameter_spaces

#endif  // TESTS_PARAMETERSPACES_KNOT_VECTOR_MOCK_HPP_
