#include "header.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#if defined(_WIN32)
#include <windows.h>
#include <conio.h>

WORD windowsColorMap[] = {
    0,
    FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/time.h>
#endif

int linuxColorMap[] = {30, 31, 32, 33, 34, 35, 36, 37};

// Global buffer variables
char* textBuffer = nullptr;
int bufferSize = 0;
int currentLength = 0;

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

char getChar()
{
    return _getch();
}

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
        case 83:
            return KeyDelete;
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

    // Return the character itself for normal keys
    return ch;
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

char getChar()
{
    enableRaw();
    char c;
    read(STDIN_FILENO, &c, 1);
    disableRaw();
    return c;
}

static Key readKey()
{
    enableRaw();

    unsigned char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);

    disableRaw();

    if (n <= 0)
        return KeyNone;

    // ESC
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
            unsigned char b1;

            enableRaw();
            read(STDIN_FILENO, &b1, 1);
            disableRaw();

            if (b1 == '[')
            {
                unsigned char b2;

                enableRaw();
                read(STDIN_FILENO, &b2, 1);
                disableRaw();

                switch (b2)
                {
                case 'A': return KeyUp;
                case 'B': return KeyDown;
                case 'C': return KeyRight;
                case 'D': return KeyLeft;
                case '3':
                    {
                        unsigned char b3;
                        enableRaw();
                        read(STDIN_FILENO, &b3, 1);
                        disableRaw();
                        if (b3 == '~') return KeyDelete;
                    }
                    return KeyNone;
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

    // ENTER
    if (c == '\n' || c == '\r')
        return KeyEnter;

    // Backspace
    if (c == 127 || c == 8)
        return KeyBackspace;

    // Return the character itself
    return (Key)c;
}

int getInput()
{
    return readKey();
}
#endif

// NEW Screen Implementation
void newScreen()
{
    clearScreen();
    moveCursor(3, 5);
    setColor(CYAN);
    cout << "=== NEW TEXT EDITOR ===" << endl;
    setColor(WHITE);
    
    moveCursor(5, 5);
    cout << "Enter buffer size (max characters): ";
    cout.flush();
    
    // Read buffer size manually
    string sizeStr = "";
    while (true)
    {
        char ch = getChar();
        if (ch == '\n' || ch == '\r')
            break;
        else if (ch == 127 || ch == 8)  // Backspace
        {
            if (!sizeStr.empty())
            {
                sizeStr.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        }
        else if (ch >= '0' && ch <= '9')
        {
            sizeStr += ch;
            cout << ch;
            cout.flush();
        }
    }
    
    if (sizeStr.empty())
    {
        moveCursor(7, 5);
        setColor(RED);
        cout << "No size entered! Press any key to return...";
        setColor(WHITE);
        getChar();
        return;
    }
    
    bufferSize = stoi(sizeStr);
    
    if (bufferSize <= 0 || bufferSize > 10000)
    {
        moveCursor(7, 5);
        setColor(RED);
        cout << "Invalid size! Press any key to return...";
        setColor(WHITE);
        getChar();
        return;
    }
    
    // Allocate buffer
    if (textBuffer != nullptr)
        delete[] textBuffer;
    
    textBuffer = new char[bufferSize];
    memset(textBuffer, 0, bufferSize);
    currentLength = 0;
    
    clearScreen();
    moveCursor(1, 1);
    setColor(GREEN);
    cout << "=== EDITING (ESC to save/discard) ===" << endl;
    setColor(YELLOW);
    cout << "Buffer Size: " << bufferSize << " | Length: " << currentLength << endl;
    setColor(WHITE);
    
    int cursorPos = 0;
    int displayRow = 3;
    int displayCol = 1;
    
    moveCursor(displayRow, displayCol);
    
    while (true)
    {
        int key = getInput();
        
        if (key == KeyEsc)
        {
            // Save or Discard menu
            clearScreen();
            moveCursor(5, 30);
            setColor(CYAN);
            cout << "=== SAVE OPTIONS ===" << endl;
            setColor(WHITE);
            
            moveCursor(7, 30);
            cout << "1. Save to file";
            moveCursor(8, 30);
            cout << "2. Discard changes";
            moveCursor(9, 30);
            cout << "3. Continue editing";
            
            moveCursor(11, 30);
            cout << "Choose option: ";
            cout.flush();
            
            char choice;
            while (true)
            {
                choice = getChar();
                if (choice == '1' || choice == '2' || choice == '3')
                    break;
            }
            
            if (choice == '1')
            {
                moveCursor(13, 5);
                cout << "Enter filename: ";
                cout.flush();
                
                // Read filename character by character
                string filename = "";
                while (true)
                {
                    char ch = getChar();
                    if (ch == '\n' || ch == '\r')
                        break;
                    else if (ch == 127 || ch == 8)  // Backspace
                    {
                        if (!filename.empty())
                        {
                            filename.pop_back();
                            cout << "\b \b";
                            cout.flush();
                        }
                    }
                    else if (ch >= 32 && ch <= 126)
                    {
                        filename += ch;
                        cout << ch;
                        cout.flush();
                    }
                }
                
                if (filename.empty())
                {
                    moveCursor(15, 5);
                    setColor(RED);
                    cout << "No filename entered! Press any key...";
                    setColor(WHITE);
                    getChar();
                    return;
                }
                
                // Check if file exists
                ifstream checkFile(filename);
                bool fileExists = checkFile.good();
                checkFile.close();
                
                if (fileExists)
                {
                    moveCursor(15, 5);
                    cout << "File exists! (A)ppend or (O)verwrite? ";
                    cout.flush();
                    char mode;
                    while (true)
                    {
                        mode = getChar();
                        if (mode == 'A' || mode == 'a' || mode == 'O' || mode == 'o')
                        {
                            cout << mode;  // Show what user pressed
                            cout.flush();
                            break;
                        }
                    }
                    
                    moveCursor(16, 5);
                    if (mode == 'A' || mode == 'a')
                    {
                        setColor(YELLOW);
                        cout << "Appending to file...";
                        setColor(WHITE);
                        ofstream file(filename, ios::app | ios::binary);
                        if (file.is_open())
                        {
                            file.write(textBuffer, currentLength);
                            file.close();
                        }
                    }
                    else
                    {
                        setColor(YELLOW);
                        cout << "Overwriting file...";
                        setColor(WHITE);
                        ofstream file(filename, ios::binary);
                        if (file.is_open())
                        {
                            file.write(textBuffer, currentLength);
                            file.close();
                        }
                    }
                }
                else
                {
                    ofstream file(filename, ios::binary);
                    if (file.is_open())
                    {
                        file.write(textBuffer, currentLength);
                        file.close();
                    }
                }
                
                moveCursor(17, 5);
                setColor(GREEN);
                cout << "File saved! Press any key...";
                setColor(WHITE);
                getChar();
                return;
            }
            else if (choice == '2')
            {
                return;
            }
            else
            {
                // Redraw screen
                clearScreen();
                moveCursor(1, 1);
                setColor(GREEN);
                cout << "=== EDITING (ESC to save/discard) ===" << endl;
                setColor(YELLOW);
                cout << "Buffer Size: " << bufferSize << " | Length: " << currentLength << endl;
                setColor(WHITE);
                
                moveCursor(displayRow, displayCol);
                for (int i = 0; i < currentLength; i++)
                    cout << textBuffer[i];
                
                moveCursor(displayRow, displayCol + cursorPos);
            }
        }
        else if (key == KeyLeft)
        {
            if (cursorPos > 0)
            {
                cursorPos--;
                moveCursor(displayRow, displayCol + cursorPos);
            }
        }
        else if (key == KeyRight)
        {
            if (cursorPos < currentLength)
            {
                cursorPos++;
                moveCursor(displayRow, displayCol + cursorPos);
            }
        }
        else if (key == KeyBackspace)
        {
            if (cursorPos > 0)
            {
                // Shift text left
                for (int i = cursorPos - 1; i < currentLength - 1; i++)
                    textBuffer[i] = textBuffer[i + 1];
                
                currentLength--;
                cursorPos--;
                
                // Redraw line
                moveCursor(displayRow, displayCol);
                for (int i = 0; i < currentLength; i++)
                    cout << textBuffer[i];
                cout << " ";
                
                moveCursor(2, 15);
                setColor(YELLOW);
                cout << bufferSize << " | Length: " << currentLength << "   ";
                setColor(WHITE);
                
                moveCursor(displayRow, displayCol + cursorPos);
            }
        }
        else if (key == KeyDelete)
        {
            if (cursorPos < currentLength)
            {
                // Shift text left
                for (int i = cursorPos; i < currentLength - 1; i++)
                    textBuffer[i] = textBuffer[i + 1];
                
                currentLength--;
                
                // Redraw line
                moveCursor(displayRow, displayCol);
                for (int i = 0; i < currentLength; i++)
                    cout << textBuffer[i];
                cout << " ";
                
                moveCursor(2, 15);
                setColor(YELLOW);
                cout << bufferSize << " | Length: " << currentLength << "   ";
                setColor(WHITE);
                
                moveCursor(displayRow, displayCol + cursorPos);
            }
        }
        else if (key >= 32 && key <= 126)  // Normal printable characters
        {
            char ch = (char)key;
            
            if (currentLength < bufferSize)
            {
                // Shift text right
                for (int i = currentLength; i > cursorPos; i--)
                    textBuffer[i] = textBuffer[i - 1];
                
                textBuffer[cursorPos] = ch;
                currentLength++;
                cursorPos++;
                
                // Redraw line
                moveCursor(displayRow, displayCol);
                for (int i = 0; i < currentLength; i++)
                    cout << textBuffer[i];
                
                moveCursor(2, 15);
                setColor(YELLOW);
                cout << bufferSize << " | Length: " << currentLength << "   ";
                setColor(WHITE);
                
                moveCursor(displayRow, displayCol + cursorPos);
            }
        }
        
        cout.flush();
    }
}

// DISPLAY Screen Implementation
void displayScreen()
{
    clearScreen();
    moveCursor(3, 5);
    setColor(CYAN);
    cout << "=== DISPLAY FILE CONTENT ===" << endl;
    setColor(WHITE);
    
    moveCursor(5, 5);
    cout << "Enter filename: ";
    cout.flush();
    
    // Read filename
    string filename = "";
    while (true)
    {
        char ch = getChar();
        if (ch == '\n' || ch == '\r')
            break;
        else if (ch == 127 || ch == 8)  // Backspace
        {
            if (!filename.empty())
            {
                filename.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        }
        else if (ch >= 32 && ch <= 126)
        {
            filename += ch;
            cout << ch;
            cout.flush();
        }
    }
    
    if (filename.empty())
    {
        moveCursor(7, 5);
        setColor(RED);
        cout << "No filename entered!";
        setColor(WHITE);
    }
    else
    {
        ifstream file(filename, ios::binary);
        if (!file.is_open())
        {
            moveCursor(7, 5);
            setColor(RED);
            cout << "Error: File not found!";
            setColor(WHITE);
        }
        else
        {
            // Get file size
            file.seekg(0, ios::end);
            int fileSize = file.tellg();
            file.seekg(0, ios::beg);
            
            moveCursor(7, 5);
            setColor(GREEN);
            cout << "File: " << filename << " (" << fileSize << " characters)" << endl;
            setColor(WHITE);
            moveCursor(9, 5);
            cout << string(70, '-') << endl;
            moveCursor(10, 5);
            
            // Read and display file
            char ch;
            while (file.get(ch))
            {
                cout << ch;
            }
            
            cout << endl;
            moveCursor(12, 5);
            cout << string(70, '-') << endl;
            
            file.close();
        }
    }
    
    moveCursor(14, 5);
    setColor(YELLOW);
    cout << "Press any key to return...";
    setColor(WHITE);
    getChar();
}

// EXIT Screen Implementation
void exitScreen()
{
    clearScreen();
    moveCursor(10, 30);
    setColor(CYAN);
    cout << "=== GOODBYE ===" << endl;
    setColor(WHITE);
    
    moveCursor(12, 25);
    cout << "Thanks for using the editor!";
    
    moveCursor(14, 30);
    cout << "Exiting...";
    
    delay(1);
    
    if (textBuffer != nullptr)
        delete[] textBuffer;
    
    clearScreen();
    exit(0);
}



