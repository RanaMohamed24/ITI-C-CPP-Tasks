#ifndef PICTURE_H
#define PICTURE_H

#include "./circle.h"
#include "./rect.h"
#include "./line.h"

class Picture {
private:
    int cNum;
    int rNum;
    int lNum;
    Circle* pC;
    Rect* pR;
    Line* pL;
    
public:
    Picture();
    ~Picture();
    
    void setCircles(int cn, Circle* cArr);
    void setRects(int rn, Rect* rArr);
    void setLines(int ln, Line* lArr);
    void draw(SDL_Renderer* renderer);
    void print();
};

#endif