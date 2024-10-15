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
//    documentIndex<string, vector<string>> index;
//
//    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
//    string bookPath = R"(C:\Users\Dominick\CLionProjects\DSA_project\books)";
//    for (const auto& dirEntry : recursive_directory_iterator(bookPath)) {
//        ifstream file(dirEntry.path());
//        if (file.is_open()) {
//            string line;
//            while (getline(file, line)) {
//                istringstream iss(line);
//                string word;
//                while (iss >> word) {
//                    word = removePunctuations(word);
//                    index.insert(word, {dirEntry.path().string()});
//                }
//            }
//            file.close();
//        }
//    }
//
////    print out find
//    auto* value = index.find("Fem├¡neo");
//    if (value) {
//        for (const auto& book : *value) {
//            cout << book << " ";
//        }
//        cout << endl;
//    }
//
//    index.print();


    // Create an instance of vectorClass with int
    vectorClass<int> v;

    v.push(10);
    v.push(20);
    v.push(30);
    v.push(40);

// Print the elements
    v.print(); // Output: 10 20 30 40

    cout << "Element at index 2: " << v.get(2) << endl; // Output: 30
    cout << "Size of vector: " << v.size() << endl;     // Output: 4
    cout << "Capacity of vector: " << v.getcapacity() << endl; // Output: 4 or more

// Use vectorClass<int> in documentIndex
    documentIndex<string, vectorClass<int>> index;
    vectorClass<int> v1;

    v1.push(10);
    v1.push(20);
    v1.push(30);
    v1.push(40);

    vectorClass<int> v2;

    v2.push(10);
    v2.push(50);
    v2.push(60);

    index.insert("document1", v1);
    index.insert("document2", v2);

    index.print();

    index.removeValue(10);
    cout << "After removing value 10:" << endl;
    index.print();

    return 0;

}
