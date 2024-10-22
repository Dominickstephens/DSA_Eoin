//
// Created by Dominick on 22/10/2024.
//

#include "../include/IndexEntry.h"
#include "../include/pairImp.h"
#include "../include/AccessBook.h"
#include "../include/AsciiArt.h"

void displayPage(const vectorClass<Pair<IndexEntry, double>>& resultsVector, int currentPage, int itemsPerPage) {
    int startIdx = currentPage * itemsPerPage;
    int endIdx = std::min(startIdx + itemsPerPage, resultsVector.size());


    for (size_t i = startIdx; i < endIdx; ++i) {
        const IndexEntry& entry = resultsVector[i].first;  // Access the IndexEntry

        std::cout << "File Path: " << entry.filePath << std::endl;
        std::cout << "File Name: " << entry.fileName << std::endl;
        const std::string blue = "\033[38;5;153m";
        AsciiArt::printColored("An Excerpt\n", blue);
        for (size_t j = 0; j < 1 && j < entry.positionOffsets.size(); ++j) {
            std::cout << printLineAtBytePosition(entry.filePath, entry.positionOffsets[j], "autocompleteResult") << std::endl;
        }

        std::cout << std::endl << "-----------------" << std::endl;  // Divider for each entry
    }

    std::cout << "Page " << (currentPage + 1) << " of " << ((resultsVector.size() + itemsPerPage - 1) / itemsPerPage) << std::endl;
}

void paginateResults(const vectorClass<Pair<IndexEntry, double>>& resultsVector, int itemsPerPage) {
    int currentPage = 0;
    char command;

    while (true) {
        // Display current page
        displayPage(resultsVector, currentPage, itemsPerPage);

        // User input for pagination
        const std::string blue = "\033[38;5;153m";
        AsciiArt::printColored("Enter '>' for next page, '<' for previous page, 'q' to quit back to search: \n", blue);
        std::cin >> command;

        if (command == '>') {
            // Go to next page if not at the last page
            if ((currentPage + 1) * itemsPerPage < resultsVector.size()) {
                currentPage++;
            } else {
                std::cout << "You are on the last page." << std::endl;
            }
        } else if (command == '<') {
            // Go to previous page if not at the first page
            if (currentPage > 0) {
                currentPage--;
            } else {
                std::cout << "You are on the first page." << std::endl;
            }
        } else if (command == 'q') {
            // Quit the pagination
            break;
        } else {
            std::cout << "Invalid command. Please enter '>' or '<' or 'q'." << std::endl;
        }
    }
}