#ifndef VECTORCLASS_H
#define VECTORCLASS_H

#include <iostream>
#include <functional>

template <typename T>
class vectorClass {
public:
    using value_type = T;

    vectorClass();

    vectorClass(const vectorClass<T> &other);
    vectorClass<T>& operator=(const vectorClass<T>& other); 

    ~vectorClass();
    void push(T data);
    void push(T data, int index);
    void erase(int index);  
    void erase(const T& value);  
    T get(int index);
    void pop();
    int size() const;
    int getcapacity();
    void print() const;
    void remove(const T& value);  

    T* begin() { return data; }
    T* end() { return data + current; }

    const T* begin() const { return data; }
    const T* end() const { return data + current; }

    bool empty() const; 

    T& operator[](int index);               
    const T& operator[](int index) const;   

    void erase_if(std::function<bool(const T &)> predicate);

private:
    T* arr;
    T* data;
    int capacity;
    int current;

    void push(const vectorClass<T> &other);

};

#include "../src/vectorBook.tpp" 

#endif 
