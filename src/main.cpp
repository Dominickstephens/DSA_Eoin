#include <iostream>
#include <filesystem>
#include <fstream>
#include "vectorBook.h"
#include "documentIndex.h"
#include "IndexEntry.h"
#include "serialization.h"
#include <regex>
#include <chrono>
#include "word_operation.h"

using namespace std::chrono;

using namespace std;

int main() {
    documentIndex<string, vectorClass<IndexEntry>> index;

    using recursive_directory_iterator = filesystem::recursive_directory_iterator;
    string bookPath = R"(../books)";
    for (const auto& dirEntry : recursive_directory_iterator(bookPath)) {
        ifstream file(dirEntry.path());
        cout << "Processing " << dirEntry.path() << endl;
        if (file.is_open()) {
            string line;
            int lineNumber = 1;
            while (getline(file, line)) {
                istringstream iss(line);
                string word;
                while (iss >> word) {
                    word = removePunctuationsAndLower(word);
                    if (word.empty()) {
                        continue;
                    }
                    IndexEntry entry;
                    entry.filePath = dirEntry.path().string();
                    entry.fileName = dirEntry.path().filename().string();
                    entry.frequency = 1;
                    entry.lineNumbers.push(lineNumber);
                    index.insert(word, entry);
                }
                ++lineNumber;
            }
            file.close();
        }
    }

//    index.printFirstPair();
    serialize(index, "index.csv");

    documentIndex<string, vectorClass<IndexEntry>> index2;

    deserialize(index2, "index.csv");

    index2.printFirstPair();



    return 0;

}
