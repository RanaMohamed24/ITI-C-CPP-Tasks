/*#include "header.h"
#include <iostream>
using namespace std;

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
        if (key == 8 || key == 127)
            return;
        if (key == 27)
        {
            clearScreen();
            exit(0);
        }
    }
}

int main()
{
    int selected = 0; 
    while (true)
    {
        clearScreen();
        drawButtons(selected);
        int key = getInput();
        
        
        if (key == 27)
        {
           
            int k2 = getInput();
            if (k2 == '[') 
            {
                int k3 = getInput();
                if (k3 == 'A') 
                    selected = (selected - 1 + 3) % 3;
                else if (k3 == 'B') 
                    selected = (selected + 1) % 3;
                else if (k3 == 'D') 
                    selected = (selected - 1 + 3) % 3;
                else if (k3 == 'C') 
                    selected = (selected + 1) % 3;
            }
            else 
            {
                clearScreen();
                exit(0);
            }
        }
        
#if defined(_WIN32)
       
        if (key == 224 || key == 0)
        {
            int arrow = getInput();
            if (arrow == 72) 
                selected = (selected - 1 + 3) % 3;
            else if (arrow == 80) 
                selected = (selected + 1) % 3;
            else if (arrow == 75) 
                selected = (selected - 1 + 3) % 3;
            else if (arrow == 77) 
                selected = (selected + 1) % 3;
        }
#endif
        
        
        if (key == 13 || key == '\n')
        {
            if (selected == 0)
                openScreen("NEW");
            else if (selected == 1)
                openScreen("DISPLAY");
            else if (selected == 2)
                openScreen("EXIT");
            continue;
        }
    }
    return 0;
}*/


#include "header.h"
#include <iostream>
using namespace std;

void openScreen(const string &title)
{
    while (true)
    {
        clearScreen();
        moveCursor(5,5);
        cout << ">>> " << title << " SCREEN <<<\n\n";
        cout << "Press BACKSPACE to return\n";
        cout << "Press ESC to exit program\n";

        int key = getInput();
        if (key == KeyBackspace) return;
        if (key == KeyEsc)
        {
            clearScreen();
            exit(0);
        }
    }
}

int main()
{
    int selected = 0;
    const int totalButtons = 3;

    // عرض الـ menu فورًا
    clearScreen();
    drawButtons(selected);
    cout.flush();

    while(true)
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
            if(selected == 0) openScreen("NEW");
            else if(selected == 1) openScreen("DISPLAY");
            else if(selected == 2) openScreen("EXIT");
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
