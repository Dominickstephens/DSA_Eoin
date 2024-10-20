#include <iostream>
#include <filesystem>  // C++17 feature
#include <fstream>
#include <algorithm>   // For std::transform
#include <sstream>     // For splitting titles into words
#include <conio.h>     // For _getch() to handle Tab key detection
#include <windows.h>   // For Windows API functions like SetConsoleTextAttribute
#include "include/Trie.h"  // Trie class definition

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

// Set cursor position in the console
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Set text color in the console using Windows API
void setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Print input and the suggestions
void printSuggestions(const std::vector<std::string>& suggestions, const std::string& input) {
    // Clear the current line by moving the cursor back and clearing to the end
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    setCursorPosition(0, csbi.dwCursorPosition.Y);
    std::cout << std::string(csbi.dwSize.X, ' ');  // Clear the current line
    setCursorPosition(0, csbi.dwCursorPosition.Y);  // Move the cursor back to the start

    // Print the input in white (default)
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // White for typed input
    std::cout << input;

    // Print suggestions below the input
    setTextColor(FOREGROUND_INTENSITY);  // Gray for suggestions
    for (const auto& suggestion : suggestions) {
        std::cout << " | " << suggestion;  // Display suggestions inline
    }

    // Reset the color
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout.flush();  // Ensure the output is updated immediately
}

int main() {
    // Create a Trie for characters (strings of type char)
    Trie<char> trie;

    // Load book titles from the "books" directory into the trie
    std::string bookDirectory = "../books";  // Adjust the path if needed
    loadBookTitles(trie, bookDirectory);

    // Set up the console to read input character by character
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));  // Disable line input and echo

    std::string input;
    char c;
    DWORD charsRead;

    while (true) {
        // Clear the input string for a new word
        input.clear();

        while (true) {
            // Read character-by-character input
            if (ReadConsoleA(hInput, &c, 1, &charsRead, NULL) && charsRead == 1) {
                if (c == '\b') {  // Handle backspace
                    if (!input.empty()) {
                        input.pop_back();
                    }
                } else if (c == '\r') {  // Handle Enter key (finish word)
                    std::cout << std::endl;
                    break;
                } else {
                    input += c;  // Append the character to input
                }

                // Find and display the suggestions from the Trie
                std::string lowerPrefix = toLowerCase(input);
                std::vector<std::string> suggestions = trie.autocomplete(lowerPrefix);

                // Print the input and suggestions together
                printSuggestions(suggestions, input);
            }
        }

        // Check if the user wants to exit
        if (input == "exit") {
            break;
        }
    }

    // Restore the console mode before exiting
    SetConsoleMode(hInput, mode);
    return 0;
}
