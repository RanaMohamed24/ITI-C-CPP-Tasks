#include "line.h"
using namespace std;

Line::Line() : start(), end() {
   
}

Line::Line(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2) {
   
}

Line::Line(Point p1, Point p2) : start(p1), end(p2) {
    
}

Line::~Line() {
    cout << "Line Destructor" << endl;
}

void Line::draw(SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, start.getX(), start.getY(), end.getX(), end.getY());
}

void Line::print() {
    cout << "Line from ";
    start.print();
    cout << " to ";
    end.print();
    cout << endl;
}