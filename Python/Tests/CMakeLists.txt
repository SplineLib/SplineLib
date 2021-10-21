# Copyright (c) 2018–2021 SplineLib
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

set(
    TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/b_spline_binding_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nurbs_binding_test.cpp
)

add_executable(test_bindings ${TEST_SOURCES})
target_link_libraries(test_bindings PRIVATE GTest::gmock_main pybind11::embed bindings mock_splines)
target_compile_definitions(test_bindings PRIVATE __PYTHON__)
target_compile_options(test_bindings PRIVATE ${COMPILE_OPTIONS} "-w")

add_test(NAME bindings_test COMMAND test_bindings)
