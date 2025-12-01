#include "string.h"



size_t String::calcLength(const char *str) const
{
    if (!str) return 0;
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void String::copyData(char *dest, const char *src) const
{
    if (!src) {
        dest[0] = '\0';
        return;
    }
    
    while ((*dest++ = *src++));
}

void String::concatData(char *dest, const char *src) const
{
    if (!src) return;
    
   
    while (*dest) dest++;

    copyData(dest, src);
}

int String::compareData(const char *s1, const char *s2) const
{
    size_t i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}

void String::resize(size_t new_capacity)
{
    if (new_capacity <= capacity) return;

    size_t new_cap = capacity;
    while (new_cap < new_capacity) 
        new_cap *= 2;

    char *new_data = new char[new_cap];
    if (data) {
        copyData(new_data, data);
        delete[] data;
    } else {
        new_data[0] = '\0';
    }
    
    data = new_data;
    capacity = new_cap;
}


String::String() : data(nullptr), length(0), capacity(16)
{
    data = new char[capacity];
    data[0] = '\0';
}

String::String(const char *str) : data(nullptr), length(0), capacity(16)
{
    if (str == nullptr) {
        data = new char[capacity];
        data[0] = '\0';
        return;
    }

    length = calcLength(str);
    capacity = (length + 1 > 16) ? (length + 1) : 16;
    data = new char[capacity];
    copyData(data, str);
}

String::String(const String &other) 
    : data(nullptr), length(other.length), capacity(other.capacity)
{
    data = new char[capacity];
    copyData(data, other.data);
}

String::String(String &&other) noexcept
    : data(other.data), length(other.length), capacity(other.capacity)
{
    other.data = nullptr;
    other.length = 0;
    other.capacity = 0;
}

String::~String() noexcept
{
    delete[] data;
}

String &String::operator=(const String &other)
{
    if (this == &other) return *this;

    if (other.length + 1 > capacity) 
        resize(other.length + 1);

    copyData(data, other.data);
    length = other.length;
    return *this;
}

String &String::operator=(String &&other) noexcept
{
    if (this != &other) {
        delete[] data;
        
        data = other.data;
        length = other.length;
        capacity = other.capacity;
        
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
    }
    return *this;
}



String &String::operator+=(const char *str)
{
    if (str == nullptr) return *this;

    size_t str_len = calcLength(str);
    if (length + str_len + 1 > capacity) 
        resize(length + str_len + 1);

    concatData(data, str);
    length += str_len;
    return *this;
}

String &String::operator+=(const String &other)
{
    return *this += other.data;
}



String String::operator+(const String &other) const
{
    String result;
    result.resize(length + other.length + 1);
    result.data[0] = '\0';  
    
    if (data) {
        copyData(result.data, data);
        result.length = length;
    }
    
    if (other.data) {
        concatData(result.data, other.data);
        result.length += other.length;
    }
    
    return result;
}

String String::operator+(const char *str) const
{
    if (!str) return *this;
    return *this + String(str);
}



bool String::operator==(const String &other) const noexcept
{
    return compareData(data, other.data) == 0;
}

bool String::operator!=(const String &other) const noexcept
{
    return !(*this == other);
}



char &String::operator[](size_t index)
{
    if (index >= length)
        throw std::out_of_range("String index out of range");
    return data[index];
}

const char &String::operator[](size_t index) const
{
    if (index >= length)
        throw std::out_of_range("String index out of range");
    return data[index];
}



void String::clear() noexcept
{
    length = 0;
    if (data) data[0] = '\0';
}


std::ostream &operator<<(std::ostream &os, const String &str)
{
    if (str.data)
        os << str.data;
    return os;
}