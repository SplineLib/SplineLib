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

#ifndef TESTS_UTILITIES_INDEX_MOCK_HPP_
#define TESTS_UTILITIES_INDEX_MOCK_HPP_

#include <gmock/gmock.h>
#include "Sources/Utilities/index.hpp"

namespace splinelib::tests::utilities {

class A2dIndexMock : public sources::utilities::Index<2> {
 public:
  MOCK_METHOD(Index_ const &, OperatorSubscript, (Dimension const &), (const));
  Index_ const & operator[](Dimension const &dimension) const final;

  // See NURBS book Exa. 2.2: {8, 3}.
  void NurbsBookExa2_2_1_0();  // {1, 0}, false
#ifndef NDEBUG
  void NurbsBookExa2_2_1_3();  // {1, 3}, false
#endif
};

}  // namespace splinelib::tests::utilities

#endif  // TESTS_UTILITIES_INDEX_MOCK_HPP_
