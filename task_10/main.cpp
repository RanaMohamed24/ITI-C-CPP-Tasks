#include "List/list.h"
#include "List/ListUtils.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    List l;

    cout << "Enter all elements in a single line, separated by spaces: ";
    string line;
    getline(cin, line);

    ListUtils::addFromString(l, line);

    l.print();
    cout << endl;

    List nested;
    nested.add(99);
    nested.add("hello");
    nested.add(1.618);

    l.add(&nested);

    l.print();
    cout << endl;

    cout << "Modifying elements using operator[]:" << endl;
    l[1] = 10;
    l[2] = "Modified";
    l.print();
    cout << endl;

    List l2;
    l2[0]=2;
    l2[2]="gap";
    cout << "list l2: ";
    l2.print();
    cout << endl;


    return 0;
}
