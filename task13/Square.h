#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(float side = 0);

    void setSide(float s);
    float getSide() const;

    float calculateArea() override;
};

#endif
