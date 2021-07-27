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

#include <gtest/gtest.h>
#include "Sources/Utilities/error_handling.hpp"
#include "Sources/Utilities/std_container_operations.hpp"
#include "Sources/Utilities/string_operations.hpp"
#include "Sources/Utilities/system_operations.hpp"
#include "Tests/Splines/spline_item_mock.hpp"
#include "Tools/Sources/log_operations.hpp"
#include "Tools/Tests/config_log.hpp"

namespace splinelib::tools::tests::log_operations {

using namespace tools::sources::log_operations;  // NOLINT(build/namespaces)
using NumberOfParametricCoordinates = NumbersOfParametricCoordinates::value_type;

class LogOperationsSuite : public testing::Test {
 protected:
  using Index_ = SplinesConsidered::value_type;

  constexpr static Index_ const kIndex0_{};
  constexpr static NumberOfParametricCoordinates::value_type const kLength10{10};
  inline static SplinesConsidered const kSplinesConsidered_{kIndex0_};
  NumbersOfParametricCoordinates numbers_of_parametric_coordinates_{{kLength10, kLength10}};
};

TEST_F(LogOperationsSuite, Append) {
  constexpr Index_ const kIndex1_{1};
  String const kInput{"# Replace by path to input file!"}, kOutput{"# Replace by path to output file!"};

  EXPECT_NO_THROW(Append(log_invalid_splines, (LogInformation{kInput, kOutput, {}, {}})));
  EXPECT_NO_THROW(Append(log_invalid_splines, (LogInformation{kInput, kOutput, {kIndex0_}, {}})));
  EXPECT_NO_THROW(Append(log_invalid_splines, (LogInformation{kInput, kOutput, {kIndex0_, kIndex1_}, {}})));
  EXPECT_NO_THROW(Append(log_invalid_splines, (LogInformation{kInput, kOutput, {kIndex0_, kIndex1_, Index_{2}}, {}})));
}

TEST_F(LogOperationsSuite, Read) {
  EXPECT_EQ(Read<LogType::kConverter>(log_converter), (LogInformation{xml_file, xml_itd, {}, {}}));
  EXPECT_EQ(Read<LogType::kSampler>(log_sampler), (LogInformation{xml_itd, itd_vtk, kSplinesConsidered_,
                                                                  numbers_of_parametric_coordinates_}));
}

TEST_F(LogOperationsSuite, SkipBlankLineAndReadSectionIdentifier) {
  namespace utilities = splinelib::sources::utilities;
  namespace system_operations = utilities::system_operations;
  using InputStream = system_operations::InputStream;
  using utilities::string_operations::StartsWith;

  InputStream log;
  ASSERT_NO_THROW(log = (system_operations::Open<InputStream,
                             system_operations::kModeIn>(log_invalid_numbers_of_parametric_coordinates)));
  String section_identifier;
  getline(log, section_identifier);
  EXPECT_TRUE(StartsWith(section_identifier, "input:"));
  getline(log, section_identifier);
  EXPECT_TRUE(StartsWith(SkipBlankLineAndReadSectionIdentifier(log), "output:"));
  getline(log, section_identifier);
  EXPECT_TRUE(StartsWith(SkipBlankLineAndReadSectionIdentifier(log), "splines:"));
  getline(log, section_identifier);
  EXPECT_TRUE(StartsWith(SkipBlankLineAndReadSectionIdentifier(log), "numbers of parametric coordinates for splines:"));
}

TEST_F(LogOperationsSuite, RemoveSplinesOfTooHighDimensionalities) {
  using SplineItem = testing::StrictMock<splinelib::tests::splines::ASplineItem>;

  SharedPointer<SplineItem> const b_spline_surface{std::make_shared<SplineItem>()};
  b_spline_surface->NurbsBookExe3_8();
  SplinesRead splines_read{b_spline_surface};
  EXPECT_EQ((RemoveSplinesOfTooHighDimensionalities<1, 3>(kSplinesConsidered_, splines_read,
                                                          &numbers_of_parametric_coordinates_)), SplinesConsidered{});
  EXPECT_EQ(splines_read, SplinesRead{});
  EXPECT_EQ(numbers_of_parametric_coordinates_, NumbersOfParametricCoordinates{});
}

#ifndef NDEBUG
TEST_F(LogOperationsSuite, ThrowIfCommandLineArgumentsAreInvalid) {
  EXPECT_NO_THROW(ThrowIfCommandLineArgumentsAreInvalid(2));
  EXPECT_THROW(ThrowIfCommandLineArgumentsAreInvalid(1), RuntimeError);
}

TEST_F(LogOperationsSuite, ThrowIfSplinesOrNumbersOfParametricCoordinatesForSplinesAreInvalid) {
  EXPECT_THROW(Read<LogType::kConverter>(log_invalid_splines), RuntimeError);
  EXPECT_THROW(Read<LogType::kSampler>(log_converter), RuntimeError);
  EXPECT_THROW(Read<LogType::kSampler>(log_invalid_numbers_of_parametric_coordinates), RuntimeError);
}
#endif
}  // namespace splinelib::tools::tests::log_operations
