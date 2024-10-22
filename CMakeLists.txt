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
        src/AsciiArt.cpp
        src/newSearch.cpp
        src/newSearch.h
        src/AccessBook.cpp
        include/AccessBook.h
)

# Download and add GoogleTest as a subdirectory
add_subdirectory(external/googletest)

# Link any additional libraries if necessary (none for now)
target_link_libraries(DSA_project)

# Enable testing
enable_testing()

# Add test executable for DSA_project tests
add_executable(DSA_project_tests
        test/test.cpp
)

# Link GoogleTest libraries to the test executable
target_link_libraries(DSA_project_tests gtest gtest_main)

# Register the test executable with CMake's testing suite
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
        tests/test_trie.cpp
        tests/test_trieNode.cpp
)

# Link the test executable with GoogleTest
target_link_libraries(test_indexing gtest gtest_main)

# Register the indexing test
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

# Link the search test executable with GoogleTest
target_link_libraries(test_search gtest gtest_main)

# Register the search test
add_test(NAME test_search COMMAND test_search)
