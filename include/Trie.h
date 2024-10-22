#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <vector>

template <typename T>
class Trie
{
private:
    TrieNode<T> *root;

public:
    Trie();
    ~Trie();
    void insert(const std::basic_string<T> &word);                                      // Insert a word into the Trie
    std::vector<std::basic_string<T>> autocomplete(const std::basic_string<T> &prefix); // Autocomplete function
    TrieNode<T> *searchPrefix(const std::basic_string<T> &prefix);
    void collectWords(TrieNode<T> *node, std::basic_string<T> &currentPrefix, std::vector<std::basic_string<T>> &result);

    void deleteTrie(TrieNode<T> *node);
};

#include "../src/Trie.tpp"

#endif
