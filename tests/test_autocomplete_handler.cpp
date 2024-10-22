#include <gtest/gtest.h>
#include "../include/AutocompleteHandler.h"
#include "../include/Trie.h"

// toLowerCase
TEST(AutocompleteHandlerTests, ToLowerCase) {
    std::string input = "HeLLo";
    std::string expected = "hello";
    ASSERT_EQ(toLowerCase(input), expected);
}

// getLastWord
TEST(AutocompleteHandlerTests, GetLastWord) {
    std::string input = "This is a test";
    std::string expected = "test";
    ASSERT_EQ(getLastWord(input), expected);
}

// replaceLastWord
TEST(AutocompleteHandlerTests, ReplaceLastWord) {
    std::string input = "This is a test";
    std::string suggestion = "success";
    std::string expected = "This is a success";
    ASSERT_EQ(replaceLastWord(input, suggestion), expected);

    // single word replacement
    input = "test";
    expected = "success";
    ASSERT_EQ(replaceLastWord(input, suggestion), expected);
}

// loadBookTitles 
TEST(AutocompleteHandlerTests, LoadBookTitles) {
    Trie<char> trie;
    documentIndex<std::string, vectorClass<IndexEntry>> index;

    index.insert("Harry Potter", {});
    index.insert("The Hobbit", {});
    index.insert("The Lord of the Rings", {});

    loadBookTitles(trie, index);

    ASSERT_TRUE(trie.search("Harry Potter"));
    ASSERT_TRUE(trie.search("The Hobbit"));
    ASSERT_TRUE(trie.search("The Lord of the Rings"));
}

// autocomplete using the Trie
TEST(AutocompleteHandlerTests, AutocompleteSuggestions) {
    Trie<char> trie;
    documentIndex<std::string, vectorClass<IndexEntry>> index;

    index.insert("The Lord of the Rings", {});
    index.insert("The Hobbit", {});
    index.insert("The Silmarillion", {});

    loadBookTitles(trie, index);

    // autocomplete "The"
    std::string input = "The";
    std::vector<std::string> suggestions = trie.autocomplete(toLowerCase(input));

    ASSERT_EQ(suggestions.size(), 3);  
    ASSERT_EQ(suggestions[0], "the hobbit");
    ASSERT_EQ(suggestions[1], "the lord of the rings");
    ASSERT_EQ(suggestions[2], "the silmarillion");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
