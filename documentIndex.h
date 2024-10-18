#ifndef DOCUMENT_INDEX_H
#define DOCUMENT_INDEX_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <functional>
#include "IndexEntry.h"


using namespace std;

template <typename KeyType, typename ValueType>
class documentIndex {
public:
    // Constructor
    documentIndex(size_t size = 10) : table(size), numElements(0) {}
    float loadFactor = 0.75;

    // Insert a key-value pair
    void insert(const KeyType& key, const IndexEntry& value) {
        if (numElements >= table.size() * loadFactor) {
            rehash();
        }

        size_t index = hashFunction(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second.push(value);  // Update value if key exists
                return;
            }
        }
        vectorClass<IndexEntry> vec;
        vec.push(value);
        table[index].emplace_back(key, vec);  // Add new pair if key doesn't exist
        ++numElements;
    }

    // Find a value by key
    ValueType* find(const KeyType& key) {
        size_t index = hashFunction(key) % table.size();
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



    // Remove a specific value from all key-value pairs
    void removeValue(const typename ValueType::value_type& value) {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                auto& vec = pair.second;  // Assuming pair.second is of type ValueType
                vec.remove(value);  // Call the custom remove method defined in vectorClass
            }
        }
    }

private:
    vector<list<pair<KeyType, ValueType>>> table;  // Hash table (buckets)
    size_t numElements;  // Number of elements in the map
    hash<KeyType> hashFunction;  // Hash function

    // Resize and rehash the table when it becomes too full
    void rehash() {
        size_t newSize = table.size() * 2;
        vector<list<pair<KeyType, ValueType>>> newTable(newSize);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t newIndex = hashFunction(pair.first) % newSize;
                newTable[newIndex].emplace_back(pair);
            }
        }
        table = move(newTable);
    }
};

#endif
