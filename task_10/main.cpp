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

    return 0;
}
