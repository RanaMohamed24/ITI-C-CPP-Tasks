#ifndef RECT_H
#define RECT_H

#include "./point.h"
#include "./shape.h"
#include <SDL2/SDL.h>

class Rect : public Shape {
private:
    Point ul; 
    Point lr; 
    
public:
    Rect();
    Rect(int x1, int y1, int x2, int y2);
    Rect(Point p1, Point p2);
    ~Rect();
    
    void draw(SDL_Renderer* renderer) override;
    void print() override;
};

#endif