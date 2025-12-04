#include "Circle.h"

Circle::Circle(float r) : GeoShape(r, 0) {}

void Circle::setRadius(float r) {
    dim1 = r;
}

float Circle::getRadius() const {
    return dim1;
}

float Circle::calculateArea() {
    return 3.14159f * dim1 * dim1;
}
