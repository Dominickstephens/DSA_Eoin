#include <gtest/gtest.h>
#include "../include/TrieNode.h"

// Test TrieNode initialization
TEST(TrieNodeTest, ConstructorInitializesCorrectly) {
    TrieNode<char> node;

    // Check if the children map is initialized empty
    EXPECT_TRUE(node.children.empty()) << "Children map should be empty upon initialization";

    // Check if isEndOfWord is initialized to false
    EXPECT_FALSE(node.isEndOfWord) << "isEndOfWord should be false upon initialization";
}

// Test inserting a child node into the TrieNode's children map
TEST(TrieNodeTest, CanInsertChildNode) {
    TrieNode<char> node;
    TrieNode<char>* childNode = new TrieNode<char>();

    // Insert a child node for character 'a'
    node.children['a'] = childNode;

    // Check if the child node is inserted correctly
    EXPECT_NE(node.children.find('a'), node.children.end()) << "Child node for 'a' should be inserted";
    EXPECT_EQ(node.children['a'], childNode) << "Child node pointer should match the inserted node";

    // Clean up
    delete childNode;
}

// Test setting isEndOfWord to true
TEST(TrieNodeTest, CanSetEndOfWord) {
    TrieNode<char> node;

    // Set isEndOfWord to true
    node.isEndOfWord = true;

    // Check if isEndOfWord is updated correctly
    EXPECT_TRUE(node.isEndOfWord) << "isEndOfWord should be true after setting";
}

