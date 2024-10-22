#ifndef VECTORCLASS_H
#define VECTORCLASS_H

#include <iostream>

template <typename T>
class vectorClass {
public:
    // Define value_type
    using value_type = T;

    vectorClass();

    vectorClass(const vectorClass<T> &other);
    vectorClass<T>& operator=(const vectorClass<T>& other); // Assignment operators

    ~vectorClass();
    void push(T data);
    void push(T data, int index);
    void erase(int index);  // Declare erase by index
    void erase(const T& value);  // Declare erase by value
    T get(int index);
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

private:
    T* arr;
    T* data;
    int capacity;
    int current;

    void push(const vectorClass<T> &other);
};

#include "../src/vectorBook.tpp"  // Include your implementation file

#endif // VECTORCLASS_H
