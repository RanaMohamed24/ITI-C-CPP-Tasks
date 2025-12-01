#include "picture.h"

Picture::Picture() {
    cNum = rNum = lNum = 0;
    pC = NULL;
    pR = NULL;
    pL = NULL;
    cout << "Picture Constructor" << endl;
}

Picture::~Picture() {
    cout << "Picture Destructor" << endl;
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
    cout << "\n========== Picture Contents ==========" << endl;
    
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
    
    cout << "======================================\n" << endl;
}