//
// Created by Dominick on 21/10/2024.
//

#ifndef DSA_PROJECT_PAIRIMP_H
#define DSA_PROJECT_PAIRIMP_H

#include <ostream>

#ifndef PAIR_H
#define PAIR_H

using namespace std;

template <typename KeyType, typename ValueType>
class Pair {
public:
    KeyType first;   // Key
    ValueType second; // Value

    // Constructor
    Pair(const KeyType& key, const ValueType& value) : first(key), second(value) {}

    // Default constructor
    Pair() = default;

    // Equality operator for comparing pairs
    bool operator==(const Pair<KeyType, ValueType>& other) const {
        return first == other.first && second == other.second;
    }

    // Output stream operator for printing
    friend std::ostream& operator<<(std::ostream& os, const Pair<KeyType, ValueType>& pair) {
        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }
};

#endif


#endif //DSA_PROJECT_PAIRIMP_H
