#include "header.h"

#include <fcntl.h>

#include <stdio.h>

#if defined(_WIN32)
#include <windows.h>
#include <io.h>
#endif

int main()
{

#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int n;
    string input;

    cout << "Enter odd number n: ";
     getline(cin, input);

     bool isValid = true;
    for (int i = 0; i < input.length(); i++)
    {
        if (!isdigit(input[i]))
        {
            isValid = false;
            break;
        }
    }

    if (!isValid || input.empty())
    {
        cout << "Invalid input! Please enter a number only.\n";
        return 0;
    }

    n = stoi(input);

    if (n % 2 == 0 || n < 1)
    {
        cout << "n must be an odd positive number.\n";
        return 0;
    }

    clearScreen();

    int maxNum = n * n;
    int CELL = 2;
    int temp = maxNum;
    while (temp > 0)
    {
        CELL++;
        temp /= 10;
    }

    drawTableFrame(n, CELL);

    int row = 1;
    int col = n / 2 + 1;

    for (int k = 1; k <= n * n; k++)
    {
        printNumberInCell(row, col, CELL, k);

        delay(1);

        if ((k) % n != 0)
        {

            row--;
            if (row < 1)
                row = n;

            col++;
            if (col > n)
                col = 1;
        }
        else
        {

            row++;
            if (row > n)
                row = 1;
        }
    }

    moveCursor(2 + n * 2 + 3, 1);
    cout << "\nMagic Square Completed!\n";

    return 0;
}