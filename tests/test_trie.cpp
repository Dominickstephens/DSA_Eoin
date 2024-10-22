#include <gtest/gtest.h>
#include "../include/Trie.h"

// Define the test fixture class
class TrieTest : public ::testing::Test {
protected:
    Trie<char> trie;  // Declare a Trie of char

    void SetUp() override {
        // This function runs before every test case
        trie.insert("apple");
        trie.insert("app");
        trie.insert("apricot");
        trie.insert("banana");
    }

    void TearDown() override {
        // This function runs after every test case
        // Destructor of the trie will take care of memory clean-up
    }
};

// Test case to check if words are inserted and autocomplete works as expected
TEST_F(TrieTest, AutocompleteBasic) {
    std::vector<std::string> results = trie.autocomplete("app");
    std::vector<std::string> expected = {"app", "apple"};
    EXPECT_EQ(results, expected);
}

// Test case for searching for a non-existent prefix
TEST_F(TrieTest, AutocompleteNonExistentPrefix) {
    std::vector<std::string> results = trie.autocomplete("xyz");
    EXPECT_TRUE(results.empty());  // Expect empty results for a non-existent prefix
}

// Test case for inserting a single word and searching it
TEST_F(TrieTest, InsertAndSearchSingleWord) {
    Trie<char> singleTrie;
    singleTrie.insert("cat");
    std::vector<std::string> results = singleTrie.autocomplete("cat");
    std::vector<std::string> expected = {"cat"};
    EXPECT_EQ(results, expected);
}

// Test case to verify that inserting the same word twice doesn't break the Trie
TEST_F(TrieTest, InsertDuplicateWords) {
    Trie<char> dupTrie;
    dupTrie.insert("dog");
    dupTrie.insert("dog");
    std::vector<std::string> results = dupTrie.autocomplete("dog");
    std::vector<std::string> expected = {"dog"};
    EXPECT_EQ(results, expected);
    EXPECT_EQ(results.size(), 1);  // Ensure only one "dog" is returned
}


// Test case to check empty trie (no words inserted)
TEST_F(TrieTest, EmptyTrieAutocomplete) {
    Trie<char> emptyTrie;
    std::vector<std::string> results = emptyTrie.autocomplete("a");
    EXPECT_TRUE(results.empty());
}
