#ifndef LINE_H
#define LINE_H

#include "./point.h"
#include <SDL2/SDL.h>

class Line {
private:
    Point start;
    Point end;
    
public:
    Line();
    Line(int x1, int y1, int x2, int y2);
    Line(Point p1, Point p2);
    ~Line();
    
    void draw(SDL_Renderer* renderer);
    void print();
};

#endif