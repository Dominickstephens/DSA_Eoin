#include <iostream>
#include <stdexcept>  // For std::out_of_range and std::runtime_error
using namespace std;

template <typename T>
vectorClass<T>::vectorClass() {
    arr = new T[1];
    capacity = 1;
    current = 0;
}

template <typename T>
vectorClass<T>::~vectorClass() {
    delete[] arr;
}

template <typename T>
void vectorClass<T>::push(T data) {
    if (current == capacity) {
        T* temp = new T[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    arr[current] = data;
    current++;
}

template <typename T>
void vectorClass<T>::remove(const T& value) {
    int newSize = 0; // New size after removal
    for (int i = 0; i < current; i++) {
        if (arr[i] != value) {
            arr[newSize++] = arr[i];  // Keep the value if it is not equal to the one being removed
        }
    }
    current = newSize;  // Update current size
}


template <typename T>
void vectorClass<T>::push(T data, int index) {
    if (index == capacity)
        push(data);
    else
        arr[index] = data;
}

template <typename T>
T vectorClass<T>::get(int index) {
    if (index < current)
        return arr[index];
    throw std::out_of_range("Index out of range");
}

template <typename T>
void vectorClass<T>::pop() {
    if (current > 0) {
        current--;
    } else {
        throw std::underflow_error("Cannot pop from an empty vector");
    }
}

template <typename T>
int vectorClass<T>::size() const {
    return current;
}

template <typename T>
int vectorClass<T>::getcapacity() {
    return capacity;
}

template <typename T>
void vectorClass<T>::print() {
    for (int i = 0; i < current; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Implementation of erase by index
template <typename T>
void vectorClass<T>::erase(int index) {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of range");
    }

    // Shift elements to the left to fill the gap
    for (int i = index; i < current - 1; i++) {
        arr[i] = arr[i + 1];
    }
    current--;
}

// Implementation of erase by value
template <typename T>
void vectorClass<T>::erase(const T& value) {
    for (int i = 0; i < current; i++) {
        if (arr[i] == value) {
            erase(i);  // Call erase by index
            return;
        }
    }
    throw std::runtime_error("Value not found");
}

template <typename T>
bool vectorClass<T>::empty() const {
    return current == 0; // Returns true if the current size is 0
}

template <typename T>
T& vectorClass<T>::operator[](int index) {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
const T& vectorClass<T>::operator[](int index) const {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}
