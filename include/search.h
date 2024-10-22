#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "Set.h"

Set<int> getDocumentsForKeyword(const std::string &keyword);
Set<int> booleanAnd(const Set<int> &set1, const Set<int> &set2);
Set<int> booleanOr(const Set<int> &set1, const Set<int> &set2);
Set<int> booleanNot(const Set<int> &allDocs, const Set<int> &setToExclude);
Set<int> booleanSearch(const std::string &query, const std::vector<std::string> &allDocs);

#endif 
