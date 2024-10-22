//
// Created by Dominick on 22/10/2024.
#ifndef DSA_PROJECT_NEWSEARCH_H
#define DSA_PROJECT_NEWSEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "IndexEntry.h"
#include "documentIndex.h"

using namespace std;

bool containsAllKeywords(const vectorClass<string> &keywords, const vectorClass<IndexEntry> &entries, documentIndex<std::string, vectorClass<IndexEntry>> index);

bool containsAnyKeywords(const vectorClass<string> &keywords, const vectorClass<IndexEntry> &entries, documentIndex<std::string, vectorClass<IndexEntry>> index);

bool containsNoneKeywords(const vectorClass<string> &keywords, const vectorClass<IndexEntry> &entries, documentIndex<std::string, vectorClass<IndexEntry>> index);

vectorClass<IndexEntry> search(const string &query, documentIndex<std::string, vectorClass<IndexEntry>> index);

#endif
