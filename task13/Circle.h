#ifndef CIRCLE_H
#define CIRCLE_H

#include "GeoShape.h"

class Circle : private GeoShape {
public:
    Circle(float r = 0) : GeoShape(r, 0) {}

    void setRadius(float r) { dim1 = r; }
    float getRadius() const { return dim1; }

    float calculateArea() override {
        return 3.14159f * dim1 * dim1;
    }
};

#endif
