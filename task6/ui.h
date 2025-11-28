#ifndef UI_H
#define UI_H

#include "types.h"
#include <string>

void setColor(Color color);
void clearScreen();
void moveCursor(int row, int col);

void drawButton(int row, int col, const std::string &text, bool selected);
void drawButtons(int selected);

void printColoredMessage(const std::string& message, int row, int col, Color color);
void printError(const std::string& message, int row, int col);
void printHeader(const std::string& title, int row, int col);
void waitForKey(const std::string& message, int row, int col);

#endif
