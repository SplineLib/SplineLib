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

#ifndef PYTHON_SOURCES_PARAMETER_SPACE_BINDING_HPP_
#define PYTHON_SOURCES_PARAMETER_SPACE_BINDING_HPP_

#include <utility>

#include "Python/Sources/knot_vector_binding.hpp"
#include "Sources/ParameterSpaces/parameter_space.hpp"
#include "Sources/Utilities/std_container_operations.hpp"

namespace splinelib::python::sources {

template<int parametric_dimensionality>
class ParameterSpace : public splinelib::sources::parameter_spaces::ParameterSpace<parametric_dimensionality> {
 public:
  using Base_ = splinelib::sources::parameter_spaces::ParameterSpace<parametric_dimensionality>;
  using KnotVector_ = KnotVector;
  using KnotVectorsBase_ = typename Base_::KnotVectors_;
  using KnotVectors_ = Array<typename KnotVector_::Knots_ const *, parametric_dimensionality>;
  using typename Base_::Degrees_, Base_::degrees_;

  ParameterSpace() = default;
  ParameterSpace(KnotVectorsBase_ knot_vectors, Degrees_ degrees);
  ParameterSpace(ParameterSpace const &other) = delete;
  ParameterSpace(ParameterSpace &&other) noexcept = default;
  ParameterSpace & operator=(ParameterSpace const &rhs) = delete;
  ParameterSpace & operator=(ParameterSpace &&rhs) noexcept = default;
  ~ParameterSpace() final = default;
};

#include "Python/Sources/parameter_space_binding.inc"

}  // namespace splinelib::python::sources

#endif  // PYTHON_SOURCES_PARAMETER_SPACE_BINDING_HPP_
