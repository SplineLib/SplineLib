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

#ifndef TESTS_PARAMETERSPACES_PARAMETER_SPACE_2D_HPP_
#define TESTS_PARAMETERSPACES_PARAMETER_SPACE_2D_HPP_

#include "Sources/ParameterSpaces/parameter_space.hpp"

namespace splinelib::tests::parameter_spaces {

class ParameterSpace2d final : public sources::parameter_spaces::ParameterSpace<2> {
 public:
  ParameterSpace2d() = default;
  ParameterSpace2d(KnotVectors_ knot_vectors, Degrees_ degrees, BSplineBasisFunctions_ basis_functions);
  ParameterSpace2d(ParameterSpace2d const &other) = default;
  ParameterSpace2d(ParameterSpace2d &&other) noexcept = default;
  ParameterSpace2d & operator=(ParameterSpace2d const &rhs) = default;
  ParameterSpace2d & operator=(ParameterSpace2d &&rhs) noexcept = default;
  ~ParameterSpace2d() = default;
};

}  // namespace splinelib::tests::parameter_spaces

#endif  // TESTS_PARAMETERSPACES_PARAMETER_SPACE_2D_HPP_
