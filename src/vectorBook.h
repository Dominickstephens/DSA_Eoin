#ifndef VECTORCLASS_H
#define VECTORCLASS_H

#include <iostream>

template <typename T>
class vectorClass {
public:
    // Define value_type
    using value_type = T;
    using size_type = size_t;

    vectorClass();

    vectorClass(const vectorClass<T> &other);
    vectorClass<T>& operator=(const vectorClass<T>& other); // Assignment operators

    ~vectorClass();
    void push(T data);
    void push(T data, size_type index);
    void erase(size_type index);  // Declare erase by index
    void erase(const T& value);  // Declare erase by value
    T get(size_type index);
    void pop();
    int size() const;
    int getcapacity();
    void print() const;
    void remove(const T& value);  // Add declaration for remove method

    T* begin() { return data; }
    T* end() { return data + current; }

    const T* begin() const { return data; }
    const T* end() const { return data + current; }

    bool empty() const; // Declaration of empty method

    T& operator[](int index);               // Non-const version
    const T& operator[](int index) const;   // Const version

    void push(const vectorClass<T> &other);

private:
    T* arr;
    T* data;
    int capacity;
    int current;

};

#include "vectorBook.tpp"  // Include your implementation file

#endif // VECTORCLASS_H
