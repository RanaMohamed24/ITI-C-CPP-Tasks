#include "list.h"
#include "../BaseType/intType.h"
#include "../BaseType/floatType.h"
#include "../BaseType/doubleType.h"
#include "../BaseType/charType.h"
#include "../BaseType/stringType.h"


List::List(int capacity)
{
    data.reserve(capacity);
}

List::~List()
{
    
}


void List::add(basetype *obj)
{
    
    data.push_back(unique_ptr<basetype>(obj->clone()));
}
void List::add(int v) { data.push_back(unique_ptr<basetype>(new intType(v))); }
void List::add(float v) { data.push_back(unique_ptr<basetype>(new floatType(v))); }
void List::add(double v) { data.push_back(unique_ptr<basetype>(new doubleType(v))); }
void List::add(char v) { data.push_back(unique_ptr<basetype>(new charType(v))); }
void List::add(string v) { data.push_back(unique_ptr<basetype>(new stringType(v))); }
void List::add(const char *v) { data.push_back(unique_ptr<basetype>(new stringType(string(v)))); }

basetype *List::get(int idx)
{
    if (idx < 0 || idx >= data.size())
        return nullptr;
    return data[idx].get();
}

int List::getSize() { return data.size(); }

void List::print()
{
    cout << "[ ";
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i]->print();
        if (i != data.size() - 1)
            cout << ", ";
    }
    cout << " ]";
}

basetype *List::clone()
{
    List *newList = new List(data.capacity());
    for (const auto &item : data)
    {
        newList->add(item.get());
    }
    return newList;
}
