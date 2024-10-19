#include <iostream>
#include "include/Trie.h"

int main() {
    // Create a Trie for characters (strings of type char)
    Trie<char> trie;

    // Insert some words into the trie
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");
    trie.insert("bat");
    trie.insert("ball");

    // Test autocomplete function
    std::string prefix;

    // Test case 1: autocomplete for prefix "ap"
    prefix = "ap";
    std::vector<std::string> suggestions = trie.autocomplete(prefix);
    std::cout << "Suggestions for prefix \"" << prefix << "\":" << std::endl;
    for (const auto& suggestion : suggestions) {
        std::cout << suggestion << std::endl;
    }

    // Test case 2: autocomplete for prefix "ba"
    prefix = "ba";
    suggestions = trie.autocomplete(prefix);
    std::cout << "Suggestions for prefix \"" << prefix << "\":" << std::endl;
    for (const auto& suggestion : suggestions) {
        std::cout << suggestion << std::endl;
    }

    // Test case 3: autocomplete for prefix "bat"
    prefix = "bat";
    suggestions = trie.autocomplete(prefix);
    std::cout << "Suggestions for prefix \"" << prefix << "\":" << std::endl;
    for (const auto& suggestion : suggestions) {
        std::cout << suggestion << std::endl;
    }

    // Test case 4: autocomplete for a prefix that does not exist
    prefix = "xyz";
    suggestions = trie.autocomplete(prefix);
    std::cout << "Suggestions for prefix \"" << prefix << "\":" << std::endl;
    if (suggestions.empty()) {
        std::cout << "No suggestions found." << std::endl;
    }

    return 0;
}
