#include "../include/search.h"
#include "../include/indexing.h"  // To access the inverted index
#include <algorithm>
#include <set>
#include <string>
#include <vector>

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
    // Example: Simple "AND" search between two keywords
    std::set<int> results1 = getDocumentsForKeyword("keyword1");
    std::set<int> results2 = getDocumentsForKeyword("keyword2");
    
    // Perform AND operation
    std::set<int> result = booleanAnd(results1, results2);
    return result;
}
