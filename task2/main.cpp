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
                openScreen("NEW");
            else if (selected == 1)
                openScreen("DISPLAY");
            else if (selected == 2)
                openScreen("EXIT");
        }
        else if (key == KeyEsc)
        {
            clearScreen();
            exit(0);
        }

        // ارسم الزرار المحدد بعد كل تحرك
        clearScreen();
        drawButtons(selected);
        cout.flush();
    }

    return 0;
}
