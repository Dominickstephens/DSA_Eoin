//
// Created by Dominick on 19/10/2024.
//

#ifndef DSA_PROJECT_SERIALIZATION_H
#define DSA_PROJECT_SERIALIZATION_H


//
// Created by Dominick on 19/10/2024.
//


#include "documentIndex.h"
#include "IndexEntry.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Serialize function to save the document index to a text file
template <typename KeyType, typename ValueType>
void serialize(const documentIndex<KeyType, ValueType>& index, const string& filename) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        // Iterate through all buckets in the hash table
        for (const auto& bucket : index.table) {
            for (const auto& pair : bucket) {
                // Write the key
                outfile << pair.first << ":";

                // Serialize the vectorClass<IndexEntry> for the key
                const auto& values = pair.second;
                for (size_t i = 0; i < values.size(); ++i) {
                    outfile << values[i];  // Serialize each IndexEntry
                    if (i < values.size() - 1) {
                        outfile << ";";  // Separate multiple IndexEntries by semicolon
                    }
                }
                outfile << endl;  // New line for the next key-value pair
            }
        }
        outfile.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}


template <typename KeyType, typename ValueType>
void deserialize(documentIndex<KeyType, ValueType>& index, const string& filename) {
    ifstream infile(filename);
    string line;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            istringstream ss(line);
            string keyStr;
            string valuesStr;

            // Split the line into the key and values part
            if (getline(ss, keyStr, ':') && getline(ss, valuesStr)) {
                KeyType key = keyStr;  // Convert string to KeyType if needed

                // Split the values part by semicolon to get each IndexEntry
                istringstream valuesStream(valuesStr);
                string entryStr;
                vectorClass<IndexEntry> entries;

                while (getline(valuesStream, entryStr, ';')) {
                    IndexEntry entry = parseIndexEntry(entryStr);  // Deserialize each IndexEntry
                    entries.push(entry);
                }

                index.insertFullVector(key, entries);
            }
        }
        infile.close();
    } else {
        cerr << "Unable to open file for reading." << endl;
    }
}


#endif //DSA_PROJECT_SERIALIZATION_H