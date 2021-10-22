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

#ifndef TESTS_PARAMETERSPACES_PARAMETER_SPACE_MOCK_HPP_
#define TESTS_PARAMETERSPACES_PARAMETER_SPACE_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/ParameterSpaces/parameter_space.hpp"

namespace splinelib::tests::parameter_spaces {

class A2dParameterSpaceMock : public sources::parameter_spaces::ParameterSpace<2> {
 private:
  using Tolerance_ = sources::parameter_spaces::Tolerance;

  constexpr static Multiplicity const &kMultiplicity_ = sources::parameter_spaces::kMultiplicity;
  constexpr static Precision const &kPrecision_ = sources::parameter_spaces::kPrecision;
  constexpr static Tolerance_ const &kEpsilon_ = sources::parameter_spaces::kEpsilon;

 public:
  MOCK_METHOD(Index_, First, (), (const, final));
  MOCK_METHOD(Index_, Behind, (), (const, final));

  MOCK_METHOD(NumberOfBasisFunctions_, GetNumberOfBasisFunctions, (), (const, final));
  MOCK_METHOD(int, GetTotalNumberOfBasisFunctions, (), (const, final));

  MOCK_METHOD(Index_, FindFirstNonZeroBasisFunctionMock, (ParametricCoordinate_ const &, Tolerance_ const &), (const));
  Index_ FindFirstNonZeroBasisFunction(ParametricCoordinate_ const &parametric_coordinate,
                                       Tolerance_ const &tolerance = kEpsilon_) const final;
  MOCK_METHOD(BezierInformation_, DetermineBezierExtractionKnotsMock, (Dimension const &, Tolerance_ const &), (const));
  BezierInformation_ DetermineBezierExtractionKnots(Dimension const &dimension, Tolerance_ const &tolerance = kEpsilon_)
      const final;

  MOCK_METHOD(Type_, EvaluateBasisFunctionMock, (Index_ const &, ParametricCoordinate_ const &, Tolerance_ const &),
              (const));
  Type_ EvaluateBasisFunction(Index_ const &basis_function_index, ParametricCoordinate_ const &parametric_coordinate,
                              Tolerance_ const &tolerance = kEpsilon_) const final;
  MOCK_METHOD(Type_, EvaluateBasisFunctionDerivativeMock, (Index_ const &, ParametricCoordinate_ const &,
                                                           Derivative_ const &, Tolerance_ const &), (const));
  Type_ EvaluateBasisFunctionDerivative(Index_ const &basis_function_index,
      ParametricCoordinate_ const &parametric_coordinate, Derivative_ const &derivative,
      Tolerance_ const &tolerance = kEpsilon_) const final;

  MOCK_METHOD(InsertionInformation_, InsertKnotMock, (Dimension const &, Knot_, Multiplicity const &,
                                                      Tolerance_ const &), ());
  InsertionInformation_ InsertKnot(Dimension const &dimension, Knot_ knot,
      Multiplicity const &multiplicity = kMultiplicity_, Tolerance_ const &tolerance = kEpsilon_) final;
  MOCK_METHOD(InsertionInformation_, RemoveKnotMock, (Dimension const &, Knot_ const &, Multiplicity const &,
                                                      Tolerance_ const &), ());
  InsertionInformation_ RemoveKnot(Dimension const &dimension, Knot_ const &knot,
      Multiplicity const &multiplicity = kMultiplicity_, Tolerance_ const &tolerance = kEpsilon_) final;
  MOCK_METHOD(ElevationInformation_, ElevateDegreeMock, (Dimension const &, Multiplicity const &, Tolerance_ const &),
              ());
  ElevationInformation_ ElevateDegree(Dimension const &dimension, Multiplicity const &multiplicity = kMultiplicity_,
                                      Tolerance_ const &tolerance = kEpsilon_) final;
  MOCK_METHOD(ElevationInformation_, ReduceDegreeMock, (Dimension const &, Multiplicity const &, Tolerance_ const &),
              ());
  ElevationInformation_ ReduceDegree(Dimension const &dimension, Multiplicity const &multiplicity = kMultiplicity_,
                                     Tolerance_ const &tolerance = kEpsilon_) final;

  MOCK_METHOD(ParametricCoordinates_, Sample, (NumberOfParametricCoordinates_ const &), (const));
  MOCK_METHOD(OutputInformation_, WriteMock, (Precision const &), (const));
  OutputInformation_ Write(Precision const &precision = kPrecision_) const final;

#ifndef NDEBUG
  MOCK_METHOD(void, ThrowIfParametricCoordinateIsOutsideScopeMock, (Dimension const &, ParametricCoordinate const &,
                                                                    Tolerance_ const &), (const));
  void ThrowIfParametricCoordinateIsOutsideScope(Dimension const &dimension,
      ParametricCoordinate const &parametric_coordinate, Tolerance_ const &tolerance = kEpsilon_) const final;
#endif

  void NurbsBookExe3_8();  // See NURBS book Exe. 3.8.
  void NurbsBookExe3_8ElevateReduce();
  void NurbsBookExe3_8ElevatedTwice();
  void NurbsBookExe3_8InsertRemove();
  void NurbsBookExe3_8KnotVector();
  void NurbsBookExe3_8Subdivided();
  void NurbsBookExe3_8Unsuccessful();
  void NurbsBookExe4_4();  // See NURBS book Exe. 4.4.
  void NurbsBookExe4_4KnotVector();
  void SquareUnitFirstOrderBezier();
  void SquareUnitSecondOrderMaximallySmooth();

 private:
  void NurbsBookExe3_8Bezier();
  void NurbsBookExe3_8BezierElevateReduce();
  void NurbsBookExe3_8BezierElevatedTwice();
  void NurbsBookExe3_8InsertRemoveKnotVectorsDegreesBasisFunctions();
  void NurbsBookExe3_8KnotVectorsDegrees();
  void NurbsBookExe4_4KnotVectorsDegrees();
};

}  // namespace splinelib::tests::parameter_spaces

#endif  // TESTS_PARAMETERSPACES_PARAMETER_SPACE_MOCK_HPP_
