#include "../include/search.h"
#include "../include/indexing.h" 
#include "../include/Set.h"
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

// get the set of document IDs for a keyword
Set<int> getDocumentsForKeyword(const std::string &keyword) {
    Set<int> result;
    if (invertedIndex.find(keyword) != invertedIndex.end()) {
        for (const auto& docID : invertedIndex[keyword]) {
            result.insert(docID);
        }
    }
    return result;
}

Set<int> booleanAnd(const Set<int> &set1, const Set<int> &set2) {
    return set1.setIntersection(set2);
}

Set<int> booleanOr(const Set<int> &set1, const Set<int> &set2) {
    return set1.setUnion(set2);
}

Set<int> booleanNot(const Set<int> &allDocs, const Set<int> &setToExclude) {
    return allDocs.setDifference(setToExclude);
}

// handle "AND", "OR", "NOT" operations
Set<int> booleanSearch(const std::string &query, const std::vector<std::string> &allDocs) {
    std::istringstream stream(query);
    std::string token;
    Set<int> result;
    Set<int> allDocIDs;

    for (size_t i = 0; i < allDocs.size(); ++i) {
        allDocIDs.insert(static_cast<int>(i)); // Ensure we store int in the set
    }

    Set<int> currentSet;
    std::string currentOp = "AND";

    while (stream >> token) {
        if (token == "AND" || token == "OR" || token == "NOT") {
            currentOp = token;
        } else {
            Set<int> keywordSet = getDocumentsForKeyword(token);
            if (currentOp == "AND") {
                if (result.toVector().empty()) {
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
