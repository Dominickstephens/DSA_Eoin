#pragma once
#include <string>
#include <vector>
#include <windows.h>
typedef unsigned char byte;
#include "Trie.h"
#include "IndexEntry.h"
#include "documentIndex.h"

std::string toLowerCase(const std::string &str);

// Loads book titles from a directory and inserts them into the Trie
void loadBookTitles(Trie<char> &trie, const documentIndex<std::string, vectorClass<IndexEntry>> &index);

void setCursorPosition(int x, int y);

void setTextColor(WORD color);

void setTextColorPink();

// Prints the input and a maximum of 3 suggestions
void printSuggestions(const std::vector<std::string> &suggestions, const std::string &input, int selectedIndex);


std::string getLastWord(const std::string &input);


std::string replaceLastWord(const std::string &input, const std::string &suggestion);


void printUpdatedInput(const std::string &input);

// Handles user input and provides autocomplete functionality
std::string handleAutocompleteInput(Trie<char> &trie, const std::string &exitCommand);
