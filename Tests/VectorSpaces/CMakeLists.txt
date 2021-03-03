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
    ${CMAKE_CURRENT_SOURCE_DIR}/vector_space_mock.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/weighted_vector_space_3d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/weighted_vector_space_mock.hpp
)

set(
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/vector_space_mock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/weighted_vector_space_3d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/weighted_vector_space_mock.cpp
#
    ${HEADERS}
)
set_source_files_properties(${HEADERS} PROPERTIES LANGUAGE CXX HEADER_FILE_ONLY TRUE)

add_library(mock_vector_spaces ${SOURCES})
target_include_directories(mock_vector_spaces PUBLIC ${INCLUDE_DIRECTORIES})
target_include_directories(mock_vector_spaces SYSTEM PUBLIC ${GMOCK_INCLUDE_DIRS})
target_link_libraries(mock_vector_spaces PUBLIC vector_spaces ${GMOCK_LDFLAGS})
target_compile_definitions(mock_vector_spaces PUBLIC ${GMOCK_CFLAGS_OTHER} INTERFACE ${COMPILE_DEFINITIONS})
target_compile_options(mock_vector_spaces PRIVATE ${COMPILE_OPTIONS})

install(
        TARGETS mock_vector_spaces
        EXPORT ${targets_export_name}
        LIBRARY DESTINATION ${library_install_directory}
        ARCHIVE DESTINATION ${library_install_directory}/static
        RUNTIME DESTINATION ${executable_install_directory}
        INCLUDES DESTINATION ${include_install_directory}
)

install(FILES ${HEADERS} DESTINATION ${include_install_directory_headers}/Tests/VectorSpaces)

set(
    TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/vector_space_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/weighted_vector_space_test.cpp
)

add_executable(test_vector_spaces ${TEST_SOURCES})
target_include_directories(test_vector_spaces SYSTEM PRIVATE ${GMOCK_INCLUDE_DIRS})
target_link_libraries(test_vector_spaces PRIVATE utilities vector_spaces ${GMOCK_LDFLAGS} mock_vector_spaces)
target_compile_definitions(test_vector_spaces PRIVATE ${GMOCK_CFLAGS_OTHER})
target_compile_options(test_vector_spaces PRIVATE ${COMPILE_OPTIONS})

add_test(NAME vector_spaces_test COMMAND test_vector_spaces)
