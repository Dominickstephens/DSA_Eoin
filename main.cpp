#include "include/indexing.h"
#include "include/search.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include "include/Trie.h"
#include "include/AutocompleteHandler.h"
#include "include/vectorBook.h"
#include "include/documentIndex.h"
#include "include/IndexEntry.h"
#include "include/serialization.h"
#include "include/DocumentIndexer.h"

// print colored text
void printColored(const std::string &text, const std::string &color)
{
    std::cout << color << text << "\033[0m";
}

// print the ASCII art
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
    // colors
    const std::string yellow = "\033[38;5;229m";
    const std::string blue = "\033[38;5;153m";
    const std::string pink = "\033[38;5;218m";

    // welcome banner
    printColored("Welcome to the JellyCats Library!\n", yellow);
    printColored("=============================================\n", yellow);

    // ASCII art
    printAsciiArtColored("cat_art.txt", pink);

    printColored("=============================================\n", yellow);

    // dynamically load document files from the "books" folder
    std::vector<std::string> documents;
    std::string booksFolder = "books/";

    for (const auto &entry : std::filesystem::directory_iterator(booksFolder))
    {
        documents.push_back(entry.path().string());
    }

    // build the index for the documents
    buildIndex(documents);

    const std::string bookDirectory = "books/";

    documentIndex<string, vectorClass<IndexEntry>> index;

    Trie<char> trie;

    std::string filename = "index.csv";

    if (!std::filesystem::exists(filename)) {
        cout << "File does not exist. Serialization performed." << endl;
        DocumentIndexer indexer(bookDirectory);
        indexer.performIndexing(index);
        serialize(index, filename); 
    } else {
        cout << "File already exists. Serialization skipped." << endl;
    }
    documentIndex<string, vectorClass<IndexEntry>> index2;
    deserialize(index2, "index.csv");
    index2.printFirstPair();

    // load book titles into the Trie for autocomplete suggestions
    loadBookTitles(trie, index2);

    // process a search query with autocomplete
    std::string query;
    while (true)
    {
        printColored("(Type 'exit' to quit)\n", blue);
        printColored("Enter search query: ", blue);

        std::string autocompleteResult = handleAutocompleteInput(trie, "exit");

        if (autocompleteResult == "exit")
        {
            break;
        }

        // use the entered term from autocomplete to perform the search
        Set<int> results = booleanSearch(autocompleteResult, documents);

       // display results
        printColored("Search Results:\n", pink);
        if (results.toVector().empty())
        {
            printColored("No documents found.\n", pink);
        }
        else
        {
            for (int docID : results.toVector())
            {
                std::filesystem::path filePath(documents[docID]);
                std::cout << "Document ID: " << docID << " - " << filePath.filename().string() << " - " << filePath.parent_path().string() << "\n";
            }
        }
    }

    printColored("Goodbye!\n", yellow);

    return 0;
}
