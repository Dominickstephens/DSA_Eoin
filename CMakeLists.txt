cmake_minimum_required(VERSION 3.25)
project(DSA_project)

set(CMAKE_CXX_STANDARD 17)

# Download and add GoogleTest
add_subdirectory(external/googletest)

enable_testing()

# Main executable
add_executable(DSA_project
        main.cpp
        src/indexing.cpp
        include/indexing.h
        src/search.cpp
        include/search.h
        src/utils.cpp
        include/utils.h
)

# Link any additional libraries if necessary
target_link_libraries(DSA_project)

# Test executable for indexing tests
add_executable(test_indexing
        tests/test_indexing.cpp
        src/indexing.cpp
        include/indexing.h
        src/search.cpp
        include/search.h
        src/utils.cpp
        include/utils.h
)

# Link the test executable with GoogleTest
target_link_libraries(test_indexing gtest gtest_main)

# Register the test
add_test(NAME test_indexing COMMAND test_indexing)

# Test executable for search tests
add_executable(test_search
        tests/test_search.cpp
        src/indexing.cpp
        include/indexing.h
        src/search.cpp
        include/search.h
        src/utils.cpp
        include/utils.h
)

# Link the test executable with GoogleTest
target_link_libraries(test_search gtest gtest_main)

# Register the test
add_test(NAME test_search COMMAND test_search)
