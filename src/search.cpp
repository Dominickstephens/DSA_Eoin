#include "../include/search.h"
#include "IndexEntry.h"
#include "documentIndex.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <sstream>

// Retrieve the set of document IDs for a keyword
std::set<IndexEntry> getDocumentsForKeyword(const std::string& keyword, documentIndex<std::string, vectorClass<IndexEntry>>& index) {
    std::set<IndexEntry> entriesSet;

    // Find the keyword in the document index
    vectorClass<IndexEntry>* entries = index.find(keyword);

    if (entries != nullptr) {
        // Insert all IndexEntry objects into the set
        for (const auto& entry : *entries) {
            entriesSet.insert(entry);  // Assuming IndexEntry has an overloaded '<' operator for std::set
        }
    }

    return entriesSet;  // Return the set of IndexEntry objects
}

// Perform AND operation between two sets of document IDs
std::set<int> booleanAnd(const std::set<int> &set1, const std::set<int> &set2) {
    std::set<int> result;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(result, result.begin()));
    return result;
}

// Perform OR operation between two sets of document IDs
std::set<int> booleanOr(const std::set<int> &set1, const std::set<int> &set2) {
    std::set<int> result;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(result, result.begin()));
    return result;
}

// Perform NOT operation (set difference)
std::set<int> booleanNot(const std::set<int> &allDocs, const std::set<int> &setToExclude) {
    std::set<int> result;
    std::set_difference(allDocs.begin(), allDocs.end(), setToExclude.begin(), setToExclude.end(), std::inserter(result, result.begin()));
    return result;
}

// Boolean search query: handle "AND", "OR", "NOT" operations
std::set<int> booleanSearch(const std::string &query, documentIndex<std::string, vectorClass<IndexEntry>>& index) {
    std::istringstream stream(query);
    std::string token;
    std::set<int> result;
    std::set<int> allDocIDs;

    // Change to size_t
//    for (size_t i = 0; i < index.size(); ++i) {
//        allDocIDs.insert(static_cast<int>(i)); // Ensure we store int in the set
//    }

    std::set<int> currentSet;
    std::string currentOp = "AND";

    while (stream >> token) {
        if (token == "AND" || token == "OR" || token == "NOT") {
            currentOp = token;
        } else {
            std::set<IndexEntry> keywordSet = getDocumentsForKeyword(token, index);
            if (currentOp == "AND") {
                if (result.empty()) {
                    result = keywordSet;
                } else {
                    result = booleanAnd(result, keywordSet);
                }
            } else if (currentOp == "OR") {
                result = booleanOr(result, keywordSet);
            } else if (currentOp == "NOT") {
                result = booleanNot(result, keywordSet);
            }
        }
    }

    return result;
}
