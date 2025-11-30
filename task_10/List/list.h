#ifndef LIST_H
#define LIST_H

#include "../BaseType/basetype.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

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

    basetype *get(int idx);
    int getSize();

    void print() override;
    basetype *clone() override;
};

#endif
