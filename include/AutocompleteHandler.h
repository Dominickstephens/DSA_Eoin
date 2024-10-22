#pragma once
#include <string>
#include <vector>
#include <windows.h>   // For Windows API
typedef unsigned char byte;  // Explicit declaration
#include "Trie.h"
#include "../src/IndexEntry.h"
#include "../src/documentIndex.h"

// Converts a string to lowercase for case-insensitive matching
std::string toLowerCase(const std::string& str);

// Loads book titles from a directory and inserts them into the Trie
void loadBookTitles(Trie<char>& trie, const documentIndex<std::string, vectorClass<IndexEntry>>& index);

// Sets the cursor position in the console
void setCursorPosition(int x, int y);

// Sets text color in the console using Windows API
void setTextColor(WORD color);

// Sets text color to pink (closest to pink in Windows API)
void setTextColorPink();

// Prints the input and a maximum of 3 suggestions
void printSuggestions(const std::vector<std::string>& suggestions, const std::string& input, int selectedIndex);

// Returns the last word from the input string
std::string getLastWord(const std::string& input);

// Replaces the last word in the input with a suggestion
std::string replaceLastWord(const std::string& input, const std::string& suggestion);

// Prints the updated input after suggestions
void printUpdatedInput(const std::string& input);

// Handles user input and provides autocomplete functionality
std::string handleAutocompleteInput(Trie<char>& trie, const std::string& exitCommand);
