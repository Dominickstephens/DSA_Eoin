#include "include/indexing.h"
#include "include/search.h"
#include <iostream>
#include <set>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <fstream>
#include <regex>
#include "include/Trie.h"
#include "include/AutocompleteHandler.h"
#include "src/vectorBook.h"
#include "src/documentIndex.h"
#include "src/IndexEntry.h"
#include "src/serialization.h"
#include "src/DocumentIndexer.h"

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
    printColored("Welcome to the JellyCats Library!\n", yellow);
    printColored("=============================================\n", yellow);

    // Print ASCII art
    printAsciiArtColored("cat_art.txt", pink);

    printColored("=============================================\n", yellow);

    // Step 1: Dynamically load document files from the "books" folder
    std::vector<std::string> documents;
    std::string booksFolder = "books/";

    for (const auto &entry : std::filesystem::directory_iterator(booksFolder))
    {
        documents.push_back(entry.path().string());
    }

    // Step 2: Build the index for the documents
    buildIndex(documents);

    // Step 3: Process a search query
    std::string query;
    while (true)
    {

        printColored("(Type 'exit' to quit)\n", blue);
        printColored("Enter search query: ", blue);
        std::getline(std::cin, query);

        if (query == "exit")
        {
            break;
        }

        // Perform the search
        std::set<int> results = booleanSearch(query, documents);

        // Display the results
        printColored("Search Results:\n", pink);
        if (results.empty())
        {
            printColored("No documents found.\n", pink);
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
    printColored("Goodbye!\n", yellow);


        Trie<char> trie;

    const std::string bookDirectory = "books";

    documentIndex<string, vectorClass<IndexEntry>> index;

    // Create DocumentIndexer and perform indexing
    DocumentIndexer indexer(bookDirectory);
    indexer.performIndexing(index);


    serialize(index, "index.csv");
    documentIndex<string, vectorClass<IndexEntry>> index2;
    deserialize(index2, "index.csv");
    index2.printFirstPair();

    loadBookTitles(trie, bookDirectory);
    handleAutocompleteInput(trie, "exit");

    return 0;
}