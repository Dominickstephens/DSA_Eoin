#include <gtest/gtest.h>
#include "../include/TrieNode.h"

// trieNode initialization
TEST(TrieNodeTest, ConstructorInitializesCorrectly) {
    TrieNode<char> node;
    EXPECT_TRUE(node.children.empty()) << "Children map should be empty upon initialization";
    EXPECT_FALSE(node.isEndOfWord) << "isEndOfWord should be false upon initialization";
}

// inserting a child node into the TrieNode's children map
TEST(TrieNodeTest, CanInsertChildNode) {
    TrieNode<char> node;
    TrieNode<char>* childNode = new TrieNode<char>();
    node.children['a'] = childNode;
    EXPECT_NE(node.children.find('a'), node.children.end()) << "Child node for 'a' should be inserted";
    EXPECT_EQ(node.children['a'], childNode) << "Child node pointer should match the inserted node";

    delete childNode;
}

// setting isEndOfWord to true
TEST(TrieNodeTest, CanSetEndOfWord) {
    TrieNode<char> node;
    node.isEndOfWord = true;
    EXPECT_TRUE(node.isEndOfWord) << "isEndOfWord should be true after setting";
}

