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

// Function to create a hyperlink
std::string createHyperlink(const std::string &text, const std::string &url)
{
    return "\033]8;;" + url + "\033\\" + text + "\033]8;;\033\\";
}

// Function to URL-encode a string
std::string urlEncode(const std::string &value)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value)
    {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            escaped << c;
        }
        else
        {
            escaped << '%' << std::setw(2) << int((unsigned char)c);
        }
    }

    return escaped.str();
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
    std::string booksFolder = "C:\\Users\\PC\\OneDrive - University of Limerick\\3rd Year\\CS4437\\Development\\DSA Project\\DSA_Eoin\\books\\";

    for (const auto &entry : std::filesystem::directory_iterator(booksFolder))
    {
        documents.push_back(entry.path().string());
    }

    // build the index for the documents
    buildIndex(documents);

    const std::string bookDirectory = "C:\\Users\\PC\\OneDrive - University of Limerick\\3rd Year\\CS4437\\Development\\DSA Project\\DSA_Eoin\\books\\";

    documentIndex<string, vectorClass<IndexEntry>> index;

    Trie<char> trie;

    std::string filename = "index.csv";

    if (!std::filesystem::exists(filename))
    {
        cout << "File does not exist. Serialization performed." << endl;
        DocumentIndexer indexer(bookDirectory);
        indexer.performIndexing(index);
        serialize(index, filename); // Call serialize only if the file does not exist
    }
    else
    {
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
                std::string fileLink = createHyperlink(filePath.filename().string(), "file:///" + urlEncode(filePath.string()));
                std::cout << "Document ID: " << docID << " - " << fileLink << " - " << filePath.parent_path().string() << "\n";
            }
        }
    }

    printColored("Goodbye!\n", yellow);

    return 0;
}
