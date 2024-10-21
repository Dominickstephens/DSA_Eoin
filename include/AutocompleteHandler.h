#pragma once
#include <string>
#include <windows.h>   // For Windows API
#include "Trie.h"
#include "../src/vectorBook.h"


// Converts a string to lowercase for case-insensitive matching
std::string toLowerCase(const std::string& str);

// Loads book titles from a directory and inserts them into the Trie
void loadBookTitles(Trie<char>& trie, const std::string& directory);

// Sets the cursor position in the console
void setCursorPosition(int x, int y);

// Sets text color in the console using Windows API
void setTextColor(WORD color);

// Sets text color to pink (closest to pink in Windows API)
void setTextColorPink();

// Prints the input and a maximum of 3 suggestions
void printSuggestions(const vectorClass<std::string>& suggestions, const std::string& input, int selectedIndex);

// Returns the last word from the input string
std::string getLastWord(const std::string& input);

// Replaces the last word in the input with a suggestion
std::string replaceLastWord(const std::string& input, const std::string& suggestion);

// Prints the updated input after suggestions
void printUpdatedInput(const std::string& input);

// Handles user input and provides autocomplete functionality
void handleAutocompleteInput(Trie<char>& trie, const std::string& exitCommand);
