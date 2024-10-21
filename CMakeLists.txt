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
        )

# Enable testing
enable_testing()

# Add a test executable
add_executable(DSA_project_tests
        test/test.cpp
        )

# Link the necessary libraries for testing (if any, e.g., Google Test)
# If you're using Google Test, you would add:
# target_link_libraries(DSA_project_tests gtest gtest_main)

# Register the test executable
add_test(NAME DSAProjectTests COMMAND DSA_project_tests)

# Ensure the main project executable and tests are built
# This line ensures that tests are built after the main project
add_dependencies(DSA_project_tests DSA_project)
