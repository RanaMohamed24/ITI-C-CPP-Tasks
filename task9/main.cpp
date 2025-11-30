#include "string.h"
#include <iostream>
using namespace std;

int main()
{
   
    String s = "ali";
    s += "helo";
    cout << s << endl;

 
    String s1 = "Hello";
    String s2 = " World!";
    String s3 = s1 + s2;
    cout << s3 << endl;

 
    String a = "hello";
    String b = "hello";
    cout << (a == b ? "Equal" : "Not equal") << endl;
    cout << (a == s2 ? "Equal" : "Not equal") << endl;

 
    String name = "Hello";
    name[0] = 'h';
    cout << name << endl;

  
    String msg = "C++";
    msg.append(" rocks!");
    cout << msg << endl;

    
    String copy = s;
    cout << copy << endl;

    return 0;
}
