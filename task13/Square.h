#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(float side = 0) : Rectangle(side, side) {}

    void setSide(float s) {
        setDim1(s);
        setDim2(s);
    }

    float getSide() const {
        return getDim1();
    }

    float calculateArea() override {
        return getSide() * getSide();
    }
};

#endif
