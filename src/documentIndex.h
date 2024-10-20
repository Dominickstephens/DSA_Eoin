#ifndef DOCUMENT_INDEX_H
#define DOCUMENT_INDEX_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <functional>
#include "IndexEntry.h"
#include <cmath>


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
                        pair.second[i].bytePositions.push(value.bytePositions[0]);
                        value.bytePositions = pair.second[i].bytePositions;
                        pair.second[i] = value;  // Replace existing value if duplicate
                        return;
                    }
                }
                pair.second.push(value);  // Add value if no duplicate found
                return;
            }
        }
        vectorClass<IndexEntry> vec;
        vec.push(value);
        table[index].emplace_back(key, vec);  // Add new pair if key doesn't exist
        ++numElements;
    }

    void insertFullVector(const KeyType& key, const vectorClass<IndexEntry>& value) {
        if (numElements >= table.size() * loadFactor) {
            rehash();
        }

        size_t index = stringHash(key) % table.size();
        table[index].emplace_back(key, value);  // Add new pair if key doesn't exist
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

    // Print the document index
    void print() {
        for (const auto& bucket : table) {
            if (!bucket.empty()) {
                for (const auto& pair : bucket) {
                    cout << pair.first << ": ";
                    if (!pair.second.empty()) {
                        for (size_t i = 0; i < pair.second.size(); ++i) {
                            cout << pair.second[i];
                            if (i < pair.second.size() - 1) cout << ", "; // Comma separation
                        }
                    } else {
                        cout << "No Values"; // Handle empty value case
                    }
                    cout << endl;
                }
            }
//            else {
//                cout << "Empty Bucket" << endl; // Optional: output for empty buckets
//            }
        }
    }

    // Print the first key-value pair in the document index
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
                return;  // Exit after printing the first pair
            }
        }
        cout << "No elements in the document index." << endl;
    }


    // Remove a specific value from all key-value pairs
    void removeValue(const typename ValueType::value_type& value) {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                auto& vec = pair.second;  // Assuming pair.second is of type ValueType
                vec.remove(value);  // Call the custom remove method defined in vectorClass
            }
        }
    }

    vector<list<pair<KeyType, ValueType>>> table;
private:
    float loadFactor = 0.75;
    const int PRIME_CONST = 31;


    int stringHash (string key) {
        int hashCode = 0;
        for (int i = 0; i < key.length(); i++) {
            hashCode += key[i] * pow(PRIME_CONST, i);
        }
        return hashCode;
    }

    // Hash table (buckets)
    size_t numElements;  // Number of elements in the map

    // Resize and rehash the table when it becomes too full
    void rehash() {
        size_t newSize = table.size() * 2;
        vector<list<pair<KeyType, ValueType>>> newTable(newSize);

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
