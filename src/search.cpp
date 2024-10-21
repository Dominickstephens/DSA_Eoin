#include "../include/search.h"
#include "../include/indexing.h"  // To access the inverted index
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <sstream>

// Retrieve the set of document IDs for a keyword
std::set<int> getDocumentsForKeyword(const std::string &keyword) {
    if (invertedIndex.find(keyword) != invertedIndex.end()) {
        return std::set<int>(invertedIndex[keyword].begin(), invertedIndex[keyword].end());
    }
    return {};
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
std::set<int> booleanSearch(const std::string &query, const std::vector<std::string> &allDocs) {
    std::istringstream stream(query);
    std::string token;
    std::set<int> result;
    std::set<int> allDocIDs;

    // Change to size_t
    for (size_t i = 0; i < allDocs.size(); ++i) {
        allDocIDs.insert(static_cast<int>(i)); // Ensure we store int in the set
    }

    std::set<int> currentSet;
    std::string currentOp = "AND";

    while (stream >> token) {
        if (token == "AND" || token == "OR" || token == "NOT") {
            currentOp = token;
        } else {
            std::set<int> keywordSet = getDocumentsForKeyword(token);
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
