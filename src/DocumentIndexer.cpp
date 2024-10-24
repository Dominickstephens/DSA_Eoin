//
// Created by Dominick on 20/10/2024.
//

#include "../include/DocumentIndexer.h"
#include "../include/vectorBook.h"


#include <utility>
#include <regex>


using namespace std;
using namespace filesystem;

DocumentIndexer::DocumentIndexer(string  path) : bookPath(std::move(path)) {}

void DocumentIndexer::performIndexing(documentIndex<string, vectorClass<IndexEntry>>& index, vectorClass<Pair<string, int>>& fileWordCount) {
    using recursive_directory_iterator = filesystem::recursive_directory_iterator;

    for (const auto& dirEntry : recursive_directory_iterator(bookPath)) {
        ifstream file(dirEntry.path());
        cout << "Processing " << dirEntry.path() << endl;

        if (file.is_open()) {
            processFile(dirEntry, index, fileWordCount);
            file.close();
        }
    }
}

void DocumentIndexer::processFile(const directory_entry& dirEntry,
                                  documentIndex<string, vectorClass<IndexEntry>>& index, vectorClass<Pair<string, int>>& fileWordCount) {
    ifstream file(dirEntry.path());
    string line;
    int wordCounter = 0;


    while (file) {
        streampos positionOffset = file.tellg();
        if (!getline(file, line)) break;

        istringstream iss(line);
        string word;
        while (iss >> word) {
            word = removePunctuationsAndLower(word);
            if (word.empty()) continue;

            IndexEntry entry;
            entry.filePath = dirEntry.path().string();
            entry.fileName = dirEntry.path().filename().string();
            entry.frequency = 1;
            entry.positionOffsets.push(positionOffset);
            wordCounter++;

            index.insert(word, entry);
        }
    }

    fileWordCount.push(Pair<string, int>(dirEntry.path().filename().string(), wordCounter));
}

string DocumentIndexer::removePunctuationsAndLower(string& s) {
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
