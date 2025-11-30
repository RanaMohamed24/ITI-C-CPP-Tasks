#ifndef FLOATTYPE_H
#define FLOATTYPE_H

#include "basetype.h"

class floatType : public basetype
{
public:
    float value;

    floatType(float v) : value(v) {}

    void print() override
    {
        cout << value;
    }

    basetype *clone() override
    {
        return new floatType(value);
    }
};

#endif
