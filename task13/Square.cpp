#include "Square.h"

Square::Square(float side) : Rectangle(side, side) {}

void Square::setSide(float s) {
    setDim1(s);
    setDim2(s);
}

float Square::getSide() const {
    return getDim1();
}

float Square::calculateArea() {
    return getSide() * getSide();
}
