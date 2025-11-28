#include "screens.h"
#include "keyboard.h"
#include "ui.h"
#include "editor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdexcept>

using namespace std;

void newScreen(TextEditor& editor)
{
    clearScreen();
    printHeader("=== NEW TEXT EDITOR ===", 3, 5);
    cout << endl;
    printColoredMessage("(Press ESC to return to menu)", 4, 5, YELLOW);
    cout << endl;

    int size = readNumber("Enter buffer size (max characters): ", 6, 5, MIN_BUFFER_SIZE, MAX_BUFFER_SIZE);


    if (size == -1)
    {
        return;
    }

    initTextEditor(&editor, size);

    clearScreen();
    printColoredMessage("=== EDITING (ESC to save/discard or return to menu) ===", 1, 1, GREEN);
    cout << endl;
    printColoredMessage("Buffer Size: " + to_string(size) + " | Length: 0", 2, 1, YELLOW);
    cout << endl;
    printColoredMessage("Press ESC to return to menu or save your work", 3, 1, CYAN);
    cout << endl;
    moveCursor(EDITOR_START_ROW+1, EDITOR_START_COL);
    cout.flush();

    while (true)
    {
        int key = getInput();

        if (key == KeyEsc)
        {
            clearScreen();
            printHeader("=== OPTIONS ===", 5, 30);
            cout << endl;

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
                saveToFile(editor);
                return;
            }
            else if (choice == '2')
            {
                return;
            }
            else
            {
                redrawEditor(&editor);
            }
        }
        else if (key == KeyLeft)
        {
            moveCursorLeft(&editor);
        }
        else if (key == KeyRight)
        {
            moveCursorRight(&editor);
        }
        else if (key == KeyUp)
        {
            moveCursorUp(&editor);
        }
        else if (key == KeyDown)
        {
            moveCursorDown(&editor);
        }
        else if (key == KeyBackspace)
        {
            backspace(&editor);
            redrawEditor(&editor);
        }
        else if (key == KeyDelete)
        {
            deleteChar(&editor);
            redrawEditor(&editor);
        }
        else if (key == KeyEnter)
        {

            insertChar(&editor, '\n');
            redrawEditor(&editor);
        }
        else if (key >= MIN_PRINTABLE_CHAR && key <= MAX_PRINTABLE_CHAR)
        {
            char ch = (char)key;
            if (insertChar(&editor, ch))
            {
                redrawEditor(&editor);
            }
        }

        cout.flush();
    }
}

void displayScreen()
{
    clearScreen();
    printHeader("=== DISPLAY FILE CONTENT ===", 3, 5);
    cout << endl;

    string filename = readString("Enter filename: ", 5, 5);

    if (filename.empty())
    {
        printError("No filename entered!", 7, 5);
    }
    else
    {
        try
        {
            ifstream file(filename, ios::binary);
            if (!file.is_open())
            {
                throw runtime_error("File not found");
            }

            file.seekg(0, ios::end);
            int fileSize = file.tellg();
            file.seekg(0, ios::beg);

            printColoredMessage("File: " + filename + " (" + to_string(fileSize) + " characters)", 7, 5, GREEN);
            cout << endl;
            moveCursor(9, 5);
            cout << string(70, '-') << endl;
            moveCursor(10, 5);

            char ch;
            while (file.get(ch))
            {

                if (ch == '\n' || ch == '\r' || ch == '\t' || 
                    (ch >= MIN_PRINTABLE_CHAR && ch <= MAX_PRINTABLE_CHAR))
                {
                    cout << ch;
                }
                else
                {

                    cout << '.';
                }
            }
            cout << endl;
        }
        catch (const exception& e)
        {
            printError("Error: " + string(e.what()), 7, 5);
        }
    }

    waitForKey("Press any key to return to menu...", 20, 5);
}

void exitScreen(TextEditor& editor)
{
    clearScreen();
    printColoredMessage("Are you sure you want to exit? (y/n): ", 10, 30, RED);
    cout.flush();

    char ch = getChar();
    if (ch == 'y' || ch == 'Y')
    {
        clearScreen();
        printColoredMessage("Goodbye!", 12, 30, GREEN);
        moveCursor(14, 30);
        cout << "Exiting...";

        sleep(1);

        cleanupTextEditor(&editor);

        clearScreen();
        exit(0);
    }
}

void saveToFile(TextEditor& editor)
{
    string filename = readString("Enter filename: ", 13, 5);

    if (filename.empty())
    {
        printError("No filename entered! Press any key...", 15, 5);
        getChar();
        return;
    }

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
                cout << mode;
                cout.flush();
                break;
            }
        }

        moveCursor(16, 5);
        bool success = false;
        if (mode == 'A' || mode == 'a')
        {
            printColoredMessage("Appending to file...", 16, 5, YELLOW);
            success = writeToFile(filename, editor.buffer, editor.currentLength, true);
        }
        else
        {
            printColoredMessage("Overwriting file...", 16, 5, YELLOW);
            success = writeToFile(filename, editor.buffer, editor.currentLength, false);
        }
        
        if (!success)
        {
            printError("Error saving file: Could not open file", 17, 5);
            waitForKey("Press any key...", 18, 5);
            return;
        }
    }
    else
    {
        if (!writeToFile(filename, editor.buffer, editor.currentLength, false))
        {
            printError("Error saving file: Could not open file", 16, 5);
            waitForKey("Press any key...", 17, 5);
            return;
        }
    }

    printColoredMessage("File saved! Press any key...", 17, 5, GREEN);
    getChar();
}

bool writeToFile(const string& filename, const char* data, int length, bool append)
{
    try
    {
        ios::openmode mode = ios::binary;
        if (append)
            mode |= ios::app;
        
        ofstream file(filename, mode);
        if (!file.is_open())
        {
            throw runtime_error("Could not open file");
        }
        
        file.write(data, length);
        file.close();
        return true;
    }
    catch (const exception&)
    {
        return false;
    }
}

