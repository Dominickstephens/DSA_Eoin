#include "../include/indexing.h"
#include "../include/utils.h" 
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::vector<int>> invertedIndex;

// tokenize document content and update the inverted index
void indexDocument(const std::string &docContent, int docID) {
    std::vector<std::string> tokens = tokenize(docContent);
    for (const std::string &token : tokens) {
        invertedIndex[token].push_back(docID);
    }
}

void buildIndex(const std::vector<std::string> &documentFiles) {
    for (int i = 0; i < documentFiles.size(); ++i) {
        std::ifstream file(documentFiles[i]);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        indexDocument(content, i); // assign document ID based on index
    }
}
