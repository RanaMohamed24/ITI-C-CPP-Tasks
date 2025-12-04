#include <iostream>
using namespace std;
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"

int main() {
    Triangle t(10, 5);
    Rectangle r(4, 6);
    Square s(5);
    Circle c(3);

    cout << "Triangle Area = " << t.calculateArea() << endl;
    cout << "Rectangle Area = " << r.calculateArea() << endl;
    cout << "Square Area = " << s.calculateArea() << endl;
    cout << "Circle Area = " << c.calculateArea() << endl;

    return 0;
}
