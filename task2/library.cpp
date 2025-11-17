
#include "header.h"
#include <cstdlib>
#include <iostream>

using namespace std;

#if defined(_WIN32)
WORD windowsColorMap[] = {
    0,
    FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};
#endif

int linuxColorMap[] = {30, 31, 32, 33, 34, 35, 36, 37};

void setColor(Color color)
{
#if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attr = windowsColorMap[(int)color];
    SetConsoleTextAttribute(hConsole, attr);
#else
    cout << "\033[" << linuxColorMap[(int)color] << "m";
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

void printColoredText(const string &text, Color color, int row, int col)
{
    moveCursor(row, col);
    setColor(color);
    cout << text;
#if defined(_WIN32)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    cout << "\033[0m";
#endif
}

void delay(int number)
{
#if defined(_WIN32)
    Sleep(number * 1000);
#else
    sleep(number);
#endif
}

void openScreen(const string &title)
{
    while (true)
    {
        clearScreen();
        moveCursor(5, 5);
        cout << ">>> " << title << " SCREEN <<<\n\n";
        cout << "Press BACKSPACE to return\n";
        cout << "Press ESC to exit program\n";

        int key = getInput();
        if (key == KeyBackspace)
            return;
        if (key == KeyEsc)
        {
            clearScreen();
            exit(0);
        }
    }
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

#if defined(_WIN32)

int getInput()
{
    int ch = _getch();
    if (ch == 0 || ch == 224)
    {
        int arrow = _getch();
        switch (arrow)
        {
        case 72:
            return KeyUp;
        case 80:
            return KeyDown;
        case 75:
            return KeyLeft;
        case 77:
            return KeyRight;
        default:
            return KeyNone;
        }
    }

    if (ch == 13)
        return KeyEnter;
    if (ch == 27)
        return KeyEsc;
    if (ch == 8 || ch == 127)
        return KeyBackspace;

    return KeyNone;
}

#else

static void enableRaw()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static void disableRaw()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static Key readKey()
{
    enableRaw();
    int c = getchar();     
    disableRaw();

    if (c == EOF)
        return KeyNone;


    if (c == 27)
    {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);

        timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 30000;

        int r = select(STDIN_FILENO + 1, &rfds, nullptr, nullptr, &tv);

        if (r == 1)
        {
            enableRaw();
            int b1 = getchar();
            disableRaw();

            if (b1 == '[')
            {
                enableRaw();
                int b2 = getchar();
                disableRaw();

                switch (b2)
                {
                case 'A': return KeyUp;
                case 'B': return KeyDown;
                case 'C': return KeyRight;
                case 'D': return KeyLeft;
                default:  return KeyNone;
                }
            }
            return KeyNone;
        }
        else
        {
            return KeyEsc; 
        }
    }

   
    if (c == '\n' || c == '\r')
        return KeyEnter;

    
    if (c == 127 || c == 8)
        return KeyBackspace;

    return KeyNone;
}

int getInput()
{
    return readKey();
}

#endif

