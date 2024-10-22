//
// Created by Dominick on 22/10/2024.
//

#ifndef DSA_PROJECT_NEWSEARCH_H
#define DSA_PROJECT_NEWSEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "IndexEntry.h"  // Assuming you have a header file for IndexEntry
#include "documentIndex.h"  // Assuming you have a header file for documentIndex

using namespace std;

// Helper function to check if an entry contains all keywords
bool containsAllKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index);

// Helper function to check if any entry contains any keyword
bool containsAnyKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index);

// Helper function to check if an entry contains none of the keywords
bool containsNoneKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index);

// Function to parse a search query with AND, OR, NOT logic
vectorClass<IndexEntry> search(const string& query, documentIndex<std::string, vectorClass<IndexEntry>> index);


#endif //DSA_PROJECT_NEWSEARCH_H
