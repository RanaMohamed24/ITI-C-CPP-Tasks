#include "header.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

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


bool isValidName(const string &name)
{
    if (name.empty())
        return false;
    
  
    bool hasLetters = false;
    for (size_t i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
            return false;
        if (isalpha(name[i]))
            hasLetters = true;
    }
    
    return hasLetters; 
}


bool isValidSalary(const string &salaryStr, double &salary)
{
    if (salaryStr.empty())
        return false;
    
   
    bool hasDigits = false;
    for (size_t i = 0; i < salaryStr.length(); i++)
    {
        if (!isspace(salaryStr[i]))
            hasDigits = true;
    }
    if (!hasDigits)
        return false;
    
    try
    {
        salary = stod(salaryStr);
        return salary > 0;
    }
    catch (...)
    {
        return false;
    }
}


string getValidatedInput(const string &prompt, bool isName)
{
    string input;
    bool validInput = false;
    
    while (!validInput)
    {
        cout << prompt;
        getline(cin, input);
        
      
        if (input.empty())
        {
            return "";
        }
        
        if (isName)
        {
            if (isValidName(input))
            {
                validInput = true;
            }
            else
            {
                setColor(RED);
                cout << "  ✗ Invalid input! Please enter letters only (not just spaces).\n";
                setColor(WHITE);
            }
        }
        else
        {
            validInput = true;
        }
    }
    
    return input;
}

void addEmployee(Employee employees[], int *count)
{
    clearScreen();
    setColor(CYAN);
    cout << "\n\n  ╔═══════════════════════════════════╗\n";
    cout << "  ║     ADD NEW EMPLOYEE               ║\n";
    cout << "  ╚═══════════════════════════════════╝\n\n";
    setColor(YELLOW);
    cout << "  (Press ENTER on empty input to return to menu)\n\n";
    setColor(WHITE);

    if (*count >= 100)
    {
        setColor(RED);
        cout << "\n  Error: Maximum number of employees reached (100)!\n";
        setColor(WHITE);
        cout << "\n  Press any key to continue...";
        getInput();
        return;
    }

    Employee *emp = &employees[*count];
    emp->id = *count + 1;
    
    cout << "  Employee ID: " << emp->id << " \n\n";

    // Get First Name with validation
    string firstName = getValidatedInput("  Enter First Name: ", true);
    if (firstName.empty())
    {
        setColor(YELLOW);
        cout << "\n  Cancelled. Returning to menu...\n";
        setColor(WHITE);
        delay(1);
        return;
    }
    strncpy(emp->firstName, firstName.c_str(), 49);
    emp->firstName[49] = '\0';

    // Get Last Name with validation
    string lastName = getValidatedInput("  Enter Last Name: ", true);
    if (lastName.empty())
    {
        setColor(YELLOW);
        cout << "\n  Cancelled. Returning to menu...\n";
        setColor(WHITE);
        delay(1);
        return;
    }
    strncpy(emp->lastName, lastName.c_str(), 49);
    emp->lastName[49] = '\0';

    // Get Position with validation
    string position = getValidatedInput("  Enter Position: ", true);
    if (position.empty())
    {
        setColor(YELLOW);
        cout << "\n  Cancelled. Returning to menu...\n";
        setColor(WHITE);
        delay(1);
        return;
    }
    strncpy(emp->position, position.c_str(), 49);
    emp->position[49] = '\0';

    // Get Salary with validation
    string salaryStr;
    bool validSalary = false;
    
    while (!validSalary)
    {
        cout << "  Enter Salary: ";
        getline(cin, salaryStr);
        
        if (salaryStr.empty())
        {
            setColor(YELLOW);
            cout << "\n  Cancelled. Returning to menu...\n";
            setColor(WHITE);
            delay(1);
            return;
        }
        
        if (isValidSalary(salaryStr, emp->salary))
        {
            validSalary = true;
        }
        else
        {
            setColor(RED);
            cout << "  ✗ Invalid salary! Please enter a positive number.\n";
            setColor(WHITE);
        }
    }

    (*count)++;

    setColor(GREEN);
    cout << "\n  ✓ Employee added successfully!\n";
    setColor(WHITE);
    cout << "\n  Press any key to continue...";
    
    getInput();
}

void displayEmployees(Employee employees[], int count)
{
    clearScreen();
    
    if (count == 0)
    {
        setColor(YELLOW);
        cout << "\n\n  ╔═══════════════════════════════════╗\n";
        cout << "  ║     NO EMPLOYEES FOUND             ║\n";
        cout << "  ╚═══════════════════════════════════╝\n\n";
        setColor(WHITE);
        cout << "  Press any key to return...";
        getInput();
        return;
    }

    setColor(CYAN);
    cout << "\n\n  ╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║                           EMPLOYEES LIST                                      ║\n";
    cout << "  ╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
    setColor(WHITE);

    cout << "  ┌────┬─────────────┬─────────────┬──────────────────────┬─────────────┐\n";
    cout << "  │ ID │ First Name  │ Last Name   │ Position             │ Salary      │\n";
    cout << "  ├────┼─────────────┼─────────────┼──────────────────────┼─────────────┤\n";

    for (int i = 0; i < count; i++)
    {
        cout << "  │ " << setw(2) << right << employees[i].id << " │ "
             << setw(11) << left << employees[i].firstName << " │ "
             << setw(11) << left << employees[i].lastName << " │ "
             << setw(20) << left << employees[i].position << " │ "
             << setw(11) << right << fixed << setprecision(2) << employees[i].salary << " │\n";
    }

    cout << "  └────┴─────────────┴─────────────┴──────────────────────┴─────────────┘\n";

    setColor(GREEN);
    cout << "\n  Total Employees: " << count << "\n";
    setColor(WHITE);
    cout << "\n  Press any key to return...";
    
    getInput();
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

    return KeyNone;
}

int getInput()
{
    return readKey();
}
#endif