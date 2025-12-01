#include "point.h"

Point::Point() {
    x = 0;
    y = 0;
    cout << "Point Default Constructor" << endl;
}

Point::Point(int _x, int _y) {
    x = _x;
    y = _y;
    cout << "Point Parameterized Constructor (" << x << ", " << y << ")" << endl;
}

Point::~Point() {
    cout << "Point Destructor (" << x << ", " << y << ")" << endl;
}

int Point::getX() { return x; }
int Point::getY() { return y; }

void Point::setX(int _x) { x = _x; }
void Point::setY(int _y) { y = _y; }

void Point::print() {
    cout << "(" << x << ", " << y << ")";
}