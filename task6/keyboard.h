#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
#include <string>

int getInput();
char getChar();

std::string readString(const std::string& prompt, int row, int col);
int readNumber(const std::string& prompt, int row, int col, int minVal, int maxVal);

#endif
