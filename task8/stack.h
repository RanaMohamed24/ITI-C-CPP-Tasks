#ifndef STACK_H
#define STACK_H

class Stack {
private:
    int* arr;
    int topIndex;
    int capacity;

public:
    Stack(int size = 10);
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack();
    
    bool push(int value);
    int pop();
    int& top();
    const int& top() const;
    bool isEmpty() const;
    bool isFull() const;
    void print() const;
    int size() const;
    int getCapacity() const;
};

#endif