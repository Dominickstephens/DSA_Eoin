#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>
#include "../include/search.h"
#include "../include/indexing.h"




// Test fixture for search tests
class SearchTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear the inverted index before each test
        invertedIndex.clear();
    }
};

// Test getDocumentsForKeyword function
TEST_F(SearchTest, GetDocumentsForKeyword) {
    invertedIndex["test"] = {1, 2, 3};
    std::set<int> result = getDocumentsForKeyword("test");
    std::set<int> expected = {1, 2, 3};
    ASSERT_EQ(result, expected);

    result = getDocumentsForKeyword("nonexistent");
    expected = {};
    ASSERT_EQ(result, expected);
}

// Test booleanAnd function
TEST_F(SearchTest, BooleanAnd) {
    std::set<int> set1 = {1, 2, 3};
    std::set<int> set2 = {2, 3, 4};
    std::set<int> result = booleanAnd(set1, set2);
    std::set<int> expected = {2, 3};
    ASSERT_EQ(result, expected);
}

// Test booleanOr function
TEST_F(SearchTest, BooleanOr) {
    std::set<int> set1 = {1, 2, 3};
    std::set<int> set2 = {2, 3, 4};
    std::set<int> result = booleanOr(set1, set2);
    std::set<int> expected = {1, 2, 3, 4};
    ASSERT_EQ(result, expected);
}

// Test booleanNot function
TEST_F(SearchTest, BooleanNot) {
    std::set<int> allDocs = {1, 2, 3, 4};
    std::set<int> setToExclude = {2, 3};
    std::set<int> result = booleanNot(allDocs, setToExclude);
    std::set<int> expected = {1, 4};
    ASSERT_EQ(result, expected);
}

// Test booleanSearch function
TEST_F(SearchTest, BooleanSearch) {
    invertedIndex["cat"] = {0, 1};
    invertedIndex["dog"] = {1, 2};
    std::vector<std::string> allDocs = {"doc1", "doc2", "doc3"};

    std::set<int> result = booleanSearch("cat AND dog", allDocs);
    std::set<int> expected = {1};
    ASSERT_EQ(result, expected);

    result = booleanSearch("cat OR dog", allDocs);
    expected = {0, 1, 2};
    ASSERT_EQ(result, expected);

    result = booleanSearch("cat NOT dog", allDocs);
    expected = {0};
    ASSERT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}