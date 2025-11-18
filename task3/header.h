#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;
enum Color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
};

void delay(int number);
void moveCursor(int row, int col);
void clearScreen();
void setColor(Color color);

void repeat(const string& s, int times);
void drawTableFrame(int n, int CELL);
void printNumberInCell(int row, int col, int CELL, int num);

#endif