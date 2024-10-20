cmake_minimum_required(VERSION 3.25)
project(DSA_project)

set(CMAKE_CXX_STANDARD 17)

# Add the main executable
add_executable(DSA_project
        src/main.cpp
        src/vectorBook.tpp src/serialization.h src/documentIndex.h src/IndexEntry.h src/DocumentIndexer.cpp src/DocumentIndexer.h src/IndexEntry.cpp
        )

# Enable testing
enable_testing()

# Add a test executable
add_executable(DSA_project_tests
<<<<<<< HEAD
        src/test.cpp
=======
        test.cpp
>>>>>>> main
        )  # Only include the test source file

# Link the necessary source files directly for testing
target_sources(DSA_project_tests
        PRIVATE
        )

# Register the test executable
<<<<<<< HEAD
add_test(NAME DSAProjectTests COMMAND DSA_project_tests)
=======
add_test(NAME DSAProjectTests COMMAND DSA_project_tests)
>>>>>>> main
