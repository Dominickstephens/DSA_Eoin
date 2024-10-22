#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/indexing.h"
#include "../include/utils.h" 


class IndexingTest : public ::testing::Test {
protected:
    void SetUp() override {
        invertedIndex.clear();
    }
};

// indexDocument
TEST_F(IndexingTest, IndexDocument) {
    std::string docContent = "this is a test document";
    int docID = 1;
    indexDocument(docContent, docID);

    ASSERT_EQ(invertedIndex["this"], std::vector<int>({docID}));
    ASSERT_EQ(invertedIndex["is"], std::vector<int>({docID}));
    ASSERT_EQ(invertedIndex["a"], std::vector<int>({docID}));
    ASSERT_EQ(invertedIndex["test"], std::vector<int>({docID}));
    ASSERT_EQ(invertedIndex["document"], std::vector<int>({docID}));
}

//  buildIndex 
TEST_F(IndexingTest, BuildIndex) {
    std::vector<std::string> documentFiles = {"doc1.txt", "doc2.txt"};

    std::ofstream file1("doc1.txt");
    file1 << "hello world";
    file1.close();

    std::ofstream file2("doc2.txt");
    file2 << "goodbye world";
    file2.close();

    buildIndex(documentFiles);

    ASSERT_EQ(invertedIndex["hello"], std::vector<int>({0}));
    ASSERT_EQ(invertedIndex["world"], std::vector<int>({0, 1}));
    ASSERT_EQ(invertedIndex["goodbye"], std::vector<int>({1}));

    std::remove("doc1.txt");
    std::remove("doc2.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}