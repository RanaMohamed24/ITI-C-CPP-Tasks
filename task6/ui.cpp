#include "ui.h"
#include <iostream>
#include <string>

using namespace std;

int linuxColorMap[] = {30, 31, 32, 33, 34, 35, 36, 37};

void setColor(Color color)
{
    cout << "\033[" << linuxColorMap[(int)color] << "m";
}

void clearScreen()
{
    system("clear");
}

void moveCursor(int row, int col)
{
    cout << "\033[" << row << ";" << col << "H";
}

void drawButton(int row, int col, const string &text, bool selected)
{
    int width = (int)text.length() + 6;
    Color frameColor = selected ? GREEN : WHITE;

    setColor(frameColor);

    moveCursor(row, col);
    cout << "+" << string(width - 2, '-') << "+";

    moveCursor(row + 1, col);
    cout << "|  " << text << "  |";

    moveCursor(row + 2, col);
    cout << "+" << string(width - 2, '-') << "+";

    setColor(WHITE);
}

void drawButtons(int selected)
{
    int startRow = 10;
    int col = 40;

    drawButton(startRow, col, "NEW", selected == 0);
    drawButton(startRow + 4, col, "DISPLAY", selected == 1);
    drawButton(startRow + 8, col, "EXIT", selected == 2);
}

void printColoredMessage(const string& message, int row, int col, Color color)
{
    moveCursor(row, col);
    setColor(color);
    cout << message;
    setColor(WHITE);
}

void printError(const string& message, int row, int col)
{
    printColoredMessage(message, row, col, RED);
}

void printHeader(const string& title, int row, int col)
{
    printColoredMessage(title, row, col, CYAN);
}

void waitForKey(const string& message, int row, int col)
{
    moveCursor(row, col);
    cout << message;
    cout.flush();
    
    // Forward declaration - we need getChar from keyboard module
    extern char getChar();
    getChar();
}
