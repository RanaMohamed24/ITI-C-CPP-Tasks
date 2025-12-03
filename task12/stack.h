#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    T* arr;
    int topIndex;
    int capacity;

public:
    Stack(int size = 10);
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);
    ~Stack();
    
    bool push(const T& value);
    T pop();
    T top();
    bool isEmpty() const;
    bool isFull() const;
    void print() const;
    int size() const;
    int getCapacity() const;
};

template <typename T>
Stack<T>::Stack(int size) {
    if (size <= 0) {
        capacity = 10;
    } else {
        capacity = size;
    }
    arr = new T[capacity];
    topIndex = -1;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
    capacity = other.capacity;
    topIndex = other.topIndex;
    arr = new T[capacity];
    
    for (int i = 0; i <= topIndex; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this == &other) {
        return *this;
    }

    delete[] arr;

    capacity = other.capacity;
    topIndex = other.topIndex;
    arr = new T[capacity];
    
    for (int i = 0; i <= topIndex; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template <typename T>
bool Stack<T>::push(const T& value) {
    if (isFull()) {
        return false;
    }
    arr[++topIndex] = value;
    return true;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        cout << "Cannot pop from empty stack." << endl;
        return T(); 
    }
    T value = arr[topIndex];
    topIndex--;
    return value;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return topIndex == -1;
}

template <typename T>
bool Stack<T>::isFull() const {
    return topIndex == capacity - 1;
}

template <typename T>
void Stack<T>::print() const {
    if (isEmpty()) {
        cout << "Stack is empty!" << endl;
        return;
    }
    
    cout << "Stack elements : ";
    for (int i = topIndex; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
int Stack<T>::size() const {
    return topIndex + 1;
}

template <typename T>
T Stack<T>::top() {
    if (isEmpty()) {
        cout << "Stack is empty!" << endl;
        return T(); 
    }
    return arr[topIndex];
}

template <typename T>
int Stack<T>::getCapacity() const {
    return capacity;
}

#endif