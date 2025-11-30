#ifndef STRINGTYPE_H
#define STRINGTYPE_H

#include "basetype.h"

class stringType : public basetype
{
public:
    string value;

    stringType(const string &v) : value(v) {}

    void print() override
    {
        cout << value;
    }

    basetype *clone() override
    {
        return new stringType(value);
    }
};

#endif
