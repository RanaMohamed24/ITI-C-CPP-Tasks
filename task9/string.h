#ifndef STRING_H
#define STRING_H

#include <iostream>

class String
{
private:
    char *data;
    int length;
    int capacity;

    void resize(int new_capacity);
    
 
    int calcLength(const char *str) const;
    void copyData(char *dest, const char *src);
    void concatData(char *dest, const char *src);
    int compareData(const char *s1, const char *s2) const;

public:
    String();
    String(const char *str);
    String(const String &other);
    ~String();

    String &operator=(const char *str);
    String &operator=(const String &other);

    String &operator+=(const char *str);
    String &operator+=(const String &other);
    
    String operator+(const char *str) const;
    String operator+(const String &other) const;

    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;

    char &operator[](int index);
    const char &operator[](int index) const;

    void append(const String &other);
    void append(const char *str);
    
    int getLength() const;
    int getCapacity() const;
    const char *c_str() const;
    
    bool isEmpty() const;
    void clear();

    friend std::ostream &operator<<(std::ostream &os, const String &str);
};

#endif
