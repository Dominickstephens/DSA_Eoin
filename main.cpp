#include "include/indexing.h"
#include "include/search.h"
#include <iostream>
#include <set>
#include <filesystem>
#include <vector>

int main() {
    // Step 1: Dynamically load document files from the "books" folder
    std::vector<std::string> documents;
    std::string booksFolder = "books/";

    for (const auto &entry : std::filesystem::directory_iterator(booksFolder)) {
        documents.push_back(entry.path().string());
    }
    
    // Step 2: Build the index for the documents
    buildIndex(documents);

    // Step 3: Process a search query
    std::string query;
    std::cout << "Enter search query: ";
    std::getline(std::cin, query);

    // Perform the search
    std::set<int> results = booleanSearch(query, documents);

    // Display the results
    std::cout << "Search Results:\n";
    for (int docID : results) {
        std::cout << "Document ID: " << docID << " - " << documents[docID] << "\n";
    }

    return 0;
}