#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <filesystem>
#include <fstream>
#include "vectorBook.h"
#include "documentIndex.h"

using namespace std;

string removePunctuations(string& s) {
    std::string result = "";
    for (char c : s) {
        if (!ispunct(c)) { // If c is not a punctuation character
            result += c;
        }
    }
    s = result;
    return s;
}

int main() {
    documentIndex<string, vector<string>> index;

    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
    string bookPath = R"(C:\Users\Dominick\CLionProjects\DSA_project\books)";
    for (const auto& dirEntry : recursive_directory_iterator(bookPath)) {
        ifstream file(dirEntry.path());
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string word;
                while (iss >> word) {
                    word = removePunctuations(word);
                    index.insert(word, {dirEntry.path().string()});
                }
            }
            file.close();
        }
    }

//    index.print();

    return 0;

}
