//
// Created by Dominick on 18/10/2024.
//

#ifndef DSA_PROJECT_INDEXENTRY_H
#define DSA_PROJECT_INDEXENTRY_H

#include <sstream>
#include "vectorBook.h"



struct IndexEntry {
    string filePath;     // The full path to the file
    string fileName;     // The name of the file
    int frequency{};            // Count of how often the word appears
    vectorClass<streampos> positionOffsets; // List of line numbers where the word appears
};

struct TfIdfResult {
    IndexEntry* result{};  // Reference to the IndexEntry (ensure the lifetime is properly managed)
    double tf_idf{};
};

// Declare the operator<< here, but define it in the .cpp file
std::ostream& operator<<(std::ostream& os, const IndexEntry& entry);

// Declare the parseIndexEntry function
IndexEntry parseIndexEntry(const std::string& str);



#endif //DSA_PROJECT_INDEXENTRY_H
