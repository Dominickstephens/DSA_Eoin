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

// parse a serialized string into an IndexEntry
IndexEntry parseIndexEntry(const string& str) {
    istringstream ss(str);
    IndexEntry entry;
    string bytePositionsStr;

    getline(ss, entry.filePath, ',');
    getline(ss, entry.fileName, ',');
    ss >> entry.frequency;
    ss.ignore();  // Ignore the comma

    // Extract the byte positions
    getline(ss, bytePositionsStr);
    istringstream bytePositionsStream(bytePositionsStr);
    string bytePosition;

    while (getline(bytePositionsStream, bytePosition, '|')) {
        entry.positionOffsets.push(static_cast<streampos>(stoll(bytePosition)));
    }

    return entry;
}
