//
// Created by Dominick on 22/10/2024.
//

#include "../include/AccessBook.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string printLineAtBytePosition(const std::string& fileName, std::streampos bytePosition, const std::string& keyword) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
//        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return "";
    }

    // Move the file pointer to the specified byte position
    file.seekg(bytePosition);

    // Read the line from the current position
    std::string line;
    std::getline(file, line);

    // Check if we reached the end of the file before reading a line
    if (file.eof() && line.empty()) {
//        std::cout << "No line found at byte position " << bytePosition << std::endl;
        return "";
    } else {
        // Coloring the keyword in green
        std::string greenColor = "\033[32m"; // ANSI code for green
        std::string resetColor = "\033[0m";  // ANSI code to reset color

        // Find the keyword in the line and replace it with colored version
        size_t pos = line.find(keyword);
        while (pos != std::string::npos) {
            line.replace(pos, keyword.length(), greenColor + keyword + resetColor);
            pos = line.find(keyword, pos + greenColor.length() + resetColor.length() + keyword.length());
        }

//        std::cout << "Line at byte position " << bytePosition << ": " << line << std::endl;
        return line;
    }

    file.close();
}

