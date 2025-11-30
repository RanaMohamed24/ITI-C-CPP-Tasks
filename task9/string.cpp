#include "string.h"



int String::calcLength(const char *str) const
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void String::copyData(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void String::concatData(char *dest, const char *src)
{
   
    int i = 0;
    while (dest[i] != '\0')
        i++;
    
   
    int j = 0;
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

int String::compareData(const char *s1, const char *s2) const
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}



void String::resize(int new_capacity)
{
    if (new_capacity <= capacity) return;

    while (capacity < new_capacity) capacity *= 2;

    char *new_data = new char[capacity];
    if (data) {
        copyData(new_data, data); // Manual copy
        delete[] data;
    }
    data = new_data;
}

String::String() : length(0), capacity(16)
{
    data = new char[capacity];
    data[0] = '\0';
}

String::String(const char *str) : length(0), capacity(16)
{
    if (str == nullptr) {
        data = new char[capacity];
        data[0] = '\0';
        return;
    }

    length = calcLength(str); 
    capacity = length + 1 > 16 ? length + 1 : 16;
    data = new char[capacity];
    copyData(data, str); 
}

String::String(const String &other) : length(other.length), capacity(other.capacity)
{
    data = new char[capacity];
    copyData(data, other.data); 
}

String::~String()
{
    delete[] data;
}

String &String::operator=(const char *str)
{
    if (str == nullptr) str = "";
    
    int new_len = calcLength(str);
    if (new_len + 1 > capacity) resize(new_len + 1);

    copyData(data, str);
    length = new_len;
    return *this;
}

String &String::operator=(const String &other)
{
    if (this == &other) return *this;

    if (other.length + 1 > capacity) resize(other.length + 1);

    copyData(data, other.data); 
    length = other.length;
    return *this;
}

String &String::operator+=(const char *str)
{
    if (str == nullptr) return *this;

    int str_len = calcLength(str);
    if (length + str_len + 1 > capacity) resize(length + str_len + 1);

    concatData(data, str); 
    length += str_len;
    return *this;
}

String &String::operator+=(const String &other)
{
    return *this += other.data;
}

String String::operator+(const char *str) const
{
    String result = *this;
    result += str;
    return result;
}

String String::operator+(const String &other) const
{
    String result = *this;
    result += other;
    return result;
}

bool String::operator==(const String &other) const
{
    return compareData(data, other.data) == 0; 
}

bool String::operator!=(const String &other) const
{
    return !(*this == other);
}

char &String::operator[](int index)
{
    return data[index];
}

const char &String::operator[](int index) const
{
    return data[index];
}

void String::append(const String &other)
{
    *this += other;
}

void String::append(const char *str)
{
    *this += str;
}

int String::getLength() const
{
    return length;
}

int String::getCapacity() const
{
    return capacity;
}

const char *String::c_str() const
{
    return data;
}

bool String::isEmpty() const
{
    return length == 0;
}

void String::clear()
{
    length = 0;
    data[0] = '\0';
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    os << str.data;
    return os;
}
