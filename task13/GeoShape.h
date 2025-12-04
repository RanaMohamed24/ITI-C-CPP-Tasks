#ifndef GEOSHAPE_H
#define GEOSHAPE_H

class GeoShape {
protected:
    float dim1, dim2;

public:
    GeoShape(float d1 = 0, float d2 = 0);
    virtual ~GeoShape();

    void setDim1(float d);
    void setDim2(float d);

    float getDim1() const;
    float getDim2() const;

    virtual float calculateArea() = 0;
};

#endif
