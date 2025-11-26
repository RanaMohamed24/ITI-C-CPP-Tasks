#include "header.h"
#include <iostream>
using namespace std;

int main()
{
    int selected = 0;
    const int totalButtons = 3;

    clearScreen();
    drawButtons(selected);
    cout.flush();

    while (true)
    {
        int key = getInput();

        if (key == KeyUp || key == KeyLeft)
        {
            selected = (selected - 1 + totalButtons) % totalButtons;
        }
        else if (key == KeyDown || key == KeyRight)
        {
            selected = (selected + 1) % totalButtons;
        }
        else if (key == KeyEnter)
        {
            if (selected == 0)
                newScreen();
            else if (selected == 1)
                displayScreen();
            else if (selected == 2)
                exitScreen();
        }
        else if (key == KeyEsc)
        {
           if (textBuffer != nullptr)
                delete[] textBuffer;
            clearScreen();
            exit(0);
        }

        
        clearScreen();
        drawButtons(selected);
        cout.flush();
    }

    return 0;
}


