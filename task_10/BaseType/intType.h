#ifndef INTTYPE_H
#define INTTYPE_H

#include "basetype.h"

class intType : public basetype
{
public:
    int value;

    intType(int v) : value(v) {}

    void print() override
    {
        cout << value;
    }

    basetype *clone() override
    {
        return new intType(value);
    }
};

#endif
