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

std::ostream& operator<<(std::ostream& os, const IndexEntry& entry) {
    os << entry.filePath << "," << entry.fileName << "," << entry.frequency << "," << entry.tf_idf << ",";

    // Serialize line numbers (vectorClass<int>)
    for (size_t i = 0; i < entry.lineNumbers.size(); ++i) {
        os << entry.lineNumbers[i];
        if (i < entry.lineNumbers.size() - 1) {
            os << "|";  // Separate line numbers by pipe
        }
    }
    return os;
}

// Function to parse a serialized string into an IndexEntry
IndexEntry parseIndexEntry(string& str) {
    istringstream ss(str);
    IndexEntry entry;
    string lineNumbersStr;

    // Extract filePath, fileName, frequency, and tf_idf
    getline(ss, entry.filePath, ',');
    getline(ss, entry.fileName, ',');
    ss >> entry.frequency;
    ss.ignore();  // Ignore the comma
    ss >> entry.tf_idf;
    ss.ignore();  // Ignore the comma

    // Extract the line numbers (split by pipe "|")
    getline(ss, lineNumbersStr);
    istringstream lineNumbersStream(lineNumbersStr);
    string lineNumber;

    while (getline(lineNumbersStream, lineNumber, '|')) {
        entry.lineNumbers.push(stoi(lineNumber));
    }

    return entry;
}


#endif //DSA_PROJECT_INDEXENTRY_H
