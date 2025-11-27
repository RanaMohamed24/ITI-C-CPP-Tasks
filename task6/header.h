#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <sys/select.h>


const int MAX_BUFFER_SIZE = 10000;
const int MIN_BUFFER_SIZE = 1;
const int MIN_PRINTABLE_CHAR = 32;
const int MAX_PRINTABLE_CHAR = 126;
const int EDITOR_START_ROW = 3;
const int EDITOR_START_COL = 1;


enum Color
{
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};


enum Key
{
    KeyNone = 0,
    KeyUp,
    KeyDown,
    KeyLeft,
    KeyRight,
    KeyEnter,
    KeyBackspace,
    KeyEsc,
    KeyDelete,
    KeyChar
};



struct TextEditor
{
    char* buffer;
    int maxSize;
    int currentLength;
    int cursorRow;
    int cursorCol;
    int scrollOffset;
};


void initTextEditor(TextEditor* editor, int size);
void cleanupTextEditor(TextEditor* editor);
bool insertChar(TextEditor* editor, char ch);
bool deleteChar(TextEditor* editor);
bool backspace(TextEditor* editor);
void moveCursorLeft(TextEditor* editor);
void moveCursorRight(TextEditor* editor);
void moveCursorUp(TextEditor* editor);
void moveCursorDown(TextEditor* editor);
int getAbsoluteCursorPos(const TextEditor* editor);
void redrawEditor(TextEditor* editor);
void moveToEndOfPreviousLine(TextEditor* editor);

void setColor(Color color);
void clearScreen();
void moveCursor(int row, int col);



void drawButton(int row, int col, const std::string &text, bool selected);
void drawButtons(int selected);

int getInput();
char getChar();


std::string readString(const std::string& prompt, int row, int col);
int readNumber(const std::string& prompt, int row, int col, int minVal, int maxVal);


void newScreen(TextEditor& editor);
void displayScreen();
void exitScreen(TextEditor& editor);
void saveToFile(TextEditor& editor);

#endif



