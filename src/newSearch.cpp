#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include "../include/IndexEntry.h"
#include "../include/documentIndex.h"


using namespace std;

bool containsAllKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    unordered_set<string> entryFiles;
    for (size_t i = 0; i < entries.size(); ++i) {
        {
            entryFiles.insert(entries[i].filePath);
        }
        for (size_t i = 0; i < keywords.size(); ++i) {
            if (index.find(keywords[i]) == index.end()) return false;
        }
    }
       return true;
}

bool containsAnyKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    for (size_t i = 0; i < keywords.size(); ++i) {
        if (index.find(keywords[i]) != index.end()) {
            return true;
        }
    }
    return false;
}

bool containsNoneKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    for (size_t i = 0; i < keywords.size(); ++i) {
        if (index.find(keywords[i]) != index.end()) {
            return false;
        }
    }
    return true;
}

// parse a search query with AND, OR, NOT logic
vectorClass<IndexEntry> search(const string& query, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    vectorClass<IndexEntry> result;

    // tokenize the query
    stringstream ss(query);
    string token;
    vectorClass<string> andKeywords, orKeywords, notKeywords;
    string logic = "AND";  // default logic is AND

    while (ss >> token) {
        if (token == "AND" || token == "OR" || token == "NOT") {
            logic = token;
        } else {
            if (logic == "AND") {
                andKeywords.push(token);
            } else if (logic == "OR") {
                orKeywords.push(token);
            } else if (logic == "NOT") {
                notKeywords.push(token);
            }
        }
    }

    // AND logic: find entries that contain all AND keywords
    if (!andKeywords.empty()) {
        for (size_t i = 0; i < andKeywords.size(); ++i) {
            if (index.find(andKeywords[i]) != index.end()) {
                auto &entries = index.at(andKeywords[i]);
                if (!entries.empty()) { // Ensure entries is not empty
                    for (size_t i = 0; i < entries.size(); ++i) {
                        if (containsAllKeywords(andKeywords, entries, index)) {
                            result.push(entries[i]);
                        }
                    }
                }
            }
        }
    }

    // OR logic: add entries that contain any OR keywords
    if (!orKeywords.empty()) {
        for (size_t i = 0; i < orKeywords.size(); ++i) {
            {
                if (index.find(orKeywords[i]) != index.end()) {
                    auto &entries = index.at(orKeywords[i]);
                    if (!entries.empty()) { // Ensure entries is not empty
                        for (const auto &entry: entries) {
                            if (containsAnyKeywords(andKeywords, entries, index)) {
                                result.push(entry);
                            }
                        }
                    }
                }
            }
        }

// NOT logic: remove entries that contain any NOT keywords
        result.erase_if([&](const IndexEntry &entry) {
            if (index.find(entry.filePath) != index.end()) {
                return !containsNoneKeywords(notKeywords, index.at(entry.filePath), index);
            }
            return false; // Don't remove the entry if the filePath isn't found
        });

    }
    return result;

}