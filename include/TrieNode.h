#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>

// Template for Trie Node
template <typename T>
class TrieNode {
public:
    std::unordered_map<T, TrieNode*> children;  // Links to child nodes
    bool isEndOfWord;  // True if node marks the end of a word

    TrieNode();  // Constructor declaration
};

#include "../src/TrieNode.tpp"

#endif
