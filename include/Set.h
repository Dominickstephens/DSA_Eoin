#ifndef SET_H
#define SET_H

#include <vector>
#include <algorithm>

template <typename T>
class Set {
public:
    Set() = default;

    void insert(const T& value);
    bool contains(const T& value) const;
    void erase(const T& value);
    std::vector<T> toVector() const;

    Set<T> setIntersection(const Set<T>& other) const;
    Set<T> setUnion(const Set<T>& other) const;
    Set<T> setDifference(const Set<T>& other) const;

private:
    std::vector<T> elements;
};

#include "../src/Set.tpp"

#endif 