#include "stack.h"
#include <iostream>
using namespace std;

int main() {

    Stack s1(5);
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

    Stack s2 = s1;
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

    Stack s3(3);
    s3.push(1);
    s3.push(2);
    cout << "s3 before ";
    s3.print();
    
    s3 = s1;
    cout << "s3 after assignment from s1: ";
    s3.print();
    cout << endl;

    Stack s4(3);
    cout << "Is s4 empty? " << (s4.isEmpty() ? "Yes" : "No") << endl;
    s4.push(5);
    cout << "After pushing 5, is s4 empty? " << (s4.isEmpty() ? "Yes" : "No") << endl;
    cout << endl;

    while (!s1.isEmpty()) {
        cout << "Popped: " << s1.pop() << endl;
        
    }
    s1.print();
    s1.pop();
   cout << endl;

    Stack s5(5);
    cout << s5.getCapacity() << endl;
    Stack s6(0);
    cout << s6.getCapacity() << endl;
    Stack s7;
    cout << s7.size() <<"  "<<s7.getCapacity() << endl;

    return 0;
}