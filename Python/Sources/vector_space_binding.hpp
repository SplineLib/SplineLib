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

#ifndef PYTHON_SOURCES_VECTOR_SPACE_BINDING_HPP_
#define PYTHON_SOURCES_VECTOR_SPACE_BINDING_HPP_

#include <utility>

#include "Sources/VectorSpaces/vector_space.hpp"

namespace splinelib::python::sources {

template<int dimensionality>
class VectorSpace : public splinelib::sources::vector_spaces::VectorSpace<dimensionality> {
 public:
  using Base_ = splinelib::sources::vector_spaces::VectorSpace<dimensionality>;
  using typename Base_::Coordinates_, Base_::coordinates_;

  VectorSpace() = default;
  explicit VectorSpace(Coordinates_ coordinates);
  VectorSpace(VectorSpace const &other) = delete;
  VectorSpace(VectorSpace &&other) noexcept = default;
  VectorSpace & operator=(VectorSpace const &rhs) = delete;
  VectorSpace & operator=(VectorSpace &&rhs) noexcept = default;
  ~VectorSpace() override = default;
};

#include "Python/Sources/vector_space_binding.inc"

}  // namespace splinelib::python::sources

#endif  // PYTHON_SOURCES_VECTOR_SPACE_BINDING_HPP_
