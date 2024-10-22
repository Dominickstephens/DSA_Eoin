
#include "include/search.h"
#include <set>
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
#include "include/newSearch.h"
#include "include/utils.h"
#include "include/quicksort.h"
#include "include/pagination.h"
#include "include/serialization.h"

int main()
{
    // colors
    const std::string yellow = "\033[38;5;229m";
    const std::string blue = "\033[38;5;153m";
    const std::string pink = "\033[38;5;218m";

    // welcome banner

    AsciiArt::printColored("Welcome to the JellyCats Library!\n", yellow);
    AsciiArt::printColored("=============================================\n", yellow);

    // ASCII art
    AsciiArt::printAsciiArtColored("cat_art.txt", pink);

    AsciiArt::printColored("=============================================\n", yellow);

    // dynamically load document files from the "books" folder
    std::vector<std::string> documents;
    std::string booksFolder = "books/";

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

// load book titles into the Trie for autocomplete suggestions
    loadBookTitles(trie, index);

// process a search query with autocomplete
    std::string query;
    while (true)
    {
        AsciiArt::printColored("(Type 'exit' to quit)\n", blue);
        AsciiArt::printColored("Enter search query: ", blue);

        std::string autocompleteResult = handleAutocompleteInput(trie, "exit");

        if (autocompleteResult == "exit")
        {
            break;
        }

        // use the entered term from autocomplete to perform the search
        vectorClass<IndexEntry> results = search(autocompleteResult, index);

        // display results
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
