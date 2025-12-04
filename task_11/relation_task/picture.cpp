#include "picture.h"
using namespace std;

Picture::Picture() {
    cNum = rNum = lNum = 0;
    pC = nullptr;
    pR = nullptr;
    pL = nullptr;
   
}

Picture::~Picture() {
   
}

void Picture::setCircles(int cn, Circle* cArr) {
    cNum = cn;
    pC = cArr;
}

void Picture::setRects(int rn, Rect* rArr) {
    rNum = rn;
    pR = rArr;
}

void Picture::setLines(int ln, Line* lArr) {
    lNum = ln;
    pL = lArr;
}

void Picture::draw(SDL_Renderer* renderer) {
    for(int i = 0; i < cNum; i++) {
        pC[i].draw(renderer);
    }
    for(int i = 0; i < rNum; i++) {
        pR[i].draw(renderer);
    }
    
    for(int i = 0; i < lNum; i++) {
        pL[i].draw(renderer);
    }
}

void Picture::print() {
   
    
    cout << "\nCircles (" << cNum << "):" << endl;
    for(int i = 0; i < cNum; i++) {
        cout << "  ";
        pC[i].print();
    }
    
    cout << "\nRectangles (" << rNum << "):" << endl;
    for(int i = 0; i < rNum; i++) {
        cout << "  ";
        pR[i].print();
    }
    
    cout << "\nLines (" << lNum << "):" << endl;
    for(int i = 0; i < lNum; i++) {
        cout << "  ";
        pL[i].print();
    }
    
   
}