#include "Rectangle.h"

Rectangle::Rectangle(float w, float h) : GeoShape(w, h) {}

float Rectangle::calculateArea() {
    return dim1 * dim2;
}
