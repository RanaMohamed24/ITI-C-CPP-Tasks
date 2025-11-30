#ifndef BASETYPE_H
#define BASETYPE_H

#include <string>
#include <iostream>
using namespace std;

class basetype
{
public:
    virtual void print() = 0;      // لطباعة القيمة
    virtual basetype *clone() = 0; // لعمل نسخة جديدة
    virtual ~basetype() {}
};

#endif
