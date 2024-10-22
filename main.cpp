#include "include/indexing.h"
#include "include/search.h"
#include <iostream>
#include <set>
#include <filesystem>
#include <vector>
#include <fstream>
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
        cout << "File does not exist. Serialization performed." << endl;
        DocumentIndexer indexer(booksFolder);
        indexer.performIndexing(index);
        serialize(index, filename); // Call serialize only if the file does not exist
    } else {
        cout << "File already exists. Serialization skipped." << endl;
    }
    documentIndex<string, vectorClass<IndexEntry>> index2;
    deserialize(index2, "index.csv");
    index2.printFirstPair();

    // Load book titles into the Trie for autocomplete suggestions
    loadBookTitles(trie, index2);

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
        std::set<int> results = booleanSearch(autocompleteResult, documents);

        // Display the results
        AsciiArt::printColored("Search Results:\n", pink);
        if (results.empty())
        {
            AsciiArt::printColored("No documents found.\n", pink);
        }
        else
        {
            for (int docID : results)
            {
                std::filesystem::path filePath(documents[docID]);
                std::cout << "Document ID: " << docID << " - " << filePath.filename().string() << " - " << filePath.parent_path().string() << "\n";
            }
        }
    }

    AsciiArt::printColored("Goodbye!\n", yellow);

    return 0;
}
