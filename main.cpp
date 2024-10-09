#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <filesystem>
#include <fstream>

using namespace std;

template<typename KeyType, typename ValueType>

class documentIndex {
public:
    documentIndex(size_t size = 10) : table(size), numElements(0) {}

    // Insert a key-value pair
    void insert(const KeyType& key, const ValueType& value) {
        if (numElements >= table.size()) {
            rehash();
        }

        size_t index = hashFunction(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Update value if key exists
                return;
            }
        }
        table[index].emplace_back(key, value); // Add new pair if key doesn't exist
        ++numElements;
    }

    // Find a value by key
    ValueType* find(const KeyType& key) {
        size_t index = hashFunction(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    void print() {
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                cout << pair.first << ": ";
                for (const auto& value : pair.second) {
                    cout << value << " ";
                }
                cout << endl;
            }
        }
    }

    void removeValue(const typename ValueType::value_type& value) {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                auto& vec = pair.second;
                vec.erase(remove(vec.begin(), vec.end(), value), vec.end()); // Remove the value from the vector
            }
        }
    }

private:
    vector<list<pair<KeyType, ValueType>>> table; // The hash table (buckets)
    size_t numElements;  // Number of elements in the map
    hash<KeyType> hashFunction;  // Hash function

    // Resize and rehash the table when it becomes too full
    void rehash() {
        size_t newSize = table.size() * 2;
        vector<list<pair<KeyType, ValueType>>> newTable(newSize);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t newIndex = hashFunction(pair.first) % newSize;
                newTable[newIndex].emplace_back(pair);
            }
        }
        table = move(newTable);
    }
};

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

//    print out find
    auto* value = index.find("Fem├¡neo");
    if (value) {
        for (const auto& book : *value) {
            cout << book << " ";
        }
        cout << endl;
    }

//    index.print();


    return 0;
}
