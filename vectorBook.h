#ifndef VECTORBOOK_H
#define VECTORBOOK_H

#include <iostream>
using namespace std;

template <typename T>
class vectorClass {
    T* arr;
    int capacity;
    int current;

public:
    vectorClass();
    ~vectorClass();
    void push(T data);
    void push(T data, int index);
    T get(int index);
    void pop();
    int size();
    int getcapacity();
    void print();
};

#include "vectorBook.tpp"  // Include the template implementation

#endif
