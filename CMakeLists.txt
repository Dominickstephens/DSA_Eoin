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
        include/serialization.h
        include/documentIndex.h
        include/IndexEntry.h
        src/DocumentIndexer.cpp
        include/DocumentIndexer.h
        src/IndexEntry.cpp
        src/indexing.cpp
        include/indexing.h
        src/search.cpp
        include/search.h
        src/utils.cpp
        include/utils.h
        include/Set.h
        src/Set.tpp
        include/pairImp.h
        include/AsciiArt.h
        src/AsciiArt.cpp
        src/newSearch.cpp
        include/newSearch.h
        src/AccessBook.cpp
        include/AccessBook.h
)

# Download and add GoogleTest as a subdirectory
add_subdirectory(external/googletest)


# Enable testing
enable_testing()

# Register the test executable with CMake's testing suite
add_test(NAME DSAProjectTests COMMAND DSA_project_tests)

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
        tests/test_trie_node.cpp
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

# Test executable for AutocompleteHandler tests
add_executable(test_autocomplete_handler
        tests/test_autocomplete_handler.cpp
        src/AutocompleteHandler.cpp
        include/AutocompleteHandler.h
        include/Trie.h
        include/IndexEntry.h
        include/documentIndex.h
)

# Link the autocomplete test executable with GoogleTest
target_link_libraries(test_autocomplete_handler gtest gtest_main)

# Register the autocomplete handler test
add_test(NAME test_autocomplete_handler COMMAND test_autocomplete_handler)

# Test executable for Trie tests
add_executable(test_trie
        tests/test_trie.cpp
)

# Link the Trie test executable with GoogleTest
target_link_libraries(test_trie gtest gtest_main)

# Register the Trie test
add_test(NAME test_trie COMMAND test_trie)

# Test executable for TrieNode tests
add_executable(test_trie_node
        tests/test_trie_node.cpp
)

# Link the TrieNode test executable with GoogleTest
target_link_libraries(test_trie_node gtest gtest_main)

# Register the TrieNode test
add_test(NAME test_trie_node COMMAND test_trie_node)
