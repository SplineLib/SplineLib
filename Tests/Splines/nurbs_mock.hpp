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

#ifndef TESTS_SPLINES_NURBS_MOCK_HPP_
#define TESTS_SPLINES_NURBS_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/Splines/nurbs.hpp"

namespace splinelib::tests::splines {

using sources::splines::Nurbs;

class A2d3dNurbsMock : public Nurbs<2, 3> {
 public:
  void SquareUnitFirstOrderBezier();  // {0; 0; 1; 1}^2 —> {[0; 1]^2, 0}
};

}  // namespace splinelib::tests::splines

#endif  // TESTS_SPLINES_NURBS_MOCK_HPP_
