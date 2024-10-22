
#include "include/search.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include "include/Trie.h"
#include "include/AutocompleteHandler.h"
#include "include/vectorBook.h"
#include "include/documentIndex.h"
#include "include/IndexEntry.h"
#include "include/serialization.h"
#include "include/DocumentIndexer.h"
#include "include/AsciiArt.h"
#include "src/newSearch.h"
#include "include/AccessBook.h"

// Function to print colored text
void printColored(const std::string &text, const std::string &color)
{
    std::cout << color << text << "\033[0m";
}

// Function to print the ASCII art from a file with a specific color
void printAsciiArtColored(const std::string &filename, const std::string &color)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            printColored(line, color);
            std::cout << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main()
{
    // Colors
    const std::string yellow = "\033[38;5;229m";
    const std::string blue = "\033[38;5;153m";
    const std::string pink = "\033[38;5;218m";

    // Welcome banner

    AsciiArt::printColored("Welcome to the JellyCats Library!\n", yellow);
    AsciiArt::printColored("=============================================\n", yellow);

    // Print ASCII art
    AsciiArt::printAsciiArtColored("cat_art.txt", pink);

    AsciiArt::printColored("=============================================\n", yellow);

    // Step 1: Dynamically load document files from the "books" folder
    std::vector<std::string> documents;
    std::string booksFolder = "books/";

    documentIndex<string, vectorClass<IndexEntry>> index;

    Trie<char> trie;

    std::string filename = "index.csv";

    if (!std::filesystem::exists(filename)) {
        DocumentIndexer indexer(booksFolder);
        indexer.performIndexing(index);
        serialize(index, filename); // Call serialize only if the file does not exist
    } else {
        deserialize(index, "index.csv");
    }

// Load book titles into the Trie for autocomplete suggestions
    loadBookTitles(trie, index);

// Step 3: Process a search query with autocomplete
    std::string query;
    while (true)
    {
        AsciiArt::printColored("(Type 'exit' to quit)\n", blue);
        AsciiArt::printColored("Enter search query: ", blue);

        // Handle autocomplete functionality
        std::string autocompleteResult = handleAutocompleteInput(trie, "exit");

        // If the user types 'exit', break the loop
        if (autocompleteResult == "exit")
        {
            break;
        }

        // Use the selected/entered term from autocomplete to perform the search
        vectorClass<IndexEntry> results = search(autocompleteResult, index);

        // Display the results
        AsciiArt::printColored("Search Results:\n", pink);
        if (results.empty())
        {
            AsciiArt::printColored("No documents found.\n", pink);
        }
        else
        {

            // Loop through and print the results
            for (size_t i = 0; i < results.size(); ++i) {
                std::cout << "File Path: " << results[i].filePath << std::endl;
                std::cout << "File Name: " << results[i].fileName << std::endl;
                for (size_t j = 0; j < 4 && j < results[i].positionOffsets.size(); ++j) {
                    cout << printLineAtBytePosition(results[i].filePath, results[i].positionOffsets[j], autocompleteResult) << endl;
                }
                std::cout << std::endl << "-----------------" << std::endl;  // Divider for each entry
            }

        }
    }

    AsciiArt::printColored("Goodbye!\n", yellow);

    return 0;
}
