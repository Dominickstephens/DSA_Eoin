#ifndef INDEXING_H
#define INDEXING_H

#include <string>
#include <vector>
#include <unordered_map>

// Inverted index (shared globally)
extern std::unordered_map<std::string, std::vector<int>> invertedIndex;

std::vector<std::string> tokenize(const std::string &text);
void indexDocument(const std::string &docContent, int docID);
void buildIndex(const std::vector<std::string> &documentFiles);

#endif
