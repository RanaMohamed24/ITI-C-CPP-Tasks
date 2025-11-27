#include "header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdexcept>

using namespace std;

void newScreen(TextEditor& editor)
{
    clearScreen();
    moveCursor(3, 5);
    setColor(CYAN);
    cout << "=== NEW TEXT EDITOR ===" << endl;
    setColor(WHITE);
    
    moveCursor(4, 5);
    setColor(YELLOW);
    cout << "(Press ESC to return to menu)" << endl;
    setColor(WHITE);

    int size = readNumber("Enter buffer size (max characters): ", 6, 5, MIN_BUFFER_SIZE, MAX_BUFFER_SIZE);


    if (size == -1)
    {
        return;
    }

    initTextEditor(&editor, size);

    clearScreen();
    moveCursor(1, 1);
    setColor(GREEN);
    cout << "=== EDITING (ESC to save/discard or return to menu) ===" << endl;
    setColor(YELLOW);
    cout << "Buffer Size: " << size << " | Length: 0" << endl;
    setColor(CYAN);
    cout << "Press ESC to return to menu or save your work" << endl;
    setColor(WHITE);
    moveCursor(EDITOR_START_ROW+1, EDITOR_START_COL);
    cout.flush();

    while (true)
    {
        int key = getInput();

        if (key == KeyEsc)
        {
            clearScreen();
            moveCursor(5, 30);
            setColor(CYAN);
            cout << "=== OPTIONS ===" << endl;
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
    moveCursor(3, 5);
    setColor(CYAN);
    cout << "=== DISPLAY FILE CONTENT ===" << endl;
    setColor(WHITE);

    string filename = readString("Enter filename: ", 5, 5);

    if (filename.empty())
    {
        moveCursor(7, 5);
        setColor(RED);
        cout << "No filename entered!";
        setColor(WHITE);
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

            moveCursor(7, 5);
            setColor(GREEN);
            cout << "File: " << filename << " (" << fileSize << " characters)" << endl;
            setColor(WHITE);
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
            moveCursor(7, 5);
            setColor(RED);
            cout << "Error: " << e.what();
            setColor(WHITE);
        }
    }

    moveCursor(20, 5);
    cout << "Press any key to return to menu...";
    getChar();
}

void exitScreen(TextEditor& editor)
{
    clearScreen();
    moveCursor(10, 30);
    setColor(RED);
    cout << "Are you sure you want to exit? (y/n): ";
    setColor(WHITE);
    cout.flush();

    char ch = getChar();
    if (ch == 'y' || ch == 'Y')
    {
        clearScreen();
        moveCursor(12, 30);
        setColor(GREEN);
        cout << "Goodbye!";
        setColor(WHITE);
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
        moveCursor(15, 5);
        setColor(RED);
        cout << "No filename entered! Press any key...";
        setColor(WHITE);
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
        try
        {
            if (mode == 'A' || mode == 'a')
            {
                setColor(YELLOW);
                cout << "Appending to file...";
                setColor(WHITE);
                ofstream file(filename, ios::app | ios::binary);
                if (file.is_open())
                {
                    file.write(editor.buffer, editor.currentLength);
                    file.close();
                }
                else
                {
                    throw runtime_error("Could not open file");
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
                    file.write(editor.buffer, editor.currentLength);
                    file.close();
                }
                else
                {
                    throw runtime_error("Could not open file");
                }
            }
        }
        catch (const exception& e)
        {
            moveCursor(17, 5);
            setColor(RED);
            cout << "Error saving file: " << e.what();
            setColor(WHITE);
            moveCursor(18, 5);
            cout << "Press any key...";
            getChar();
            return;
        }
    }
    else
    {
        try
        {
            ofstream file(filename, ios::binary);
            if (file.is_open())
            {
                file.write(editor.buffer, editor.currentLength);
                file.close();
            }
            else
            {
                throw runtime_error("Could not open file");
            }
        }
        catch (const exception& e)
        {
            moveCursor(16, 5);
            setColor(RED);
            cout << "Error saving file: " << e.what();
            setColor(WHITE);
            moveCursor(17, 5);
            cout << "Press any key...";
            getChar();
            return;
        }
    }

    moveCursor(17, 5);
    setColor(GREEN);
    cout << "File saved! Press any key...";
    setColor(WHITE);
    getChar();
}
