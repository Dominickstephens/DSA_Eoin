cmake_minimum_required(VERSION 3.25)
project(DSA_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSA_project main.cpp
        src/indexing.cpp
        include/indexing.h
        src/search.cpp
        include/search.h
        src/utils.cpp
        include/utils.h
        books/ChristmasCarol.txt
        books/test.txt)
