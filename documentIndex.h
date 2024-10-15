#ifndef DOCUMENT_INDEX_H
#define DOCUMENT_INDEX_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;

template <typename KeyType, typename ValueType>
class documentIndex {
public:
    // Constructor
    documentIndex(size_t size = 10) : table(size), numElements(0) {}

    // Insert a key-value pair
    void insert(const KeyType& key, const ValueType& value) {
        if (numElements >= table.size()) {
            rehash();
        }

        size_t index = hashFunction(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;  // Update value if key exists
                return;
            }
        }
        table[index].emplace_back(key, value);  // Add new pair if key doesn't exist
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
            for (const auto& pair : bucket) {
                cout << pair.first << ": ";
                for (const auto& value : pair.second) {
                    cout << value << " ";
                }
                cout << endl;
            }
        }
    }

    // Remove a specific value from all key-value pairs
    void removeValue(const typename ValueType::value_type& value) {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                auto& vec = pair.second;
                vec.erase(remove(vec.begin(), vec.end(), value), vec.end());  // Remove the value from the vector
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
