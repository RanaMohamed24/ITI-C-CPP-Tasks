#include "rect.h"
using namespace std;

Rect::Rect() : ul(), lr() {
    cout << "Rect Default Constructor" << endl;
}

Rect::Rect(int x1, int y1, int x2, int y2) : ul(x1, y1), lr(x2, y2) {
    cout << "Rect Parameterized Constructor" << endl;
}

Rect::Rect(Point p1, Point p2) : ul(p1), lr(p2) {
    cout << "Rect Constructor with Points" << endl;
}

Rect::~Rect() {
    
}

void Rect::draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = ul.getX();
    rect.y = ul.getY();
    rect.w = lr.getX() - ul.getX();
    rect.h = lr.getY() - ul.getY();
    SDL_RenderDrawRect(renderer, &rect);
}

void Rect::print() {
    cout << "Rectangle from ";
    ul.print();
    cout << " to ";
    lr.print();
    cout << endl;
}