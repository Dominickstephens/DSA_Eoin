
#include "include/search.h"
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
#include "include/utils.h"
#include "include/quicksort.h"
#include "include/pagination.h"

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
    vectorClass<Pair<string, int>> fileWordCount;

    Trie<char> trie;

    std::string filename = "index.csv";
    std::string Wordfilename = "WordCount.csv";

    if (!std::filesystem::exists(filename)) {
        DocumentIndexer indexer(booksFolder);
        indexer.performIndexing(index,fileWordCount);
        serialize(index, filename); // Call serialize only if the file does not exist
        serializeWords(fileWordCount, Wordfilename);
    } else {
        deserialize(index, "index.csv");
        deserializeWords(fileWordCount, "WordCount.csv");
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
            vectorClass<Pair<IndexEntry, double>> resultsVector;
            for (size_t i = 0; i < results.size(); ++i) {
//              generate tf-idf score
                int wordCount = getWordCount("specificWord", fileWordCount);
                double tf_idf = calculate_tf_idf(results[i].frequency, wordCount, fileWordCount.size(), results.size());
                resultsVector.push(Pair(results[i], tf_idf));

            }

            quickSort(resultsVector, 0, resultsVector.size() - 1);

            int itemsPerPage = 5;
            paginateResults(resultsVector, itemsPerPage);

        }
    }

    AsciiArt::printColored("Goodbye!\n", yellow);

    return 0;
}
