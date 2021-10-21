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

#ifndef PYTHON_SOURCES_KNOT_VECTOR_BINDING_HPP_
#define PYTHON_SOURCES_KNOT_VECTOR_BINDING_HPP_

#include <utility>

#include "Sources/ParameterSpaces/knot_vector.hpp"

namespace splinelib::python::sources {

class KnotVector final : public splinelib::sources::parameter_spaces::KnotVector {
 public:
  using Base_ = splinelib::sources::parameter_spaces::KnotVector;
  using Base_::Knots_, Base_::knots_;

  KnotVector() = default;
  explicit KnotVector(Knots_ knots);
  KnotVector(KnotVector const &other) = delete;
  KnotVector(KnotVector &&other) noexcept = default;
  KnotVector & operator=(KnotVector const &rhs) = delete;
  KnotVector & operator=(KnotVector &&rhs) noexcept = default;
  ~KnotVector() = default;
};

}  // namespace splinelib::python::sources

#endif  // PYTHON_SOURCES_KNOT_VECTOR_BINDING_HPP_
