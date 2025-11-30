#include "List.h"
#include "../BaseType/intType.h"
#include "../BaseType/floatType.h"
#include "../BaseType/doubleType.h"
#include "../BaseType/charType.h"
#include "../BaseType/stringType.h"

// constructor/destructor
List::List(int capacity) : cap(capacity), size(0)
{
    data = new basetype *[cap];
}

List::~List()
{
    for (int i = 0; i < size; i++)
        delete data[i];
    delete[] data;
}

void List::expand()
{
    cap *= 2;
    basetype **newArr = new basetype *[cap];
    for (int i = 0; i < size; i++)
        newArr[i] = data[i];
    delete[] data;
    data = newArr;
}

// add methods
void List::add(basetype *obj)
{
    if (size == cap)
        expand();
    data[size++] = obj->clone();
}
void List::add(int v) { add(new intType(v)); }
void List::add(float v) { add(new floatType(v)); }
void List::add(double v) { add(new doubleType(v)); }
void List::add(char v) { add(new charType(v)); }
void List::add(string v) { add(new stringType(v)); }
void List::add(const char *v) { add(new stringType(string(v))); }

basetype *List::get(int idx)
{
    if (idx < 0 || idx >= size)
        return nullptr;
    return data[idx];
}

int List::getSize() { return size; }

void List::print()
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        data[i]->print();
        if (i != size - 1)
            cout << ", ";
    }
    cout << " ]";
}

basetype *List::clone()
{
    List *newList = new List(cap);
    for (int i = 0; i < size; i++)
        newList->add(data[i]);
    return newList;
}
