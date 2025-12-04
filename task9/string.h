#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <stdexcept>

class String
{
private:
    char *data;
    size_t length;
    size_t capacity;

    void resize(size_t new_capacity);
    
    size_t calcLength(const char *str) const;
    void copyData(char *dest, const char *src) const;
    void concatData(char *dest, const char *src) const;
    int compareData(const char *s1, const char *s2) const;

public:
  
    String();
    String(const char *str);
    String(const String &other);
    String(String &&other) noexcept;            
    ~String() noexcept;

    
    String &operator=(const String &other);
    String &operator=(String &&other) noexcept;  

  
    String &operator+=(const char *str);
    String &operator+=(const String &other);
    
 
    String operator+(const char *str) const;
    String operator+(const String &other) const;

  
    bool operator==(const String &other) const noexcept;
    bool operator!=(const String &other) const noexcept;

  
    char &operator[](size_t index);
    const char &operator[](size_t index) const;

   
    void append(const String &other) { *this += other; }
    void append(const char *str) { *this += str; }
    
 
    size_t getLength() const noexcept { return length; }
    size_t getCapacity() const noexcept { return capacity; }
   
    
   
    bool isEmpty() const noexcept { return length == 0; }
    void clear() noexcept;

   
    friend std::ostream &operator<<(std::ostream &os, const String &str);
};

#endif