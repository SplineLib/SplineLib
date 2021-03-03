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

#ifndef TESTS_VECTORSPACES_WEIGHTED_VECTOR_SPACE_3D_HPP_
#define TESTS_VECTORSPACES_WEIGHTED_VECTOR_SPACE_3D_HPP_

#include "Sources/VectorSpaces/weighted_vector_space.hpp"

namespace splinelib::tests::vector_spaces {

class WeightedVectorSpace3d final : public sources::vector_spaces::WeightedVectorSpace<3> {
 public:
  WeightedVectorSpace3d() = default;
  WeightedVectorSpace3d(WeightedVectorSpace3d const &other) = default;
  WeightedVectorSpace3d(WeightedVectorSpace3d &&other) noexcept = default;
  WeightedVectorSpace3d & operator=(WeightedVectorSpace3d const &rhs) = default;
  WeightedVectorSpace3d & operator=(WeightedVectorSpace3d &&rhs) noexcept = default;
  WeightedVectorSpace3d & operator=(Base_ &&rhs) noexcept;
  ~WeightedVectorSpace3d() = default;
};

}  // namespace splinelib::tests::vector_spaces

#endif  // TESTS_VECTORSPACES_WEIGHTED_VECTOR_SPACE_3D_HPP_
