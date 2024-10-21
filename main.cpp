#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include "include/Trie.h"
#include "include/AutocompleteHandler.h"
#include "src/vectorBook.h"
#include "src/documentIndex.h"
#include "src/IndexEntry.h"
#include "src/serialization.h"
#include "src/DocumentIndexer.h"

using namespace std;

int main() {
    Trie<char> trie;

    const std::string bookDirectory = "../books";

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
