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

#include "Tools/Sources/log_operations.hpp"

#include "Sources/Utilities/string_operations.hpp"
#include "Sources/Utilities/system_operations.hpp"

namespace splinelib::tools::sources::log_operations {

namespace system_operations = splinelib::sources::utilities::system_operations;

void Append(String const &name_log, LogInformation const &log_information) {
  using OutputStream = system_operations::OutputStream;
  using std::get, splinelib::sources::utilities::string_operations::Write;

  OutputStream log{system_operations::Open<OutputStream, system_operations::kModeAppend>(name_log)};
  system_operations::LocalTime const &timeinfo = system_operations::GetLocalTime();
  log << "\nlog:\n" << std::asctime(&timeinfo);
  std::tuple_element_t<2, LogInformation> const &splines = get<2>(log_information);
  int const &number_of_splines = splines.size();
  bool const &is_single_spline = (number_of_splines == 1);
  if (number_of_splines > 0) {
    String const &plural = (is_single_spline ? "" : "s");
    log << "The spline" << plural << " at position" << plural << " ";
    Index::Type_ spline{};
    for (; spline < (number_of_splines - 1); ++spline)
        log << Write(splines[spline]) << (number_of_splines == 2 ? " " : ", ");
    log << (is_single_spline ? "" : "and ") << Write(splines[spline]);
  } else {
    log << "No splines";
  }
  log << " in the file \"" << get<0>(log_information) << "\" " << (is_single_spline ? "was" : "were")
      << " considered and exported to the file \"" << get<1>(log_information) << "\".\n";
}

String SkipBlankLineAndReadSectionIdentifier(InputStream &log) {
  using std::getline;

  String section_identifier;
  getline(log, section_identifier);
  getline(log, section_identifier);
  return section_identifier;
}

#ifndef NDEBUG
void ThrowIfCommandLineArgumentsAreInvalid(int const &argument_count) {
  if (argument_count != 2) throw RuntimeError("Exactly one of the options -h or --help, or one log filename must be "
                                              "provided as command line argument.");
}
#endif
}  // namespace splinelib::tools::sources::log_operations
