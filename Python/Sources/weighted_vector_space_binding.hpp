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

#ifndef PYTHON_SOURCES_WEIGHTED_VECTOR_SPACE_BINDING_HPP_
#define PYTHON_SOURCES_WEIGHTED_VECTOR_SPACE_BINDING_HPP_

#include <utility>

#include "Python/Sources/vector_space_binding.hpp"
#include "Sources/VectorSpaces/weighted_vector_space.hpp"

namespace splinelib::python::sources {

template<int dimensionality>
class WeightedVectorSpace : public splinelib::sources::vector_spaces::WeightedVectorSpace<dimensionality> {
 public:
  using Base_ = splinelib::sources::vector_spaces::WeightedVectorSpace<dimensionality>;
  using HomogeneousCoordinates_ = typename Base_::Base_::Coordinates_;
  using typename Base_::Coordinates_, typename Base_::Weights_;

  SharedPointer<HomogeneousCoordinates_> homogeneous_coordinates_;

  WeightedVectorSpace() = default;
  WeightedVectorSpace(Coordinates_ coordinates, Weights_ weights);
  WeightedVectorSpace(WeightedVectorSpace const &other) = delete;
  WeightedVectorSpace(WeightedVectorSpace &&other) noexcept = default;
  WeightedVectorSpace & operator=(WeightedVectorSpace const &rhs) = delete;
  WeightedVectorSpace & operator=(WeightedVectorSpace &&rhs) noexcept = default;
  ~WeightedVectorSpace() final = default;
};

#include "Python/Sources/weighted_vector_space_binding.inc"

}  // namespace splinelib::python::sources

#endif  // PYTHON_SOURCES_WEIGHTED_VECTOR_SPACE_BINDING_HPP_
