#include "Rectangle.cpp";
class Square : private Rectangle {
public:
    Square(float side = 0) : Rectangle(side, side) {}

    void setSide(float s) {
        Rectangle::setDim1(s);
        Rectangle::setDim2(s);
    }

    float getSide() const {
        return Rectangle::getDim1();
    }

    float calculateArea() {
        return getSide() * getSide();
    }
};
