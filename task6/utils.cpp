#include "header.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdexcept>

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

char getChar()
{
    enableRaw();
    char c;
    read(STDIN_FILENO, &c, 1);
    disableRaw();
    return c;
}


static bool readRawChar(unsigned char& c)
{
    enableRaw();
    ssize_t n = read(STDIN_FILENO, &c, 1);
    disableRaw();
    return n > 0;
}


static bool hasInputAvailable(int timeoutMicroseconds = 30000)
{
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = timeoutMicroseconds;

    return select(STDIN_FILENO + 1, &rfds, nullptr, nullptr, &tv) == 1;
}


static Key handleEscapeSequence()
{
    unsigned char b1;
    if (!readRawChar(b1) || b1 != '[')
        return KeyNone;

    unsigned char b2;
    if (!readRawChar(b2))
        return KeyNone;

    switch (b2)
    {
        case 'A': return KeyUp;
        case 'B': return KeyDown;
        case 'C': return KeyRight;
        case 'D': return KeyLeft;
        case '3':
            {
                unsigned char b3;
                if (readRawChar(b3) && b3 == '~')
                    return KeyDelete;
                return KeyNone;
            }
        default:
            return KeyNone;
    }
}

static Key readKey()
{
    unsigned char c;
    if (!readRawChar(c))
        return KeyNone;

    
    if (c == 27)
    {
       
        if (hasInputAvailable())
            return handleEscapeSequence();
        else
            return KeyEsc;  
    }


    if (c == '\n' || c == '\r')
        return KeyEnter;

  
    if (c == 127 || c == 8)
        return KeyBackspace;

   
    return (Key)c;
}

int getInput()
{
    return readKey();
}

string readString(const string& prompt, int row, int col)
{
    moveCursor(row, col);
    cout << prompt;
    cout.flush();

    string result = "";
    while (true)
    {
        char ch = getChar();
        if (ch == '\n' || ch == '\r')
            break;
        else if (ch == 27)
        {
            return "\x1B";
        }
        else if (ch == 127 || ch == 8)
        {
            if (!result.empty())
            {
                result.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        }
        else if (ch >= MIN_PRINTABLE_CHAR && ch <= MAX_PRINTABLE_CHAR)
        {
            result += ch;
            cout << ch;
            cout.flush();
        }
    }

    return result;
}

int readNumber(const string& prompt, int row, int col, int minVal, int maxVal)
{
    while (true)
    {
        string input = readString(prompt, row, col);

        if (input == "\x1B")
        {
            return -1;
        }

        if (input.empty())
        {
            moveCursor(row + 2, col);
            setColor(RED);
            cout << "No input entered! Try again...";
            setColor(WHITE);
            sleep(1);
            clearScreen();
            continue;
        }

        try
        {
            int value = stoi(input);
            if (value < minVal || value > maxVal)
            {
                moveCursor(row + 2, col);
                setColor(RED);
                cout << "Value must be between " << minVal << " and " << maxVal << "!";
                setColor(WHITE);
                sleep(1);
                clearScreen();
                continue;
            }
            return value;
        }
        catch (const invalid_argument&)
        {
            moveCursor(row + 2, col);
            setColor(RED);
            cout << "Invalid number! Try again...";
            setColor(WHITE);
            sleep(1);
            clearScreen();
        }
        catch (const out_of_range&)
        {
            moveCursor(row + 2, col);
            setColor(RED);
            cout << "Number too large! Try again...";
            setColor(WHITE);
            sleep(1);
            clearScreen();
        }
    }
}