#include "include/indexing.h"
#include "include/search.h"
#include <iostream>
#include <set>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

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

// Function to display a loading animation
void showLoadingAnimation(const std::string &message, int duration)
{
    const std::string animation = "|/-\\";
    int animationIndex = 0;
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(duration))
    {
        std::cout << "\r" << message << " " << animation[animationIndex++ % animation.size()] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\r" << message << " Done!" << std::endl;
}
int main()
{
    // Colors
    const std::string yellow = "\033[38;5;229m";
    const std::string blue = "\033[38;5;153m";
    const std::string pink = "\033[38;5;218m";

    // Welcome banner
    printColored("  Welcome to the JellyCats Library!\n", yellow);
    printColored("====================================\n", yellow);

    // Print ASCII art
    printAsciiArtColored("cat_art.txt", pink);

    printColored("====================================\n", yellow);

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
    printColored("Enter search query: ", blue);
    std::getline(std::cin, query);

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
            std::cout << "Document ID: " << docID << " - " << documents[docID] << "\n";
        }
    }

    return 0;
}