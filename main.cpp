#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;


void add_reference_to_hash(unordered_map<string, vector<int>> &map, string key, int value) {
    if (map.find(key) == map.end()) {
        map[key] = {value};
    } else {
        map[key].push_back(value);
    }

}

int main() {
    unordered_map<string, vector<int>> map;

    // Insert key-value pairs into the unordered_map
    map["Apple"] = {10, 20, 30};
    map["Mango"] = {20, 30, 40};
//    map["Cherry"] = {30, 40, 50};

    // Print the key-value pairs
    for (auto &pair : map) {
        cout << pair.first << ": ";
        for (int value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }

    // add another value to cherry

    add_reference_to_hash(map, "Cherry", 50);
    add_reference_to_hash(map, "Pear", 70);

    for (auto &pair : map) {
        cout << pair.first << ": ";
        for (int value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }

}
