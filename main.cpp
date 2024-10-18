#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <filesystem>
#include <fstream>
#include "vectorBook.h"
#include "documentIndex.h"
#include "IndexEntry.h"

using namespace std;


// Overload operator<< for IndexEntry
ostream& operator<<(ostream& os, const IndexEntry& entry) {
    os << "FilePath: " << entry.filePath << ", FileName: " << entry.fileName
       << ", Frequency: " << entry.frequency << ", TF-IDF: " << entry.tf_idf
       << ", Line Numbers: ";
    entry.lineNumbers.print();
    return os;
}

string removePunctuations(string& s) {
    string result;
    for (char c : s) {
        if (!ispunct(c)) { // If c is not a punctuation character
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
                    word = removePunctuations(word);
//                    cout << word << endl;
                    IndexEntry entry;
                    entry.filePath = dirEntry.path().string();
                    entry.fileName = dirEntry.path().filename().string();
                    entry.frequency = 1;
                    entry.tf_idf = 0;
                    entry.lineNumbers.push(1);
//                    vectorClass<IndexEntry> entries;
//                    entries.push(entry);
                    index.insert(word, entry);
                }
            }
            file.close();
        }
    }

//    IndexEntry entry;
//    entry.filePath = "path";
//    entry.fileName = "name";
//    entry.frequency = 1;
//    entry.tf_idf = 0;
//    vectorClass <int> lineNumbers;
//    lineNumbers.push(1);
//    lineNumbers.push(2);
//    lineNumbers.push(3);
//    lineNumbers.push(4);
//    entry.lineNumbers = lineNumbers;
//    IndexEntry entry2;
//    entry2.filePath = "path2";
//    entry2.fileName = "name2";
//    entry2.frequency = 2;
//    entry2.tf_idf = 0;
//    vectorClass <int> lineNumbers2;
//    lineNumbers2.push(1);
//    lineNumbers2.push(2);
//    lineNumbers2.push(3);
//    lineNumbers2.push(4);
//    entry2.lineNumbers = lineNumbers2;
//
//
////    cout << entry << endl;
//    documentIndex <string, vectorClass<IndexEntry>> index;
//    vectorClass<IndexEntry> entries;
//    entries.push(entry);
//    entries.push(entry2);
//    index.insert("word", entries);
//    index.print();

    return 0;

}
