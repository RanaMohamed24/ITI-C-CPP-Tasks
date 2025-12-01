#include "stack.h"
#include <iostream>
using namespace std;

Stack::Stack(int size) {
    if (size <= 0) {
        capacity = 10;
    } else {
        capacity = size;
    }
    arr = new int[capacity];
    topIndex = -1;
}

Stack::Stack(const Stack& other) {
    capacity = other.capacity;
    topIndex = other.topIndex;
    arr = new int[capacity];
    
    for (int i = 0; i <= topIndex; i++) {
        arr[i] = other.arr[i];
    }
}

Stack& Stack::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    delete[] arr;

    capacity = other.capacity;
    topIndex = other.topIndex;
    arr = new int[capacity];
    
    for (int i = 0; i <= topIndex; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

Stack::~Stack() {
    delete[] arr;
}

bool Stack::push(int value) {
    if (isFull()) {
        return false;
    }
    arr[++topIndex] = value;
    return true;
}

int Stack::pop() {
    if (isEmpty()) {
        cout << "Cannot pop from empty stack." << endl;
        return -1;
    }
    int value = arr[topIndex];
    topIndex--;
    return value;
}

bool Stack::isEmpty() const {
    return topIndex == -1;
}

bool Stack::isFull() const {
    return topIndex == capacity - 1;
}

void Stack::print() const {
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

int Stack::size() const {
    return topIndex + 1;
}



int Stack::top() {
    if (isEmpty()) {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    return arr[topIndex];
}

int Stack::getCapacity() const {
    return capacity;
}