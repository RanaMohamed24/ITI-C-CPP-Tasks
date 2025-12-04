#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>


struct Shape {
    virtual ~Shape() = default;  
    
    virtual void draw(SDL_Renderer* renderer) = 0;  
    virtual void print() = 0;                        
};

#endif
