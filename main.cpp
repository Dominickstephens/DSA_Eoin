#include <iostream>
#include <filesystem>  // C++17 feature
#include <fstream>
#include <algorithm>   // For std::transform
#include <sstream>     // For splitting titles into words
#include <conio.h>     // For _getch() to handle key detection
#include <windows.h>   // For Windows API functions like SetConsoleTextAttribute
#include "include/Trie.h"  // Trie class definition
#include "include/AutocompleteHandler.h"

int main() {
    Trie<char> trie;

    std::string bookDirectory = "books";  // Directory containing book titles
    loadBookTitles(trie, bookDirectory);

    // Start the autocomplete input loop
    handleAutocompleteInput(trie, "exit");

    return 0;
}
