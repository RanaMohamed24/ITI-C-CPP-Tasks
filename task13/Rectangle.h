#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GeoShape.h"

class Rectangle : public GeoShape {
public:
    Rectangle(float w = 0, float h = 0) : GeoShape(w, h) {}

    float calculateArea() override {
        return dim1 * dim2;
    }
};

#endif
