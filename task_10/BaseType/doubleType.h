#ifndef DOUBLETYPE_H
#define DOUBLETYPE_H

#include "basetype.h"

class doubleType : public basetype
{
public:
    double value;

    doubleType(double v) : value(v) {}

    void print() override
    {
        cout << value;
    }

    basetype *clone() override
    {
        return new doubleType(value);
    }
};

#endif
