#ifndef LISTUTILS_H
#define LISTUTILS_H

#include "list.h"
#include <string>
#include <sstream>
using namespace std;

namespace ListUtils
{
    inline bool isInt(const string &s)
    {
        try
        {
            size_t pos;
            stoi(s, &pos);
            return pos == s.size();
        }
        catch (...)
        {
            return false;
        }
    }

    inline bool isFloat(const string &s)
    {
        try
        {
            size_t pos;
            stof(s, &pos);
            return pos == s.size();
        }
        catch (...)
        {
            return false;
        }
    }

    inline bool isDouble(const string &s)
    {
        try
        {
            size_t pos;
            stod(s, &pos);
            return pos == s.size();
        }
        catch (...)
        {
            return false;
        }
    }

    inline void addFromString(List &l, const string &line)
    {
        stringstream ss(line);
        string token;

        while (ss >> token)
        {
            if (isInt(token))
                l.add(stoi(token));
            else if (isFloat(token))
                l.add(stof(token));
            else if (isDouble(token))
                l.add(stod(token));
            else if (token.size() == 1)
                l.add(token[0]);
            else
                l.add(token);
        }
    }
}

#endif
