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

#include "Tests/Splines/nurbs_2d_to_3d.hpp"

#include <utility>

namespace splinelib::tests::splines {

using std::move;

Nurbs2dTo3d::Nurbs2dTo3d(SharedPointer<ParameterSpace_> parameter_space,
    SharedPointer<WeightedVectorSpace_> weighted_vector_space,
    SharedPointer<HomogeneousBSpline_> homogeneous_b_spline) : Nurbs{move(parameter_space), move(weighted_vector_space)}
{
  homogeneous_b_spline_ = move(homogeneous_b_spline);
}

}  // namespace splinelib::tests::splines
