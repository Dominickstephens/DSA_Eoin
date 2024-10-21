//
// Created by Dominick on 20/10/2024.
//

#include "IndexEntry.h"

ostream& operator<<(ostream& os, const IndexEntry& entry) {
    os << entry.filePath << "," << entry.fileName << "," << entry.frequency << ",";

    for (size_t i = 0; i < entry.bytePositions.size(); ++i) {
        os << entry.bytePositions[i];
        if (i < entry.bytePositions.size() - 1) {
            os << "|";  // Separate byte positions by pipe
        }
    }
    return os;
}

bool operator<(const IndexEntry& lhs, const IndexEntry& rhs) {

    // If filePath is the same, compare by frequency
    if (lhs.frequency != rhs.frequency) {
        return lhs.frequency < rhs.frequency;
    }

    // You can add additional comparisons if needed (e.g., fileName or bytePositions)
    return lhs.fileName < rhs.fileName;
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
        entry.bytePositions.push(static_cast<streampos>(stoll(bytePosition)));
    }

    return entry;
}
