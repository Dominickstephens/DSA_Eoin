#ifndef DSA_PROJECT_PAIRIMP_H
#define DSA_PROJECT_PAIRIMP_H

#include <ostream>

#ifndef PAIR_H
#define PAIR_H

using namespace std;

template <typename KeyType, typename ValueType>
class Pair
{
public:
    KeyType first;
    ValueType second;

    Pair(const KeyType &key, const ValueType &value) : first(key), second(value) {}

    Pair() = default;

    // Equality operator for comparing pairs
    bool operator==(const Pair<KeyType, ValueType> &other) const
    {
        return first == other.first && second == other.second;
    }

    friend std::ostream &operator<<(std::ostream &os, const Pair<KeyType, ValueType> &pair)
    {
        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }
};

#endif

#endif
