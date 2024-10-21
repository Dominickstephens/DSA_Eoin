#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <vector>

// Template for the Trie class
template <typename T>
class Trie {
private:
    TrieNode<T>* root;  // Root node of the Trie

public:
    Trie();  // Constructor declaration
    ~Trie();  // Destructor declaration
    void insert(const std::basic_string<T>& word);  // Insert a word into the Trie
    std::vector<std::basic_string<T>> autocomplete(const std::basic_string<T>& prefix);  // Autocomplete function
    TrieNode<T>* searchPrefix(const std::basic_string<T>& prefix);  // Search for a prefix
    void collectWords(TrieNode<T>* node, std::basic_string<T>& currentPrefix, std::vector<std::basic_string<T>>& result);  // Helper function

    // Recursive helper function to delete the Trie
    void deleteTrie(TrieNode<T>* node);
};

#include "../src/Trie.tpp" // Include template implementation file

#endif
