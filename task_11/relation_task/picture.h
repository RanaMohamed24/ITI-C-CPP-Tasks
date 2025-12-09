#ifndef PICTURE_H
#define PICTURE_H

#include <iostream>
#include "./shape.h"

class Picture {
private:
    int shapeNum;
    Shape** pShapes;
    
public:
    Picture();
    ~Picture();
    
    void setShapes(int sn, Shape** sArr);
    void draw(SDL_Renderer* renderer);
    void print();
};

#endif