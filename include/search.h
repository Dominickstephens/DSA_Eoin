#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <set>
#include <vector>

// Function declarations for Boolean operations
std::set<int> getDocumentsForKeyword(const std::string &keyword);
std::set<int> booleanAnd(const std::set<int> &set1, const std::set<int> &set2);
std::set<int> booleanOr(const std::set<int> &set1, const std::set<int> &set2);
std::set<int> booleanNot(const std::set<int> &allDocs, const std::set<int> &setToExclude);
std::set<int> booleanSearch(const std::string &query, const std::vector<std::string> &allDocs);

#endif // SEARCH_H
