//
// Created by Dominick on 20/10/2024.
//

#include "../include/IndexEntry.h"

ostream& operator<<(ostream& os, const IndexEntry& entry) {
    os << entry.filePath << "," << entry.fileName << "," << entry.frequency << ",";

    for (size_t i = 0; i < entry.positionOffsets.size(); ++i) {
        os << entry.positionOffsets[i];
        if (i < entry.positionOffsets.size() - 1) {
            os << "|";  // Separate byte positions by pipe
        }
    }
    return os;
}

// Function to parse a serialized string into an IndexEntry
IndexEntry parseIndexEntry(const string& str) {
    istringstream ss(str);
    IndexEntry entry;
    string bytePositionsStr;

    // Extract filePath, fileName, and frequency
    getline(ss, entry.filePath, ',');
    getline(ss, entry.fileName, ',');
    ss >> entry.frequency;
    ss.ignore();  // Ignore the comma

    // Extract the byte positions (split by pipe "|")
    getline(ss, bytePositionsStr);
    istringstream bytePositionsStream(bytePositionsStr);
    string bytePosition;

    while (getline(bytePositionsStream, bytePosition, '|')) {
        // Convert the string to streampos (using stoll for long long conversion)
        entry.positionOffsets.push(static_cast<streampos>(stoll(bytePosition)));
    }

    return entry;
}
