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

#include <iostream>

#include "Sources/InputOutput/operations.hpp"
#include "Sources/InputOutput/vtk.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/string_operations.hpp"
#include "Tools/Sources/log_operations.hpp"

using namespace splinelib;  // NOLINT(build/namespaces)
using namespace splinelib::sources::input_output;  // NOLINT(build/namespaces)
using namespace splinelib::tools::sources::log_operations;  // NOLINT(build/namespaces)
using FileFormat = operations::FileFormat;
using std::cout, std::endl, std::to_string;

// Samples splines and outputs VTK files.
//
// Example:
//   $ sampler --help (explains usage)
//   $ sampler sampler.log
int main(int argc, char *argv[]) {
#ifndef NDEBUG
  try {
    ThrowIfCommandLineArgumentsAreInvalid(argc);
#endif
    String const name_log{argv[1]};
    auto const &[name_input, name_output, splines, numbers_of_parametric_coordinates] =
        Read<LogType::kSampler>(name_log);
    SplinesRead splines_read{operations::Read(name_input)};
    SplinesConsidered splines_sampled;
#ifndef NDEBUG
    int const &number_of_splines_read = splines_read.size(),
              &numbers_of_parametric_coordinates_size = numbers_of_parametric_coordinates.size();
    if (number_of_splines_read != numbers_of_parametric_coordinates_size)
      throw RuntimeError(to_string(number_of_splines_read) + " splines were given, but " +
          to_string(numbers_of_parametric_coordinates_size) + " numbers of parametric coordinates were provided.");
#endif
    if (operations::DetermineFileFormat(name_output) == FileFormat::kVtk) {
      NumbersOfParametricCoordinates numbers_of_parametric_coordinates_read{numbers_of_parametric_coordinates};
      splines_sampled = RemoveSplinesOfTooHighDimensionalities<3, 3>(splines, splines_read,
                                                                     &numbers_of_parametric_coordinates_read);
      vtk::Sample(splines_read, name_output, numbers_of_parametric_coordinates_read);
    } else {
#ifndef NDEBUG
      throw RuntimeError("Output of spline sampling must be stored in VTK (.vtk) files.");
#endif
    }
    Append(name_log, {name_input, name_output, splines_sampled, numbers_of_parametric_coordinates});
    cout << "Sampling succeeded: Check the information appended to the log file for further information." << endl;
#ifndef NDEBUG
  } catch (RuntimeError const &exception) { cout << exception.what() << endl; }
#endif

  return 0;
}
