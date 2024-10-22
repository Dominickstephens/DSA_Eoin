//
// Created by Dominick on 20/10/2024.
//

#include "IndexEntry.h"

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
    string modifiedStr = str;

    // Check if the first character is a comma
    if (!str.empty() && str[0] == ',') {
        // Remove the first character (comma)
        modifiedStr = str.substr(1);
    }

    istringstream ss(modifiedStr);
    IndexEntry entry;
    string bytePositionsStr;

    // Extract filePath, fileName, and frequency
    if (getline(ss, entry.filePath, ',') &&
        getline(ss, entry.fileName, ',') &&
        (ss >> entry.frequency)) {
        ss.ignore();  // Ignore the comma

        // Check for empty filePath and log a warning
        if (entry.filePath.empty()) {
            cerr << "Warning: Empty filePath encountered in entry: " << str << endl;
        }

        // Extract the byte positions (split by pipe "|")
        getline(ss, bytePositionsStr);
        istringstream bytePositionsStream(bytePositionsStr);
        string bytePosition;

        while (getline(bytePositionsStream, bytePosition, '|')) {
            // Convert the string to streampos (using stoll for long long conversion)
            try {
                entry.positionOffsets.push(static_cast<streampos>(stoll(bytePosition)));
            } catch (const std::exception& e) {
                cerr << "Error parsing byte position: " << bytePosition << " - " << e.what() << endl;
            }
        }
    } else {
        cerr << "Failed to parse IndexEntry from string: " << str << endl;
        // Handle error, possibly return a default entry or throw
    }

    return entry;
}

