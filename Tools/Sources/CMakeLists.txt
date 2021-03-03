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
    HEADERS
    log_operations.hpp
    log_operations.inc
)

set(
    SOURCES
    log_operations.cpp
#
    ${HEADERS}
)
set_source_files_properties(${HEADERS} PROPERTIES LANGUAGE CXX HEADER_FILE_ONLY TRUE)

add_executable(sampler sampler.cpp)
target_include_directories(sampler PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(sampler PRIVATE utilities input_output tools)
target_compile_options(sampler PRIVATE ${COMPILE_OPTIONS})

add_executable(converter converter.cpp)
target_include_directories(converter PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(converter PRIVATE utilities input_output tools)
target_compile_options(converter PRIVATE ${COMPILE_OPTIONS})

add_library(tools ${SOURCES})
target_include_directories(tools PUBLIC ${INCLUDE_DIRECTORIES})
target_link_libraries(tools PUBLIC utilities input_output)
target_compile_definitions(tools INTERFACE ${COMPILE_DEFINITIONS})
target_compile_options(tools PRIVATE ${COMPILE_OPTIONS})

install(
        TARGETS converter sampler tools
        EXPORT ${targets_export_name}
        LIBRARY DESTINATION ${library_install_directory}
        ARCHIVE DESTINATION ${library_install_directory}/static
        RUNTIME DESTINATION ${executable_install_directory}
        INCLUDES DESTINATION ${include_install_directory}
)
