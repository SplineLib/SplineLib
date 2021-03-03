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

#include "Sources/InputOutput/iges.hpp"
#include "Sources/InputOutput/irit.hpp"
#include "Sources/InputOutput/operations.hpp"
#include "Sources/InputOutput/xml.hpp"
#include "Sources/Utilities/error_handling.hpp"
#include "Tools/Sources/log_operations.hpp"

using namespace splinelib;  // NOLINT(build/namespaces)
using namespace splinelib::sources::input_output;  // NOLINT(build/namespaces)
using namespace splinelib::tools::sources::log_operations;  // NOLINT(build/namespaces)
using FileFormat = operations::FileFormat;
using std::cout, std::endl;

// Converts splines between formats IGES, IRIT, and XML.
//
// Example:
//   $ converter --help (explains usage)
//   $ converter converter.log
int main(int argc, char *argv[]) {
#ifndef NDEBUG
  try {
    ThrowIfCommandLineArgumentsAreInvalid(argc);
#endif
    String const name_log{argv[1]};
    auto const &[name_input, name_output, splines, ignored] = Read<LogType::kConverter>(name_log);
    SplinesRead splines_read{operations::Read(name_input)};
    SplinesConsidered splines_converted;
    switch (operations::DetermineFileFormat(name_output)) {
      case FileFormat::kIges:
        splines_converted = RemoveSplinesOfTooHighDimensionalities<2, 3>(splines, splines_read);
        iges::Write(splines_read, name_output);
        break;
      case FileFormat::kIrit:
        splines_converted = RemoveSplinesOfTooHighDimensionalities<3, 3>(splines, splines_read);
        irit::Write(splines_read, name_output);
        break;
      case FileFormat::kXml:
        splines_converted = RemoveSplinesOfTooHighDimensionalities<4, 9>(splines, splines_read);
        xml::Write(splines_read, name_output);
        break;
      default:
        break;
    }
    Append(name_log, {name_input, name_output, splines_converted, ignored});
    cout << "Conversion succeeded: Check the information appended to the log file for further information." << endl;
#ifndef NDEBUG
  } catch (RuntimeError const &exception) { cout << exception.what() << endl; }
#endif

  return 0;
}
