#include "list.h"
#include "../BaseType/intType.h"
#include "../BaseType/floatType.h"
#include "../BaseType/doubleType.h"
#include "../BaseType/charType.h"
#include "../BaseType/stringType.h"


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
List::List(int cap) : capacity(cap), size(0)
{
    data = new basetype*[capacity];
    for (int i = 0; i < capacity; i++)
    {
        data[i] = nullptr;
    }
}

List::~List()
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] != nullptr)
        {
            delete data[i];
        }
    }
    delete[] data;
}

List::List(const List& other) : capacity(other.capacity), size(other.size)
{
    data = new basetype*[capacity];
    for (int i = 0; i < capacity; i++)
    {
        if (i < size && other.data[i] != nullptr)
        {
            data[i] = other.data[i]->clone();
        }
        else
        {
            data[i] = nullptr;
        }
    }
}

List& List::operator=(const List& other)
{
    if (this != &other)
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] != nullptr)
            {
                delete data[i];
            }
        }
        delete[] data;
        
        capacity = other.capacity;
        size = other.size;
        data = new basetype*[capacity];
        
        for (int i = 0; i < capacity; i++)
        {
            if (i < size && other.data[i] != nullptr)
            {
                data[i] = other.data[i]->clone();
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    return *this;
}
void List::add(basetype *obj)
{
    if (size >= capacity)
    {
        int newCapacity = capacity * 2;
        basetype **newData = new basetype*[newCapacity];
        
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        for (int i = size; i < newCapacity; i++)
        {
            newData[i] = nullptr;
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
    data[size] = obj->clone();
    size++;
}

void List::add(int v) 
{ 
    intType *it = new intType(v);
    add(it);
    delete it;
}

void List::add(float v) 
{ 
    floatType *ft = new floatType(v);
    add(ft);
    delete ft;
}

void List::add(double v) 
{ 
    doubleType *dt = new doubleType(v);
    add(dt);
    delete dt;
}

void List::add(char v) 
{ 
    charType *ct = new charType(v);
    add(ct);
    delete ct;
}

void List::add(string v) 
{ 
    stringType *st = new stringType(v);
    add(st);
    delete st;
}

void List::add(const char *v) 
{ 
    stringType *st = new stringType(string(v));
    add(st);
    delete st;
}


void List::set(int idx, basetype *obj)
{
    if (idx >= capacity)
    {
        int newCapacity = (idx + 1) * 2;
        basetype **newData = new basetype*[newCapacity];
        
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        for (int i = size; i < newCapacity; i++)
        {
            newData[i] = nullptr;
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
    if (data[idx] != nullptr)
    {
        delete data[idx];
    }
    
    data[idx] = obj->clone();
    
    if (idx >= size)
    {
        size = idx + 1;
    }
}

void List::set(int idx, int v)
{
    intType *it = new intType(v);
    set(idx, it);
    delete it;
}

void List::set(int idx, float v)
{
    floatType *ft = new floatType(v);
    set(idx, ft);
    delete ft;
}

void List::set(int idx, double v)
{
    doubleType *dt = new doubleType(v);
    set(idx, dt);
    delete dt;
}

void List::set(int idx, char v)
{
    charType *ct = new charType(v);
    set(idx, ct);
    delete ct;
}

void List::set(int idx, const char *v)
{
    stringType *st = new stringType(string(v));
    set(idx, st);
    delete st;
}

void List::set(int idx, string v)
{
    stringType *st = new stringType(v);
    set(idx, st);
    delete st;
}

basetype *List::get(int idx)
{
    if (idx < 0 || idx >= size)
        return nullptr;
    return data[idx];
}

Item List::operator[](int idx)
{
    return Item(this, idx);
}

int List::getSize() { return size; }

void List::print()
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        if (data[i] != nullptr)
            data[i]->print();
        else
            cout << "null";
            
        if (i != size - 1)
            cout << ", ";
    }
    cout << " ]";
}

basetype *List::clone()
{
    List *newList = new List(capacity);
    for (int i = 0; i < size; i++)
    {
        if (data[i] != nullptr)
        {
            newList->add(data[i]);
        }
    }
    return newList;
}
