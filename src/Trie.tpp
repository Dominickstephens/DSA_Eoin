#ifndef TRIE_TPP
#define TRIE_TPP

#include "../include/Trie.h"
#include "vectorBook.h"

// Constructor implementation
template <typename T>
Trie<T>::Trie() {
    root = new TrieNode<T>();
}

// Destructor implementation
template <typename T>
Trie<T>::~Trie() {
    deleteTrie(root);
}

// Recursive helper to delete the Trie nodes
template <typename T>
void Trie<T>::deleteTrie(TrieNode<T>* node) {
    for (auto& child : node->children) {
        deleteTrie(child.second);
    }
    delete node;
}

// Insert a word into the Trie
template <typename T>
void Trie<T>::insert(const std::basic_string<T>& word) {
    TrieNode<T>* current = root;
    for (const auto& ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode<T>();
        }
        current = current->children[ch];
    }
    current->isEndOfWord = true;
}

// Search for a prefix in the Trie
template <typename T>
TrieNode<T>* Trie<T>::searchPrefix(const std::basic_string<T>& prefix) {
    TrieNode<T>* current = root;
    for (const auto& ch : prefix) {
        if (current->children.find(ch) == current->children.end()) {
            return nullptr;
        }
        current = current->children[ch];
    }
    return current;
}

// Collect all words from a given node
template <typename T>
void Trie<T>::collectWords(TrieNode<T>* node, std::basic_string<T>& currentPrefix, vectorClass<std::basic_string<T>>& result) {
    if (node->isEndOfWord) {
        result.push(currentPrefix);
    }
    for (auto& child : node->children) {
        currentPrefix.push_back(child.first);
        collectWords(child.second, currentPrefix, result);
        currentPrefix.pop_back();
    }
}

// Autocomplete function to return all words that start with a given prefix
template <typename T>
vectorClass<std::basic_string<T>> Trie<T>::autocomplete(const std::basic_string<T>& prefix) {
    vectorClass<std::basic_string<T>> result;

    if (TrieNode<T>* prefixNode = searchPrefix(prefix)) {  // Declare prefixNode inside the if-statement
        std::basic_string<T> currentPrefix = prefix;
        collectWords(prefixNode, currentPrefix, result);
    }

    return result;
}

#endif
