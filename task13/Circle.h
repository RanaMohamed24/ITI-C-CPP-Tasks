#ifndef CIRCLE_H
#define CIRCLE_H

#include "GeoShape.h"

class Circle : public GeoShape {
public:
    Circle(float r = 0);

    void setRadius(float r);
    float getRadius() const;

    float calculateArea() override;
};

#endif
