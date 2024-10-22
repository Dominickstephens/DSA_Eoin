#include "../include/AccessBook.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string printLineAtBytePosition(const std::string& fileName, std::streampos bytePosition, const std::string& keyword) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        return "";
    }

    // move file pointer to the specified byte position
    file.seekg(bytePosition);

    std::string line;
    std::getline(file, line);

    // Check if we reached the end of the file
    if (file.eof() && line.empty()) {
        return "";
    } else {
        std::string greenColor = "\033[32m"; // green
        std::string resetColor = "\033[0m";  // reset color

        // Find specified keyword and make it green
        size_t pos = line.find(keyword);
        while (pos != std::string::npos) {
            line.replace(pos, keyword.length(), greenColor + keyword + resetColor);
            pos = line.find(keyword, pos + greenColor.length() + resetColor.length() + keyword.length());
        }

        return line;
    }

    file.close();
}

