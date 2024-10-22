cmake_minimum_required(VERSION 3.25)
project(DSA_project)

set(CMAKE_CXX_STANDARD 17)

# Add the main project executable
add_executable(DSA_project
        main.cpp
        include/TrieNode.h
        include/Trie.h
        include/AutocompleteHandler.h
        src/AutocompleteHandler.cpp
        src/vectorBook.tpp
        src/serialization.h
        src/documentIndex.h
        src/IndexEntry.h
        src/DocumentIndexer.cpp
        src/DocumentIndexer.h
        src/IndexEntry.cpp
        src/indexing.cpp
        include/indexing.h
        src/search.cpp
        include/search.h
        src/utils.cpp
        include/utils.h
        include/pairImp.h
        include/AsciiArt.h
        src/AsciiArt.cpp src/newSearch.cpp src/newSearch.h src/newSearch.h src/AccessBook.cpp include/AccessBook.h include/quicksort.h src/quicksort.cpp src/pagination.cpp include/pagination.h)

# Link any additional libraries if necessary
target_link_libraries(DSA_project)

# Download and add GoogleTest
#add_subdirectory(external/googletest)

# Enable testing
enable_testing()

# Add a test executable
add_executable(DSA_project_tests
        test/test.cpp
)

# Link the necessary libraries for testing (if any, e.g., Google Test)
target_link_libraries(DSA_project_tests gtest gtest_main)

# Register the test executable
add_test(NAME DSAProjectTests COMMAND DSA_project_tests)

# Ensure the main project executable and tests are built
add_dependencies(DSA_project_tests DSA_project)

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
