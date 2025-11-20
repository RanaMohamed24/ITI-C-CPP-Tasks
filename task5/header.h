#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

#if defined(_WIN32)
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <sys/select.h>
#endif

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
    KeyEsc
};


struct Employee
{
    int id;
    char firstName[50];
    char lastName[50];
    char position[50];
    double salary;
};

typedef struct Employee Employee;

void setColor(Color color);
void clearScreen();
void moveCursor(int row, int col);
void printColoredText(const std::string &text, Color color, int row, int col);
void delay(int seconds);

void drawButton(int row, int col, const std::string &text, bool selected);
void drawButtons(int selected);

int getInput();
void openScreen(const std::string &title);

// Employee functions
void addEmployee(Employee employees[], int *count);
void displayEmployees(Employee employees[], int count);

#endif