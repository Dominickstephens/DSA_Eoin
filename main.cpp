#include <iostream>
#include <filesystem>
#include <fstream>
#include "vectorBook.h"
#include "documentIndex.h"
#include "IndexEntry.h"
#include "serialization.h"
#include <regex>
#include <chrono>
using namespace std::chrono;

using namespace std;

string removePunctuationsAndLower(string& s) {
    string result;
    regex validChar("[a-zA-Z0-9]");
    for (char c : s) {
        if (regex_match(string(1, c), validChar)) { // Check if c matches the regex
            if (isalpha(c) && isupper(c)) {
                c = static_cast<char>(tolower(c));
            }
            result += c;
        }
    }
    s = result;
    return s;
}

int main() {
    documentIndex<string, vectorClass<IndexEntry>> index;

    using recursive_directory_iterator = filesystem::recursive_directory_iterator;
    string bookPath = R"(../books)";
    for (const auto& dirEntry : recursive_directory_iterator(bookPath)) {
        ifstream file(dirEntry.path());
        cout << "Processing " << dirEntry.path() << endl;
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string word;
                while (iss >> word) {
                    word = removePunctuationsAndLower(word);
                    IndexEntry entry;
                    entry.filePath = dirEntry.path().string();
                    entry.fileName = dirEntry.path().filename().string();
                    entry.frequency = 1;
                    entry.lineNumbers.push(1);
                    index.insert(word, entry);
                }
            }
            file.close();
        }
    }

//    index.printFirstPair();
    serialize(index, "index.csv");

    documentIndex<string, vectorClass<IndexEntry>> index2;

    deserialize(index2, "index.csv");



    return 0;

}
