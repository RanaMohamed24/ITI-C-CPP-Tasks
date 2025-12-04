#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GeoShape.h"

class Rectangle : public GeoShape {
public:
    Rectangle(float w = 0, float h = 0);

    float calculateArea() override;
};

#endif
