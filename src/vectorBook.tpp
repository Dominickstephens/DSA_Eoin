#include <iostream>
#include <stdexcept>  
#include <functional>
#include "../include/vectorBook.h"

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
void vectorClass<T>::push(T item) {
    if (current == capacity) {
        T* temp = new T[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    arr[current] = item;
    current++;
}

template <typename T>
void vectorClass<T>::push(const vectorClass<T>& other) {
    for (int i = 0; i < other.current; i++) {
        if (current == capacity) {
            T* temp = new T[2 * capacity];
            for (int j = 0; j < capacity; j++) {
                temp[j] = arr[j];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = other.arr[i];
        current++;
    }
}

template <typename T>
void vectorClass<T>::remove(const T& value) {
    int newSize = 0; // new size after removal
    for (int i = 0; i < current; i++) {
        if (arr[i] != value) {
            arr[newSize++] = arr[i];  // keep the value if it is not equal to the one being removed
        }
    }
    current = newSize;  // update current size
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
void vectorClass<T>::print() const {
    for (int i = 0; i < current; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// erase by index
template <typename T>
void vectorClass<T>::erase(int index) {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of range");
    }

    // shift elements to the left to fill the gap
    for (int i = index; i < current - 1; i++) {
        arr[i] = arr[i + 1];
    }
    current--;
}

// erase by value
template <typename T>
void vectorClass<T>::erase(const T& value) {
    for (int i = 0; i < current; i++) {
        if (arr[i] == value) {
            erase(i); 
            return;
        }
    }
    throw std::runtime_error("Value not found");
}

template <typename T>
bool vectorClass<T>::empty() const {
    return current == 0; // returns true if the current size is 0
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

// copy constructor
template <typename T>
vectorClass<T>::vectorClass(const vectorClass<T>& other) {
    capacity = other.capacity;
    current = other.current;
    arr = new T[capacity];
    for (int i = 0; i < current; i++) {
        arr[i] = other.arr[i];
    }
}

// qssignment operator
template <typename T>
vectorClass<T>& vectorClass<T>::operator=(const vectorClass<T>& other) {
    if (this == &other) return *this; // handle self-assignment

    delete[] arr; // clean up existing memory

    capacity = other.capacity;
    current = other.current;
    arr = new T[capacity]; // qllocate new memory
    for (int i = 0; i < current; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

template <typename T>
void vectorClass<T>::erase_if(std::function<bool(const T&)> predicate) {
    int newSize = 0; // new size after removal
    for (int i = 0; i < current; i++) {
        if (!predicate(arr[i])) {
            arr[newSize++] = arr[i];  // keep the value if it does not satisfy the predicate
        }
    }
    current = newSize;  // update current size
}