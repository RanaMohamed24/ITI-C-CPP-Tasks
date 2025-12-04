
#include "GeoShape.cpp";
class Circle : private GeoShape {
public:
    Circle(float r = 0) : GeoShape(r, 0) {}

    void setRadius(float r) { dim1 = r; }
    float getRadius() const { return dim1; }

    float calculateArea() {
        return 3.14f * dim1 * dim1;
    }
};
