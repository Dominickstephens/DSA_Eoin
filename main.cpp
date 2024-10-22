
#include "include/search.h"
#include <iostream>
#include <set>
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include "include/Trie.h"
#include "include/AutocompleteHandler.h"
#include "src/vectorBook.h"
#include "src/documentIndex.h"
#include "src/IndexEntry.h"
#include "src/serialization.h"
#include "src/DocumentIndexer.h"
#include "include/AsciiArt.h"
#include "src/newSearch.h"
#include "include/AccessBook.h"


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
    AsciiArt::printAsciiArtColored(R"(C:\Users\Dominick\CLionProjects\DSA_project\cat_art.txt)", pink);

    AsciiArt::printColored("=============================================\n", yellow);

    // Step 1: Dynamically load document files from the "books" folder
    std::vector<std::string> documents;
    std::string booksFolder = R"(C:\Users\Dominick\CLionProjects\DSA_project\books)";

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
