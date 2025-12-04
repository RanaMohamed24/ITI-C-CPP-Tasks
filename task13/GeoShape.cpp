

class GeoShape {
protected:
    float dim1, dim2;

public:
    GeoShape(float d1 = 0, float d2 = 0) : dim1(d1), dim2(d2) {}

    void setDim1(float d) { dim1 = d; }
    void setDim2(float d) { dim2 = d; }

    float getDim1() const { return dim1; }
    float getDim2() const { return dim2; }

    virtual float calculateArea() = 0;
};
