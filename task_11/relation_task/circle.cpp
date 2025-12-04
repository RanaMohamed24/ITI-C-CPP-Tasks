#include "circle.h"
using namespace std;

Circle::Circle() : cen(), r(0) {
    
}

Circle::Circle(int x, int y, int _r) : cen(x, y), r(_r) {
   
}

Circle::Circle(Point p, int _r) : cen(p), r(_r) {
  
}

Circle::~Circle() {
   
}
void Circle::drawCirclePoints(SDL_Renderer* renderer, int xc, int yc, int x, int y) {
    SDL_RenderDrawPoint(renderer, xc + x, yc + y);
    SDL_RenderDrawPoint(renderer, xc - x, yc + y);
    SDL_RenderDrawPoint(renderer, xc + x, yc - y);
    SDL_RenderDrawPoint(renderer, xc - x, yc - y);
    SDL_RenderDrawPoint(renderer, xc + y, yc + x);
    SDL_RenderDrawPoint(renderer, xc - y, yc + x);
    SDL_RenderDrawPoint(renderer, xc + y, yc - x);
    SDL_RenderDrawPoint(renderer, xc - y, yc - x);
}

void Circle::draw(SDL_Renderer* renderer) {

    int x = 0;
    int y = r;
    int d = 1 - r;
    
    while (x <= y) {
        drawCirclePoints(renderer, cen.getX(), cen.getY(), x, y);
        
        if (d < 0) {
            d = d + 2 * x + 3;
        } else {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void Circle::print() {
    cout << "Circle at ";
    cen.print();
    cout << " with radius " << r << endl;
}
