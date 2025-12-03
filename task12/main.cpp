#include "stack.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
 
    Stack<int> s1(5);
    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.push(40);
    s1.push(50);
    s1.print();
    cout << endl;

    cout << "Is stack full? " << (s1.isFull() ? "Yes" : "No") << endl;
    if (!s1.push(60)) {
        cout << "Stack Overflow! Cannot push 60" << endl;
    }
    cout << endl;

    if (!s1.isEmpty()) {
        cout << "Popped: " << s1.pop() << endl;
    }
    if (!s1.isEmpty()) {
        cout << "Popped: " << s1.pop() << endl;
    }
    s1.print();
    cout << endl;

    Stack<int> s2 = s1;
    cout << "s1: ";
    s1.print();
    cout << "Copied s2: ";
    s2.print();
    
    s2.push(100);
    cout << "s1: ";
    s1.print();
    cout << "s2: ";
    s2.print();
    cout << endl;

    
    
    Stack<double> doubleStack(5);
    doubleStack.push(3.14);
    doubleStack.push(2.718);
    doubleStack.push(1.414);
    doubleStack.print();
    cout << "Top element: " << doubleStack.top() << endl;
    cout << endl;


    Stack<string> stringStack(5);
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("C++");
    stringStack.push("Templates");
    stringStack.print();
    cout << "Popped: " << stringStack.pop() << endl;
    stringStack.print();
    cout << endl;

    
    Stack<char> charStack(5);
    charStack.push('A');
    charStack.push('B');
    charStack.push('C');
    charStack.print();
    cout << "Size: " << charStack.size() << endl;
    cout << "Capacity: " << charStack.getCapacity() << endl;

    return 0;
}