#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeoShape.h"

class Triangle : public GeoShape {
public:
    Triangle(float b = 0, float h = 0);

    float calculateArea() override;
};

#endif
