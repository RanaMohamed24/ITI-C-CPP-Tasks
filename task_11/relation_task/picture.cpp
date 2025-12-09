#include "picture.h";
using namespace std;

Picture::Picture() {
    shapeNum = 0;
    pShapes = nullptr;
}

Picture::~Picture() {
   
}

void Picture::setShapes(int sn, Shape** sArr) {
    shapeNum = sn;
    pShapes = sArr;
}

void Picture::draw(SDL_Renderer* renderer) {
    for(int i = 0; i < shapeNum; i++) {
        pShapes[i]->draw(renderer);
    }
}

void Picture::print() {
    cout << "\nShapes (" << shapeNum << "):" << endl;
    for(int i = 0; i < shapeNum; i++) {
        cout << "  ";
        pShapes[i]->print();
    }
}