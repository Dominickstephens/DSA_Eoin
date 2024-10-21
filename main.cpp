#include <iostream>
#include <filesystem>  // C++17 feature
#include <fstream>
#include <algorithm>   // For std::transform
#include <sstream>     // For splitting titles into words
#include <conio.h>     // For _getch() to handle key detection
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

// Set text color in the console using Windows API (closest to pink)
void setTextColorPink() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Magenta is a combination of red and blue with intensity for brightness
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// Print input and the suggestions
void printSuggestions(const std::vector<std::string>& suggestions, const std::string& input, int selectedIndex) {
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
    for (size_t i = 0; i < suggestions.size(); ++i) {
        if (i == selectedIndex) {
            setTextColorPink();  // Set the color to magenta (closest to pink)
        }
        std::cout << " | " << suggestions[i];  // Display suggestions inline
        setTextColor(FOREGROUND_INTENSITY);  // Reset color for next suggestions
    }

    // Reset the color
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout.flush();  // Ensure the output is updated immediately
}

// Function to get the last word from input
std::string getLastWord(const std::string& input) {
    std::istringstream iss(input);
    std::string lastWord;
    while (iss >> lastWord) {}  // Extract last word
    return lastWord;
}

// Function to replace the last word with a suggestion
std::string replaceLastWord(const std::string& input, const std::string& suggestion) {
    std::string result = input;
    size_t lastSpace = result.find_last_of(' ');
    if (lastSpace != std::string::npos) {
        result = result.substr(0, lastSpace + 1) + suggestion;  // Replace only the last word
    } else {
        result = suggestion;  // No spaces, replace the entire input
    }
    return result;
}

// Function to print the updated input
void printUpdatedInput(const std::string& input) {
    // Clear the current line and print the updated input
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    setCursorPosition(0, csbi.dwCursorPosition.Y);
    std::cout << std::string(csbi.dwSize.X, ' ');  // Clear the current line
    setCursorPosition(0, csbi.dwCursorPosition.Y);  // Move the cursor back to the start

    // Print the input
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // White for typed input
    std::cout << input;

    // Reset the color
    setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout.flush();  // Ensure the output is updated immediately
}

int main() {
    // Create a Trie for characters (strings of type char)
    Trie<char> trie;

    // Load book titles from the "books" directory into the trie
    std::string bookDirectory = "books";  // Adjust the path if needed
    loadBookTitles(trie, bookDirectory);

    // Set up the console to read input character by character
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));  // Disable line input and echo

    std::string input;
    char c;
    DWORD charsRead;
    int selectedIndex = 0;  // Index of the currently selected suggestion

    while (true) {
        // Clear the input string for a new word
        input.clear();
        selectedIndex = 0;  // Reset selection for each new input

        while (true) {
            // Read character-by-character input
            if (ReadConsoleA(hInput, &c, 1, &charsRead, NULL) && charsRead == 1) {
                if (c == '\b') {  // Handle backspace
                    if (!input.empty()) {
                        input.pop_back();
                    }
                    selectedIndex = 0;  // Reset selection on backspace
                } else if (c == '\r') {  // Handle Enter key (finish word)
                    // Move to next line after printing the input
                    printUpdatedInput(input);
                    std::cout << std::endl;
                    break;
                } else if (c == '\t') {  // Handle Tab key (accept suggestion)
                    std::vector<std::string> suggestions = trie.autocomplete(getLastWord(input));
                    if (!suggestions.empty() && selectedIndex < suggestions.size()) {
                        input = replaceLastWord(input, suggestions[selectedIndex]);  // Replace with selected suggestion
                    }
                    printUpdatedInput(input); // Print updated input
                    // Keep the cursor on the same line
                } else if (c == 'n') {  // Next suggestion (using 'n' key)
                    // Don't add 'n' to input
                    selectedIndex++;
                } else if (c == 'p') {  // Previous suggestion (using 'p' key)
                    // Don't add 'p' to input
                    selectedIndex--;
                } else {
                    input += c;  // Append the character to input
                }

                // Get the last word for suggestions
                std::string lastWord = getLastWord(input);
                std::string lowerPrefix = toLowerCase(lastWord);
                std::vector<std::string> suggestions = trie.autocomplete(lowerPrefix);

                // Adjust selected index to stay within bounds
                if (suggestions.empty()) {
                    selectedIndex = 0; // No suggestions
                } else {
                    if (selectedIndex < 0) {
                        selectedIndex = suggestions.size() - 1; // Wrap to last suggestion
                    } else if (selectedIndex >= suggestions.size()) {
                        selectedIndex = 0; // Wrap to first suggestion
                    }
                }

                // Print the input and suggestions together
                printSuggestions(suggestions, input, selectedIndex);
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