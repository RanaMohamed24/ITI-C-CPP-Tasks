#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeoShape.h"

class Triangle : public GeoShape {
public:
    Triangle(float b = 0, float h = 0) : GeoShape(b, h) {}

    float calculateArea() override {
        return 0.5f * dim1 * dim2;
    }
};

#endif
