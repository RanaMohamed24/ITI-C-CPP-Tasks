#ifndef LIST_H
#define LIST_H

#include "../BaseType/basetype.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class List;

class Item
{
private:
    List *list;
    int index;

public:
    Item(List *l, int idx);

    Item &operator=(int v);
    Item &operator=(float v);
    Item &operator=(double v);
    Item &operator=(char v);
    Item &operator=(const char *v);
    Item &operator=(string v);
    Item &operator=(basetype *v);

    operator basetype *() const;
};

class List : public basetype
{
private:
    vector<unique_ptr<basetype>> data;

public:
    List(int capacity = 8); 
    ~List();

    void add(basetype *obj);
    void add(int v);
    void add(float v);
    void add(double v);
    void add(char v);
    void add(const char *v);
    void add(string v);

    void set(int idx, basetype *obj);
    void set(int idx, int v);
    void set(int idx, float v);
    void set(int idx, double v);
    void set(int idx, char v);
    void set(int idx, const char *v);
    void set(int idx, string v);

    basetype *get(int idx);
    Item operator[](int idx);
    int getSize();

    void print() override;
    basetype *clone() override;
};

#endif
