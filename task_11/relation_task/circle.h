#ifndef CIRCLE_H
#define CIRCLE_H

#include "./point.h"
#include <SDL2/SDL.h>

class Circle {
private:
    Point cen; // center
    int r;     // radius
    
    void drawCirclePoints(SDL_Renderer* renderer, int xc, int yc, int x, int y);
    
public:
    Circle();
    Circle(int x, int y, int _r);
    Circle(Point p, int _r);
    ~Circle();
    
    void draw(SDL_Renderer* renderer);
    void print();
};

#endif