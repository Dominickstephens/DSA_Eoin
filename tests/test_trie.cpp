#include <gtest/gtest.h>
#include "../include/Trie.h"

class TrieTest : public ::testing::Test {
protected:
    Trie<char> trie; 

    void SetUp() override {
        // runs before every test case
        trie.insert("apple");
        trie.insert("app");
        trie.insert("apricot");
        trie.insert("banana");
    }

    void TearDown() override {
        // runs after every test case. Destructor of the trie will take care of memory clean-up 🧹
    }
};

// check if words are inserted and autocomplete works as expected
TEST_F(TrieTest, AutocompleteBasic) {
    std::vector<std::string> results = trie.autocomplete("app");
    std::vector<std::string> expected = {"app", "apple"};
    EXPECT_EQ(results, expected);
}

// searching for a non-existent prefix
TEST_F(TrieTest, AutocompleteNonExistentPrefix) {
    std::vector<std::string> results = trie.autocomplete("xyz");
    EXPECT_TRUE(results.empty());  
}

// inserting a single word and searching it
TEST_F(TrieTest, InsertAndSearchSingleWord) {
    Trie<char> singleTrie;
    singleTrie.insert("cat");
    std::vector<std::string> results = singleTrie.autocomplete("cat");
    std::vector<std::string> expected = {"cat"};
    EXPECT_EQ(results, expected);
}

// verify that inserting the same word twice doesn't break the Trie
TEST_F(TrieTest, InsertDuplicateWords) {
    Trie<char> dupTrie;
    dupTrie.insert("dog");
    dupTrie.insert("dog");
    std::vector<std::string> results = dupTrie.autocomplete("dog");
    std::vector<std::string> expected = {"dog"};
    EXPECT_EQ(results, expected);
    EXPECT_EQ(results.size(), 1); 
}


// check empty trie (no words inserted)
TEST_F(TrieTest, EmptyTrieAutocomplete) {
    Trie<char> emptyTrie;
    std::vector<std::string> results = emptyTrie.autocomplete("a");
    EXPECT_TRUE(results.empty());
}
