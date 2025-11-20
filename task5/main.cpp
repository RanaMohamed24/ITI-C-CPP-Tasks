#include "header.h"
#include <iostream>
using namespace std;

int main()
{
    Employee employees[100]; 
    int employeeCount = 0;   
    
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
            {
                addEmployee(employees, &employeeCount);  // Add new employee
            }
            else if (selected == 1)
            {
                displayEmployees(employees, employeeCount);  // Display all employees
            }
            else if (selected == 2)
            {
                clearScreen();
                cout << "\n\n  Thank you for using Employee Management System!\n\n";
                exit(0);
            }
        }
        else if (key == KeyEsc)
        {
            clearScreen();
            exit(0);
        }

        clearScreen();
        drawButtons(selected);
        cout.flush();
    }

    return 0;
}