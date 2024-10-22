#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include "IndexEntry.h"
#include "documentIndex.h"


using namespace std;

// Helper function to check if an entry contains all keywords
bool containsAllKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    unordered_set<string> entryFiles;
    for (size_t i = 0; i < entries.size(); ++i) {
        {
            entryFiles.insert(entries[i].filePath);
        }
        for (size_t i = 0; i < keywords.size(); ++i) {
            if (index.find(keywords[i]) == index.end()) return false;
        }
        return true;
    }
}

// Helper function to check if any entry contains any keyword
bool containsAnyKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    for (size_t i = 0; i < keywords.size(); ++i) {
        if (index.find(keywords[i]) != index.end()) {
            return true;
        }
    }
    return false;
}

// Helper function to check if an entry contains none of the keywords
bool containsNoneKeywords(const vectorClass<string>& keywords, const vectorClass<IndexEntry>& entries, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    for (size_t i = 0; i < keywords.size(); ++i) {
        if (index.find(keywords[i]) != index.end()) {
            return false;
        }
    }
    return true;
}

// Function to parse a search query with AND, OR, NOT logic
vectorClass<IndexEntry> search(const string& query, documentIndex<std::string, vectorClass<IndexEntry>> index) {
    vectorClass<IndexEntry> result;

    // Tokenize the query
    stringstream ss(query);
    string token;
    vectorClass<string> andKeywords, orKeywords, notKeywords;
    string logic = "AND";  // Default logic is AND

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


    // AND logic: Find entries that contain all AND keywords
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

    // OR logic: Add entries that contain any OR keywords
    if (!orKeywords.empty()) {
        for (size_t i = 0; i < orKeywords.size(); ++i) {
            {
                if (index.find(orKeywords[i]) != index.end()) {
                    auto &entries = index.at(orKeywords[i]);
                    if (!entries.empty()) { // Ensure entries is not empty
                        for (size_t i = 0; i < entries.size(); ++i) {
                            if (containsAnyKeywords(orKeywords, entries, index)) {
                                result.push(entries[i]);
                            }
                        }
                    }
                }
            }
        }

// NOT logic: Remove entries that contain any NOT keywords
        result.erase_if([&](const IndexEntry &entry) {
            // Check if the entry's filePath exists in the index
            if (index.find(entry.filePath) != index.end()) {
                return !containsNoneKeywords(notKeywords, index.at(entry.filePath), index);
            }
            // If filePath doesn't exist in index, we can keep the entry
            return false; // Don't remove the entry if the filePath isn't found
        });

    }
    return result;

}