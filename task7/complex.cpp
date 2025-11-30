#include "Complex.h"
#include <cmath>
#include <stdexcept>
#include <sstream> // Added for string conversion

using namespace std;

Complex::Complex() : real(0), imag(0)
{
}

Complex::Complex(double r, double i) : real(r), imag(i)
{
}

Complex::Complex(const Complex &other) : real(other.real), imag(other.imag)
{
}

Complex::~Complex()
{
}

Complex Complex::operator+(const Complex &other) const
{
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator+(double num) const
{
    return Complex(real + num, imag);
}

Complex Complex::operator-(const Complex &other) const
{
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator-(double num) const
{
    return Complex(real - num, imag);
}

Complex Complex::operator*(const Complex &other) const
{
    double newReal = (real * other.real) - (imag * other.imag);
    double newImag = (real * other.imag) + (imag * other.real);
    return Complex(newReal, newImag);
}

Complex Complex::operator*(double num) const
{
    return Complex(real * num, imag * num);
}

Complex Complex::operator/(const Complex &other) const
{
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0)
    {
        throw runtime_error("Division by zero!");
    }
    double newReal = (real * other.real + imag * other.imag) / denominator;
    double newImag = (imag * other.real - real * other.imag) / denominator;
    return Complex(newReal, newImag);
}

Complex Complex::operator/(double num) const
{
    if (num == 0)
    {
        throw runtime_error("Division by zero!");
    }
    return Complex(real / num, imag / num);
}

Complex &Complex::operator+=(const Complex &other)
{
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex &Complex::operator-=(const Complex &other)
{
    real -= other.real;
    imag -= other.imag;
    return *this;
}

Complex &Complex::operator*=(const Complex &other)
{
    double newReal = (real * other.real) - (imag * other.imag);
    double newImag = (real * other.imag) + (imag * other.real);
    real = newReal;
    imag = newImag;
    return *this;
}

Complex &Complex::operator/=(const Complex &other)
{
    *this = *this / other;
    return *this;
}

Complex &Complex::operator=(const Complex &other)
{
    if (this == &other)
        return *this;
    real = other.real;
    imag = other.imag;
    return *this;
}

Complex Complex::operator-() const
{
    return Complex(-real, -imag);
}

Complex Complex::operator+() const
{
    return *this;
}

Complex &Complex::operator++()
{
    ++real;
    return *this;
}

Complex Complex::operator++(int)
{
    Complex temp = *this;
    ++real;
    return temp;
}

Complex &Complex::operator--()
{
    --real;
    return *this;
}

Complex Complex::operator--(int)
{
    Complex temp = *this;
    --real;
    return temp;
}

bool Complex::operator==(const Complex &other) const
{
    return (real == other.real) && (imag == other.imag);
}

bool Complex::operator!=(const Complex &other) const
{
    return !(*this == other);
}

bool Complex::operator<(const Complex &other) const
{
    return getMagnitude() < other.getMagnitude();
}

bool Complex::operator>(const Complex &other) const
{
    return getMagnitude() > other.getMagnitude();
}

bool Complex::operator<=(const Complex &other) const
{
    return getMagnitude() <= other.getMagnitude();
}

bool Complex::operator>=(const Complex &other) const
{
    return getMagnitude() >= other.getMagnitude();
}

bool Complex::operator!() const
{
    return (real == 0 && imag == 0);
}

// Fixed: Simplified logic
bool Complex::operator&&(const Complex &other) const
{
    return (*this && other) ? true : false;
}

// Fixed: Simplified logic
bool Complex::operator||(const Complex &other) const
{
    return (*this || other) ? true : false;
}

double Complex::getMagnitude() const
{
    return sqrt(real * real + imag * imag);
}

void Complex::display() const
{
    cout << real;
    if (imag >= 0)
        cout << " + " << imag << "i";
    else
        cout << " - " << abs(imag) << "i";
    cout << endl;
}

double Complex::getReal() const
{
    return real;
}

double Complex::getImag() const
{
    return imag;
}

void Complex::setReal(double r)
{
    real = r;
}

void Complex::setImag(double i)
{
    imag = i;
}

Complex operator+(double num, const Complex &c)
{
    return c + num; // Reuse existing operator
}

Complex operator-(double num, const Complex &c)
{
    return Complex(num - c.real, -c.imag);
}

Complex operator*(double num, const Complex &c)
{
    return c * num; // Reuse existing operator
}

Complex operator/(double num, const Complex &c)
{
    double denominator = c.real * c.real + c.imag * c.imag;
    if (denominator == 0)
    {
        throw runtime_error("Division by zero!");
    }
    return Complex((num * c.real) / denominator, (-num * c.imag) / denominator);
}

ostream &operator<<(ostream &os, const Complex &c)
{
    os << c.real;
    if (c.imag >= 0)
        os << " + " << c.imag << "i";
    else
        os << " - " << abs(c.imag) << "i";
    return os;
}

istream &operator>>(istream &is, Complex &c)
{
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}