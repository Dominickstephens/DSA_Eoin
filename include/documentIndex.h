#ifndef DOCUMENT_INDEX_H
#define DOCUMENT_INDEX_H

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include "IndexEntry.h"
#include <cmath>
#include "../include/pairImp.h"

using namespace std;

template <typename KeyType, typename ValueType>
class documentIndex {
public:
    // Constructor
    explicit documentIndex(size_t size = 10) : table(size), numElements(0) {}

    // Insert a key-value pair
    void insert(const KeyType& key, IndexEntry& value) {
        if (numElements >= table.size() * loadFactor) {
            rehash();
        }

        size_t index = stringHash(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                for (size_t i = 0; i < pair.second.size(); ++i) {
                    if (pair.second[i].filePath == value.filePath) {
                        value.frequency += pair.second[i].frequency;
                        pair.second[i].positionOffsets.push(value.positionOffsets[0]);
                        value.positionOffsets = pair.second[i].positionOffsets;
                        pair.second[i] = value;  
                        return;
                    }
                }
                pair.second.push(value);  
                return;
            }
        }
        vectorClass<IndexEntry> vec;
        vec.push(value);
        table[index].emplace_back(key, vec);  
        ++numElements;
    }

    void insertFullVector(const KeyType& key, const vectorClass<IndexEntry>& value) {
        if (numElements >= table.size() * loadFactor) {
            rehash();
        }

        size_t index = stringHash(key) % table.size();
        table[index].emplace_back(key, value);  
        ++numElements;
    }

    // Find a value by key
    ValueType* find(const KeyType& key) {
        size_t index = stringHash(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    ValueType& at(const KeyType& key) {
        size_t index = stringHash(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw out_of_range("Key not found in documentIndex");
    }

   
    ValueType* end() {
        return nullptr;  // Acts like an "end" for comparison with find()
    }

    bool operator==(const documentIndex& other) const {
        if (numElements != other.numElements) {
            return false;
        }
        if (table.size() != other.table.size()) {
            return false;
        }
        // Compare each bucket in the table
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[i] != other.table[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const documentIndex& other) const {
        return !(*this == other);
    }

    void print() {
        for (const auto& bucket : table) {
            if (!bucket.empty()) {
                for (const auto& pair : bucket) {
                    cout << pair.first << ": ";
                    if (!pair.second.empty()) {
                        for (size_t i = 0; i < pair.second.size(); ++i) {
                            cout << pair.second[i];
                            if (i < pair.second.size() - 1) cout << ", "; 
                        }
                    } else {
                        cout << "No Values"; 
                    }
                    cout << endl;
                }
            }
        }
    }

    void printFirstPair() {
        for (const auto& bucket : table) {
            if (!bucket.empty()) {  // Check for the first non-empty bucket
                const auto& firstPair = bucket.front();  // Get the first key-value pair in the bucket
                cout << "First Key: " << firstPair.first << ", Values: ";
                for (size_t i = 0; i < firstPair.second.size(); ++i) {
                    cout << firstPair.second[i];
                    if (i < firstPair.second.size() - 1) cout << ", ";
                }
                cout << endl;
                return;  
            }
        }
        cout << "No elements in the document index." << endl;
    }

    void removeValueByFileName(const std::string& fileName) {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                auto& vec = pair.second;
                vec.erase(std::remove_if(vec.begin(), vec.end(), [&](const auto& value) {
                    return value.fileName == fileName; // assuming `fileName` is a field in `value`
                }), vec.end());
            }
        }
    }


    vector<vector<Pair<KeyType, ValueType>>> table;
private:
    float loadFactor = 0.75;
    const int PRIME_CONST = 31;

    size_t stringHash(const string& key) {
        size_t hashCode = 0;
        for (char i : key) {
            hashCode = hashCode * PRIME_CONST + i;
        }
        return hashCode;
    }

    size_t numElements;  

    // Resize and rehash the table when it becomes too full
    void rehash() {
        size_t newSize = table.size() * 2;
        vector<vector<Pair<KeyType, ValueType>>> newTable(newSize);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t newIndex = stringHash(pair.first) % newSize;
                newTable[newIndex].emplace_back(pair);
            }
        }
        table = std::move(newTable);
    }
};

#endif
