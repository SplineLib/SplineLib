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

template<LogType log_type>
LogInformation Read(String const name_log) {
  namespace string_operations = splinelib::sources::utilities::string_operations;
  namespace system_operations = splinelib::sources::utilities::system_operations;
  using std::get, std::tuple_element_t, string_operations::ConvertToNumbers, string_operations::StartsWith;

  constexpr bool const kIsSampler{log_type == LogType::kSampler};

  LogInformation log_information{};
#ifndef NDEBUG
  try {
    if ((name_log == "--help") || (name_log == "-h"))
        throw RuntimeError(Message{"The log file has to be of the following format (cf. example log files in Tools/"
            "Tests):\ninput:\n# path to the input file\n\noutput:\n# path to the output file\n\noptions:\n# list "
            "(separated by spaces) of positions of splines or \"all\" for all splines in the input file"} +
            (kIsSampler ? "\n\nnumbers of parametric coordinates for splines:\n# list (separated by line breaks) of "
                          "numbers of parametric coordinates (separated by spaces)" : ""));
#endif
    InputStream log{system_operations::Open<InputStream, system_operations::kModeIn>(name_log)};
    String input_section;
    getline(log, input_section);
    if (StartsWith(input_section, "input:")) {
      getline(log, get<0>(log_information));
    } else {
#ifndef NDEBUG
      throw RuntimeError("Log files must start with \"input:\" section.");
#endif
    }
    if (StartsWith(SkipBlankLineAndReadSectionIdentifier(log), "output:")) {
      getline(log, get<1>(log_information));
    } else {
#ifndef NDEBUG
      throw RuntimeError("The \"input:\" section must be followed by a blank line and then the \"output:\" section.");
#endif
    }
    if (StartsWith(SkipBlankLineAndReadSectionIdentifier(log), "splines:")) {
      String options;
      getline(log, options);
      SplinesConsidered &splines = get<2>(log_information);
      if (options == "all") {
        splines = SplinesConsidered{};
      } else {
#ifndef NDEBUG
        try {
#endif
          splines = ConvertToNumbers<SplinesConsidered::value_type>(options, ' ');
#ifndef NDEBUG
        } catch (...) {
          throw RuntimeError("Options value is neither \"all\" nor a list of spline positions separated by spaces.");
        }
#endif
      }
    } else {
#ifndef NDEBUG
      throw RuntimeError("The \"output:\" section must be followed by a blank line and then the \"splines:\" section.");
#endif
    }
    if constexpr (kIsSampler) {
      if (StartsWith(SkipBlankLineAndReadSectionIdentifier(log), "numbers of parametric coordinates for splines:")) {
#ifndef NDEBUG
        try {
#endif
          String numbers_of_parametric_coordinates;
          while (getline(log, numbers_of_parametric_coordinates) && (numbers_of_parametric_coordinates.size() != 0))
              get<3>(log_information).push_back(
                  ConvertToNumbers<NumbersOfParametricCoordinates::value_type::value_type>(
                      numbers_of_parametric_coordinates, ' '));
#ifndef NDEBUG
        } catch (...) {
          throw RuntimeError("The given numbers of parametric coordinates for splines are not a line-break–separated "
                             "list of space-separated numbers of parametric coordinates.");
        }
#endif
      } else {
#ifndef NDEBUG
        throw RuntimeError("The \"splines:\" section must be followed by a blank line and then the \"numbers of "
                           "parametric coordinates for splines:\" section.");
#endif
      }
    }
#ifndef NDEBUG
  } catch (RuntimeError const &exception) {
    Throw(exception, "splinelib::tools::sources::log_information::Read");
  }
#endif
  return log_information;
}

template<int maximum_parametric_dimensionality, int maximum_dimensionality>
SplinesConsidered RemoveSplinesOfTooHighDimensionalities(SplinesConsidered const &splines, SplinesRead &splines_read,
    NumbersOfParametricCoordinates * const numbers_of_parametric_coordinates) {
  SplinesConsidered::const_iterator const &splines_end = splines.end();
  Index const maximum_spline_index{static_cast<int>(splines_read.size()) - 1};
  SplinesConsidered written{};
  Index::ForEach(0, maximum_spline_index.Get() + 1, [&] (Index const &index) {
      Index::Type_ const spline_index{(maximum_spline_index - index).Get()};
      SplinesRead::value_type const &spline = splines_read[spline_index];
      if (((spline->parametric_dimensionality_ > maximum_parametric_dimensionality) || (spline->dimensionality_ >
               maximum_dimensionality)) || (!splines.empty() && (std::find(splines.begin(), splines_end, index) ==
                                                                 splines_end))) {
        splines_read.erase(splines_read.begin() + spline_index);
        if (numbers_of_parametric_coordinates)
            numbers_of_parametric_coordinates->erase(numbers_of_parametric_coordinates->begin() + spline_index);
      } else {
        written.emplace_back(spline_index);
      } });
  std::reverse(written.begin(), written.end());
  return written;
}
