//#include <sstream>
//#include <set>
//#include <string>
//#include "documentIndex.h"  // Include your documentIndex header file
//#include "IndexEntry.h"     // Include your IndexEntry header file
//
//// Perform AND operation between two sets of document paths
//std::set<std::string> booleanAnd(const std::set<std::string> &set1, const std::set<std::string> &set2) {
//    std::set<std::string> result;
//    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(result, result.begin()));
//    return result;
//}
//
//// Perform OR operation between two sets of document paths
//std::set<std::string> booleanOr(const std::set<std::string> &set1, const std::set<std::string> &set2) {
//    std::set<std::string> result;
//    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(result, result.begin()));
//    return result;
//}
//
//// Perform NOT operation (set difference)
//std::set<std::string> booleanNot(const std::set<std::string> &allDocs, const std::set<std::string> &setToExclude) {
//    std::set<std::string> result;
//    std::set_difference(allDocs.begin(), allDocs.end(), setToExclude.begin(), setToExclude.end(), std::inserter(result, result.begin()));
//    return result;
//}
//
//// Helper function to retrieve documents containing a specific keyword
//std::set<std::string> getDocumentsForKeyword(documentIndex<std::string, vectorClass<IndexEntry>> &docIndex, const std::string &keyword) {
//    std::set<std::string> resultSet;
//    auto entries = docIndex.find(keyword);
//
//    if (entries) {
//        // Iterate through all IndexEntry for the keyword and collect document paths
//        for (const auto &entry : *entries) {
//            resultSet.insert(entry.filePath);
//        }
//    }
//
//    return resultSet;
//}
//
//// Boolean search query: handle "AND", "OR", "NOT" operations
//std::set<std::string> booleanSearch(documentIndex<std::string, vectorClass<IndexEntry>> &docIndex, const std::string &query) {
//    std::istringstream stream(query);
//    std::string token;
//    std::set<std::string> result;
//
//    // Get all document paths from the index
////    std::set<std::string> allDocPaths;
////    for (const auto &pair : docIndex.getTable()) {
////        for (const auto &entry : pair.second) {
////            allDocPaths.insert(entry.filePath);
////        }
////    }
//
//    std::string currentOp = "AND";
//    while (stream >> token) {
//        if (token == "AND" || token == "OR" || token == "NOT") {
//            currentOp = token;
//        } else {
//            std::set<std::string> keywordSet = getDocumentsForKeyword(docIndex, token);
//            if (currentOp == "AND") {
//                if (result.empty()) {
//                    result = keywordSet;
//                } else {
//                    result = booleanAnd(result, keywordSet);
//                }
//            } else if (currentOp == "OR") {
//                result = booleanOr(result, keywordSet);
//            } else if (currentOp == "NOT") {
//                result = booleanNot(result, keywordSet);
//            }
//        }
//    }
//
//    return result;
//}
