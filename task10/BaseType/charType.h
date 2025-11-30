#ifndef CHARTYPE_H
#define CHARTYPE_H

#include "basetype.h"

class charType : public basetype
{
public:
    char value;

    charType(char v) : value(v) {}

    void print() override
    {
        cout << value;
    }

    basetype *clone() override
    {
        return new charType(value);
    }
};

#endif
