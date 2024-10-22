#include "../include/Set.h"

template <typename T>
void Set<T>::insert(const T& value) {
    if (!contains(value)) {
        elements.push_back(value);
    }
}

template <typename T>
bool Set<T>::contains(const T& value) const {
    return std::find(elements.begin(), elements.end(), value) != elements.end();
}

template <typename T>
void Set<T>::erase(const T& value) {
    auto it = std::find(elements.begin(), elements.end(), value);
    if (it != elements.end()) {
        elements.erase(it);
    }
}

template <typename T>
std::vector<T> Set<T>::toVector() const {
    return elements;
}

template <typename T>
Set<T> Set<T>::setIntersection(const Set<T>& other) const {
    Set<T> result;
    for (const auto& elem : elements) {
        if (other.contains(elem)) {
            result.insert(elem);
        }
    }
    return result;
}

template <typename T>
Set<T> Set<T>::setUnion(const Set<T>& other) const {
    Set<T> result = *this;
    for (const auto& elem : other.elements) {
        result.insert(elem);
    }
    return result;
}

template <typename T>
Set<T> Set<T>::setDifference(const Set<T>& other) const {
   Set<T> result;
    for (const auto& elem : elements) {
        if (!other.contains(elem)) {
            result.insert(elem);
        }
    }
    return result;
}