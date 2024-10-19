cmake_minimum_required(VERSION 3.25)
project(DSA_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSA_project main.cpp
        src/TrieNode.tpp
        include/TrieNode.h
        src/Trie.tpp
        include/Trie.h)
