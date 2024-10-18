//
// Created by Dominick on 18/10/2024.
//

#ifndef DSA_PROJECT_INDEXENTRY_H
#define DSA_PROJECT_INDEXENTRY_H

#include "vectorBook.h"



struct IndexEntry {
    string filePath;     // The full path to the file
    string fileName;     // The name of the file
    int frequency{};            // Count of how often the word appears
    long tf_idf{};              // Term frequency-inverse document frequency
    vectorClass<int> lineNumbers; // List of line numbers where the word appears
};

// Overload operator<< for IndexEntry
ostream& operator<<(ostream& os, const IndexEntry& entry) {
    os << "FilePath: " << entry.filePath << ", FileName: " << entry.fileName
       << ", Frequency: " << entry.frequency << ", TF-IDF: " << entry.tf_idf
       << ", Line Numbers: ";
    entry.lineNumbers.print();
    return os;
}


#endif //DSA_PROJECT_INDEXENTRY_H
