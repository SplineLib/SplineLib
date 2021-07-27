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

#ifndef TOOLS_SOURCES_LOG_OPERATIONS_HPP_
#define TOOLS_SOURCES_LOG_OPERATIONS_HPP_

#include "Sources/InputOutput/vtk.hpp"
#include "Sources/Utilities/named_type.hpp"
#include "Sources/Utilities/std_container_operations.hpp"
#include "Sources/Utilities/string_operations.hpp"
#include "Sources/Utilities/system_operations.hpp"

// Log operations for converting and sampling splines.
//
// Example:
//   LogInformation log_info{Read<LogType::kConverter>(converter.log)};
//   SplinesConsidered iges_splines{RemoveSplinesOfTooHighDimensionalities<2, 3>(get<2>(log_info), splines_read)};
//   Append(converter.log, log_info_iges);
namespace splinelib::tools::sources::log_operations {

enum class LogType { kConverter, kSampler };
using InputStream = splinelib::sources::utilities::system_operations::InputStream;
using NumbersOfParametricCoordinates = splinelib::sources::input_output::vtk::NumbersOfParametricCoordinates;
using SplinesConsidered = Vector<Index>;
using SplinesRead = splinelib::sources::input_output::Splines;
using LogInformation = Tuple<String, String, SplinesConsidered, NumbersOfParametricCoordinates>;

void Append(String const &name_log, LogInformation const &log_information);
template<LogType log_type>
LogInformation Read(String const name_log);

String SkipBlankLineAndReadSectionIdentifier(InputStream &log);
template<int maximum_parametric_dimensionality, int maximum_dimensionality>
SplinesConsidered RemoveSplinesOfTooHighDimensionalities(SplinesConsidered const &splines_considered,
    SplinesRead &splines_read, NumbersOfParametricCoordinates * const numbers_of_parametric_coordinates = nullptr);

#ifndef NDEBUG
void ThrowIfCommandLineArgumentsAreInvalid(int const &argument_count);
#endif

#include "Tools/Sources/log_operations.inc"

}  // namespace splinelib::tools::sources::log_operations

#endif  // TOOLS_SOURCES_LOG_OPERATIONS_HPP_
