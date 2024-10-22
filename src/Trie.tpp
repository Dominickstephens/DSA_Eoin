#ifndef TRIE_TPP
#define TRIE_TPP

#include "../include/Trie.h"

template <typename T>
Trie<T>::Trie() {
    root = new TrieNode<T>();
}

template <typename T>
Trie<T>::~Trie() {
    deleteTrie(root);
}

// recursive helper to delete the Trie nodes
template <typename T>
void Trie<T>::deleteTrie(TrieNode<T>* node) {
    for (auto& child : node->children) {
        deleteTrie(child.second);
    }
    delete node;
}

// insert into the Trie
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

// search for a prefix in the Trie
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

// collect all words from a given node
template <typename T>
void Trie<T>::collectWords(TrieNode<T>* node, std::basic_string<T>& currentPrefix, std::vector<std::basic_string<T>>& result) {
    if (node->isEndOfWord) {
        result.push_back(currentPrefix);
    }
    for (auto& child : node->children) {
        currentPrefix.push_back(child.first);
        collectWords(child.second, currentPrefix, result);
        currentPrefix.pop_back();
    }
}

// autocomplete function
template <typename T>
std::vector<std::basic_string<T>> Trie<T>::autocomplete(const std::basic_string<T>& prefix) {
    std::vector<std::basic_string<T>> result;

    if (TrieNode<T>* prefixNode = searchPrefix(prefix)) { 
        std::basic_string<T> currentPrefix = prefix;
        collectWords(prefixNode, currentPrefix, result);
    }

    return result;
}

#endif
