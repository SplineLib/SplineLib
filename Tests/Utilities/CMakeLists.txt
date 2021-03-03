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
    ${CMAKE_CURRENT_SOURCE_DIR}/index_mock.hpp
)

set(
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/index_mock.cpp
#
    ${HEADERS}
)
set_source_files_properties(${HEADERS} PROPERTIES LANGUAGE CXX HEADER_FILE_ONLY TRUE)

add_library(mock_utilities ${SOURCES})
target_include_directories(mock_utilities PUBLIC ${INCLUDE_DIRECTORIES})
target_include_directories(mock_utilities SYSTEM PUBLIC ${GMOCK_INCLUDE_DIRS})
target_link_libraries(mock_utilities PUBLIC utilities ${GMOCK_LDFLAGS})
target_compile_definitions(mock_utilities PUBLIC ${GMOCK_CFLAGS_OTHER} INTERFACE ${COMPILE_DEFINITIONS})
target_compile_options(mock_utilities PRIVATE ${COMPILE_OPTIONS})

install(
        TARGETS mock_utilities
        EXPORT ${targets_export_name}
        LIBRARY DESTINATION ${library_install_directory}
        ARCHIVE DESTINATION ${library_install_directory}/static
        RUNTIME DESTINATION ${executable_install_directory}
        INCLUDES DESTINATION ${include_install_directory}
)

install(FILES ${HEADERS} DESTINATION ${include_install_directory_headers}/Tests/Utilities)

set(
    TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/error_handling_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/index_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_operations_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/named_type_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/numeric_operations_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/std_container_operations_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/string_operations_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system_operations_test.cpp
)

add_executable(test_utilities ${TEST_SOURCES})
target_include_directories(test_utilities SYSTEM PRIVATE ${GMOCK_INCLUDE_DIRS})
target_link_libraries(test_utilities PRIVATE utilities ${GMOCK_LDFLAGS})
target_compile_definitions(test_utilities PRIVATE ${GMOCK_CFLAGS_OTHER})
target_compile_options(test_utilities PRIVATE ${COMPILE_OPTIONS})

add_test(NAME utilities_test COMMAND test_utilities)
