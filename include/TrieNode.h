#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>

template <typename T>
class TrieNode
{
public:
    std::unordered_map<T, TrieNode *> children;
    bool isEndOfWord; // True if node marks the end of a word

    TrieNode();
};

#include "../src/TrieNode.tpp"

#endif
