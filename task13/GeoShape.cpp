#include "GeoShape.h"

GeoShape::GeoShape(float d1, float d2) : dim1(d1), dim2(d2) {}

GeoShape::~GeoShape() {}

void GeoShape::setDim1(float d) {
    dim1 = d;
}

void GeoShape::setDim2(float d) {
    dim2 = d;
}

float GeoShape::getDim1() const {
    return dim1;
}

float GeoShape::getDim2() const {
    return dim2;
}
