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

set(CMAKE_DEBUG_POSTFIX "")
set(MESSAGE_QUIET ON)
pybind11_add_module(splinelyp splinelyp.cpp)
set(MESSAGE_QUIET OFF)
target_include_directories(splinelyp PUBLIC ${INCLUDE_DIRECTORIES})
target_link_libraries(splinelyp PRIVATE bindings)
target_compile_definitions(splinelyp PRIVATE __PYTHON__)
target_compile_options(splinelyp PRIVATE ${COMPILE_OPTIONS} "-w")

install(
        TARGETS splinelyp
        EXPORT ${targets_export_name}
        LIBRARY DESTINATION ${library_install_directory}
        ARCHIVE DESTINATION ${library_install_directory}/static
        RUNTIME DESTINATION ${executable_install_directory}
)

if(NOT DEFINED ENV{VIRTUAL_ENV})
    execute_process(COMMAND bash "-c" "${Python3_EXECUTABLE} -m site --user-site" OUTPUT_VARIABLE user_site
                                                                                  OUTPUT_STRIP_TRAILING_WHITESPACE)
    install(CODE "execute_process(COMMAND bash \"-c\" \"cp splinelyp.*.so ${user_site}\" \
                                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} RESULT_VARIABLE python_installation)")
    if(python_installation AND (NOT python_installation EQUAL 0))
        message(FATAL_ERROR "Python installation failed!")
    endif()
endif()
