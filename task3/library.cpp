#include "header.h"
#include <iomanip>

#if defined(_WIN32)
#include <windows.h>

WORD windowsColorMap[] = {
    0,
    FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};
#else
#include <unistd.h>

int linuxColorMap[] = {
    30,  // BLACK
    31,  // RED
    32,  // GREEN
    33,  // YELLOW
    34,  // BLUE
    35,  // MAGENTA
    36,  // CYAN
    37   // WHITE
};
#endif



void delay(int number)
{
#if defined(_WIN32)
    Sleep(number * 1000);
#else
    sleep(number);
#endif
}



void moveCursor(int row, int col)
{
#if defined(_WIN32)
    COORD coord;
    coord.X = col - 1;
    coord.Y = row - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    cout << "\033[" << row << ";" << col << "H";
#endif
}



void clearScreen()
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}



void setColor(Color color)
{
#if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attr = windowsColorMap[(int)color];
    SetConsoleTextAttribute(hConsole, attr);
#else
    int ansi = linuxColorMap[(int)color];
    cout << "\033[" << ansi << "m";
#endif
}



void repeat(const string& s, int times)
{
    for (int i = 0; i < times; i++)
        cout << s;
}



void drawTableFrame(int n, int CELL)
{
    setColor(WHITE); 
    
  
    moveCursor(1, 1);
    cout << "┌";
    for (int i = 1; i <= n - 1; i++)
    {
        repeat("─", CELL);
        cout << "┬";
    }
    repeat("─", CELL);
    cout << "┐";

    for (int r = 0; r < n; r++)
    {
     
        moveCursor(2 + r * 2, 1);
        cout << "│";
        for (int c = 0; c < n; c++)
        {
            repeat(" ", CELL);
            cout << "│";
        }

       
        if (r != n - 1)
        {
            moveCursor(3 + r * 2, 1);
            cout << "├";
            for (int i = 1; i <= n - 1; i++)
            {
                repeat("─", CELL);
                cout << "┼";
            }
            repeat("─", CELL);
            cout << "┤";
        }
    }

    
    int bottomRow = 2 + (n - 1) * 2 + 1;  
    moveCursor(bottomRow, 1);
    cout << "└";
    for (int i = 1; i <= n - 1; i++)
    {
        repeat("─", CELL);
        cout << "┴";
    }
    repeat("─", CELL);
    cout << "┘";
    
    setColor(WHITE);  
}



void printNumberInCell(int row, int col, int CELL, int num)
{
    int screenRow = 2 + (row - 1) * 2;
    
    
    int numWidth = 0;
    int temp = num;
    if (num == 0) numWidth = 1;
    else {
        while (temp > 0) {
            numWidth++;
            temp /= 10;
        }
    }
    
   
    int padding = (CELL - numWidth) / 2;
    int screenCol = 1 + (col - 1) * (CELL + 1) + 1 + padding;

    moveCursor(screenRow, screenCol);
    
    
    Color colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
    setColor(colors[num % 7]);
    
    cout << num << flush;
    
   
    setColor(WHITE);
}