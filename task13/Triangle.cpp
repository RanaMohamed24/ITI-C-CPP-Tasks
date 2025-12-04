
#include "GeoShape.cpp";
class Triangle : public GeoShape {
public:
    Triangle(float b = 0, float h = 0) : GeoShape(b, h) {}

    float calculateArea() override {
        return 0.5 * dim1 * dim2;
    }
};
