#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>
#include <cmath>

class Complex
{
private:
    double real;
    double imag;

public:
    Complex();
    Complex(double r, double i = 0);
    Complex(const Complex &other);
    ~Complex();

    Complex operator+(const Complex &other) const;
    Complex operator+(double num) const;

    Complex operator-(const Complex &other) const;
    Complex operator-(double num) const;

    Complex operator*(const Complex &other) const;
    Complex operator*(double num) const;

    Complex operator/(const Complex &other) const;
    Complex operator/(double num) const;

    friend Complex operator+(double num, const Complex &c);
    friend Complex operator-(double num, const Complex &c);
    friend Complex operator*(double num, const Complex &c);
    friend Complex operator/(double num, const Complex &c);

    Complex &operator+=(const Complex &other);
    Complex &operator-=(const Complex &other);
    Complex &operator*=(const Complex &other);
    Complex &operator/=(const Complex &other);

    Complex &operator=(const Complex &other);

    Complex operator-() const;
   

    Complex &operator++();
    Complex operator++(int);

    Complex &operator--();
    Complex operator--(int);

    bool operator==(const Complex &other) const;
    bool operator!=(const Complex &other) const;
    bool operator<(const Complex &other) const;
    bool operator>(const Complex &other) const;
    bool operator<=(const Complex &other) const;
    bool operator>=(const Complex &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Complex &c);
    friend std::istream &operator>>(std::istream &is, Complex &c);

    double getMagnitude() const;

    void display() const;

    double getReal() const;
    double getImag() const;

    void setReal(double r);
    void setImag(double i);
};

#endif