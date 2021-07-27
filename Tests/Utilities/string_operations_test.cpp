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
#include "Sources/Utilities/numeric_operations.hpp"
#include "Sources/Utilities/std_container_operations.hpp"
#include "Sources/Utilities/string_operations.hpp"

namespace splinelib::tests::utilities::string_operations {

using namespace sources::utilities::string_operations;  // NOLINT(build/namespaces)
template<typename Name, typename Type>
using NamedType = sources::utilities::NamedType<Name, Type>;
using Double = NamedType<struct DoubleName, double>;
using Int = NamedType<struct IntName, int>;

constexpr Double const k0_5{0.5}, k8_765432101234567{8.765432101234567};
constexpr Int const kInt{1};
constexpr Precision const kPrecision{4};
String const kHelloWorld{"hello world"}, kHelloWorldCapitalized{"Hello World"}, kZero{"0"},
             kZeroPointZeroEightZeroNineSeven{"80.97e-3"}, kZeroPointFive{"0.5"}, kOne{"1"};

TEST(StringOperationsSuite, EndsWith) {
  const String kWorld{"world"};

  EXPECT_TRUE(EndsWith(kHelloWorld, kWorld));
  EXPECT_FALSE(EndsWith(kHelloWorldCapitalized, kWorld));
  EXPECT_FALSE(EndsWith("hellow orld", kWorld));
  EXPECT_FALSE(EndsWith("hello world ", kWorld));
}

TEST(StringOperationsSuite, StartsWith) {
  const String kHello{"hello"};

  EXPECT_TRUE(StartsWith(kHelloWorld, kHello));
  EXPECT_FALSE(StartsWith(kHelloWorldCapitalized, kHello));
  EXPECT_FALSE(StartsWith("hell oworld", kHello));
  EXPECT_FALSE(StartsWith(" hello world", kHello));
}

TEST(StringOperationsSuite, Append) {
  String const kAppend{"append"}, kDelimiter{","}, kMore{"more"};

  String string{"test"};
  EXPECT_NO_THROW(Append(string, kDelimiter, " append"));
  EXPECT_EQ(string, "test, append");
  EXPECT_NO_THROW(Append(string, "; ", StringArray<2>{kAppend, kMore}));
  EXPECT_EQ(string, "test, append; append; more");
  EXPECT_NO_THROW(Append(string, kDelimiter, StringVector{kAppend, "even", kMore}));
  EXPECT_EQ(string, "test, append; append; more,append,even,more");
  EXPECT_NO_THROW(Append(string, "", StringArray<1>{";"}));
  EXPECT_EQ(string, "test, append; append; more,append,even,more;");
}

TEST(StringOperationsSuite, TrimCharacter) {
  String const kSevenEightEight{"7.88"};

  EXPECT_EQ(TrimCharacter(" 7.88 ", ' '), kSevenEightEight);
  EXPECT_EQ(TrimCharacter(kSevenEightEight, ' '), kSevenEightEight);
  EXPECT_EQ(TrimCharacter(TrimCharacter(TrimCharacter("[ 7.88 ]", '['), ']'), ' '), kSevenEightEight);
}

TEST(StringOperationsSuite, SplitAtDelimiter) {
  EXPECT_EQ(SplitAtDelimiter("delimited by spaces", ' '), (StringVector{"delimited", "by", "spaces"}));
  EXPECT_EQ(SplitAtDelimiter("semicolons; not; removed", ' '), (StringVector{"semicolons;", "not;", "removed"}));
}

TEST(StringOperationsSuite, ConvertToNumber) {
  using sources::utilities::numeric_operations::IsEqual;

  String const kMinusEightPointZeroNineSeven{"-80.97e-01"}, kMinusEight{"-8"},
               kMinusZeroPointZeroZeroZeroZeroNine{"-0.9e-4"}, kMinusZero{"-0.0e-4"}, kEight{"8"}, kPlusEight{"+8"},
               kEightPointZeroNineSeven{"80.97e-01"}, kEightyPointNineSeven{"80.97"},
               kEightHundredAndNinePointSevenLower{"80.97e1"}, kEightHundredAndNinePointSevenUpper{"80.97E1"},
               kEightHundredAndNinePointSevenPlus{"80.97e+1"};

  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kEight), 8.0));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kMinusEight), -8.0));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kPlusEight), 8.0));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kEightyPointNineSeven), 80.97));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kEightHundredAndNinePointSevenLower), 809.7));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kEightHundredAndNinePointSevenUpper), 809.7));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kEightHundredAndNinePointSevenPlus), 809.7));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kZeroPointZeroEightZeroNineSeven), 0.08097));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kEightPointZeroNineSeven), 8.097));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kMinusEightPointZeroNineSeven), -8.097));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kMinusZero), 0.0));
  EXPECT_TRUE(IsEqual(ConvertToNumber<double>(kMinusZeroPointZeroZeroZeroZeroNine), -0.00009));
  EXPECT_EQ(ConvertToNumber<Double>(kZeroPointFive), k0_5);
  EXPECT_EQ(ConvertToNumber<Double>(Write(k8_765432101234567)), Double{8.765432101234567});

  EXPECT_EQ(ConvertToNumber<int>(kEight), 8);
  EXPECT_EQ(ConvertToNumber<int>(kMinusEight), -8);
  EXPECT_EQ(ConvertToNumber<int>(kPlusEight), 8);
  EXPECT_EQ(ConvertToNumber<int>(kEightyPointNineSeven), 80);
  EXPECT_EQ(ConvertToNumber<int>(kEightHundredAndNinePointSevenLower), 80);
  EXPECT_EQ(static_cast<int>(ConvertToNumber<double>(kEightHundredAndNinePointSevenLower)), 809);
  EXPECT_EQ(ConvertToNumber<int>(kEightHundredAndNinePointSevenUpper), 80);
  EXPECT_EQ(ConvertToNumber<int>(kEightHundredAndNinePointSevenPlus), 80);
  EXPECT_EQ(ConvertToNumber<int>(kZeroPointZeroEightZeroNineSeven), 80);
  EXPECT_EQ(ConvertToNumber<int>(kEightPointZeroNineSeven), 80);
  EXPECT_EQ(ConvertToNumber<int>(kMinusEightPointZeroNineSeven), -80);
  EXPECT_EQ(static_cast<int>(ConvertToNumber<double>(kMinusEightPointZeroNineSeven)), -8);
  EXPECT_EQ(ConvertToNumber<int>(kMinusZero), 0);
  EXPECT_EQ(ConvertToNumber<int>(kMinusZeroPointZeroZeroZeroZeroNine), 0);
  EXPECT_EQ(ConvertToNumber<Int>(kOne), kInt);
}

TEST(StringOperationsSuite, ConvertToNumbers) {
  String const kComma{"-6.7,80.97e-3,-2.27E2,1.1e+3,-0.0E+03,0.2e-0,1"};

  EXPECT_EQ(ConvertToNumbers<Double>(kComma, ','),
            (Vector<Double>{Double{-6.7}, Double{80.97e-3}, Double{-2.27E2}, Double{1.1e+3}, Double{-0.0E+03},
                            Double{0.2e-0}, Double{1.0}}));
}

TEST(StringOperationsSuite, Write) {
  using StringArray = StringArray<2>;

  String const kDouble{"8.76543210123457"}, kDoubleTruncated{"8.765"};
  Array<Double, 2> const kDoubles{k0_5, k8_765432101234567};

  EXPECT_EQ(Write(k0_5), kZeroPointFive);
  EXPECT_EQ(Write(k8_765432101234567), kDouble);
  EXPECT_EQ(Write(k8_765432101234567, kPrecision), kDoubleTruncated);
  EXPECT_EQ(Write<StringVector>(Vector<Double>{k0_5, k0_5}), (StringVector{kZeroPointFive, kZeroPointFive}));
  EXPECT_EQ(Write<StringArray>(kDoubles), (StringArray{kZeroPointFive, kDouble}));
  EXPECT_EQ(Write<StringVector>(kDoubles, kPrecision), (StringVector{kZeroPointFive, kDoubleTruncated}));

  EXPECT_EQ(Write(kInt), kOne);
  EXPECT_EQ(Write<StringArray>(Vector<Int>{kInt, kInt}), (StringArray{kOne, kOne}));
}

#ifndef NDEBUG
TEST(StringOperationsSuite, ThrowIfPrecisionIsNegative) {
  EXPECT_THROW(Write(k0_5, Precision{-1}), DomainError);
}
#endif
}  // namespace splinelib::tests::utilities::string_operations
