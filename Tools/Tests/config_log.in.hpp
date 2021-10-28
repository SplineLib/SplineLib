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

#ifndef TOOLS_TESTS_CONFIG_LOG_IN_HPP_
#define TOOLS_TESTS_CONFIG_LOG_IN_HPP_

namespace splinelib::tools::tests {

char const * const xml_file{"@xml_file@"}, * const xml_itd{"@xml_itd@"}, * const log_converter{"@log_converter@"},
           * const log_invalid_numbers_of_parametric_coordinates{"@log_invalid_numbers_of_parametric_coordinates@"},
           * const log_invalid_splines{"@log_invalid_splines@"}, * const log_sampler{"@log_sampler@"},
           * const itd_vtk{"@itd_vtk@"};

}  // namespace splinelib::tools::tests

#endif  // TOOLS_TESTS_CONFIG_LOG_IN_HPP_
