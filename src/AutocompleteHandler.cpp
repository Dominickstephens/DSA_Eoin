#include "../include/AutocompleteHandler.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <conio.h>
#include <windows.h>

namespace fs = std::filesystem;

// Helper function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

// Function to load book titles and insert each word into the Trie
void loadBookTitles(Trie<char>& trie, const std::string& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            std::string lowerTitle = toLowerCase(filename);  // Convert to lowercase for case-insensitivity

            // Insert the full title
            trie.insert(lowerTitle);

            // Split the title into words and insert each word
            std::istringstream iss(lowerTitle);
            std::string word;
            while (iss >> word) {
                trie.insert(word);
            }
        }
    }
}

// Function to set cursor position
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to set text color
void setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Set text color to pink (closest to pink using Windows API)
void setTextColorPink() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// Prints the input and suggestions inline
void printSuggestions(const std::vector<std::string>& suggestions, const std::string& input, std::vector<std::string>::size_type selectedIndex) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    setCursorPosition(0, csbi.dwCursorPosition.Y);
    std::cout << std::string(csbi.dwSize.X, ' ');
    setCursorPosition(0, csbi.dwCursorPosition.Y);

    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // White for input
    std::cout << input;

    setTextColor(FOREGROUND_INTENSITY);  // Gray for suggestions
    size_t limit = std::min(suggestions.size(), static_cast<size_t>(3));  // Limit to 3 suggestions
    for (size_t i = 0; i < limit; ++i) {
        if (i == selectedIndex) {
            setTextColorPink();  // Highlight selected suggestion
        }
        std::cout << " | " << suggestions[i];
        setTextColor(FOREGROUND_INTENSITY);  // Reset for next suggestions
    }

    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // Reset
    std::cout.flush();
}

// Returns the last word from input
std::string getLastWord(const std::string& input) {
    std::istringstream iss(input);
    std::string lastWord;
    while (iss >> lastWord) {}
    return lastWord;
}

// Replaces the last word in input with a suggestion
std::string replaceLastWord(const std::string& input, const std::string& suggestion) {
    size_t lastSpace = input.find_last_of(' ');
    if (lastSpace != std::string::npos) {
        return input.substr(0, lastSpace + 1) + suggestion;
    } else {
        return suggestion;  // No spaces, replace the entire input
    }
}

// Prints updated input after accepting suggestions
void printUpdatedInput(const std::string& input) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    setCursorPosition(0, csbi.dwCursorPosition.Y);
    std::cout << std::string(csbi.dwSize.X, ' ');
    setCursorPosition(0, csbi.dwCursorPosition.Y);

    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // White for typed input
    std::cout << input;

    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // Reset
    std::cout.flush();
}

// Handles the autocomplete functionality and user input
std::string handleAutocompleteInput(Trie<char>& trie, const std::string& exitCommand) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));  // Disable line input and echo

    std::string input;
    char c;
    DWORD charsRead;
    std::vector<std::string>::size_type selectedIndex = 0;
    std::vector<std::string> suggestions;  // Declare once

    while (true) {
        input.clear();
        selectedIndex = 0;

        while (true) {
            if (ReadConsoleA(hInput, &c, 1, &charsRead, NULL) && charsRead == 1) {
                if (c == '\b') {
                    if (!input.empty()) {
                        input.pop_back();
                    }
                    selectedIndex = 0;
                } else if (c == '\r') {  // When Enter is pressed
                    printUpdatedInput(input);
                    std::cout << std::endl;
                    return input;  // Return the input to submit the search query
                } else if (c == '\t') {
                    if (!suggestions.empty() && selectedIndex < suggestions.size()) {
                        input = replaceLastWord(input, suggestions[selectedIndex]);
                    }
                    printUpdatedInput(input);
                } else if (c == 'n') {
                    if (!suggestions.empty()) {
                        selectedIndex = (selectedIndex + 1) % suggestions.size();  // Cycle forward
                    }
                } else if (c == 'p') {
                    if (!suggestions.empty()) {
                        selectedIndex = (selectedIndex == 0) ? suggestions.size() - 1 : selectedIndex - 1;  // Cycle backward
                    }
                } else {
                    input += c;
                }

                if (input.empty()) {
                    suggestions.clear();
                    selectedIndex = 0;
                } else {
                    std::string lastWord = toLowerCase(getLastWord(input));
                    suggestions = trie.autocomplete(lastWord);  // Update suggestions
                }

                printSuggestions(suggestions, input, selectedIndex);
            }
        }

        if (input == exitCommand) {
            break;
        }
    }

    SetConsoleMode(hInput, mode);  // Restore original console mode
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // Reset text color
    return input;
}
