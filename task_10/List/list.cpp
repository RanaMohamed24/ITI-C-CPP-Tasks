#include "list.h"
#include "../BaseType/intType.h"
#include "../BaseType/floatType.h"
#include "../BaseType/doubleType.h"
#include "../BaseType/charType.h"
#include "../BaseType/stringType.h"

// Item implementation
Item::Item(List *l, int idx) : list(l), index(idx) {}

Item &Item::operator=(int v)
{
    list->set(index, v);
    return *this;
}

Item &Item::operator=(float v)
{
    list->set(index, v);
    return *this;
}

Item &Item::operator=(double v)
{
    list->set(index, v);
    return *this;
}

Item &Item::operator=(char v)
{
    list->set(index, v);
    return *this;
}

Item &Item::operator=(const char *v)
{
    list->set(index, v);
    return *this;
}

Item &Item::operator=(string v)
{
    list->set(index, v);
    return *this;
}

Item &Item::operator=(basetype *v)
{
    list->set(index, v);
    return *this;
}

Item::operator basetype *() const
{
    return list->get(index);
}
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


void List::set(int idx, basetype *obj)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(obj->clone());
}
void List::set(int idx, int v)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(new intType(v));
}
void List::set(int idx, float v)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(new floatType(v));
}
void List::set(int idx, double v)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(new doubleType(v));
}
void List::set(int idx, char v)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(new charType(v));
}
void List::set(int idx, const char *v)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(new stringType(string(v)));
}
void List::set(int idx, string v)
{
    if (idx >= data.size())
        data.resize(idx + 1);
    data[idx] = unique_ptr<basetype>(new stringType(v));
}

basetype *List::get(int idx)
{
    if (idx < 0 || idx >= data.size())
        return nullptr;
    return data[idx].get();
}

Item List::operator[](int idx)
{
    return Item(this, idx);
}

int List::getSize() { return data.size(); }

void List::print()
{
    cout << "[ ";
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i])
            data[i]->print();
        else
            cout << "null";
            
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
