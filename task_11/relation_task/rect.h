#ifndef RECT_H
#define RECT_H

#include "./point.h"
#include <SDL2/SDL.h>

class Rect {
private:
    Point ul; // upper left
    Point lr; // lower right
    
public:
    Rect();
    Rect(int x1, int y1, int x2, int y2);
    Rect(Point p1, Point p2);
    ~Rect();
    
    void draw(SDL_Renderer* renderer);
    void print();
};

#endif