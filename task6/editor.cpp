#include "editor.h"
#include "ui.h"

#include <iostream>
#include <cstring>

using namespace std;

void initTextEditor(TextEditor* editor, int size)
{
    editor->maxSize = size;
    editor->buffer = new char[editor->maxSize]();
    editor->currentLength = 0;
    editor->cursorRow = 0;
    editor->cursorCol = 0;
   
}

bool insertChar(TextEditor* editor, char ch)
{
    if (editor->currentLength >= editor->maxSize)
        return false;

    int pos = getAbsoluteCursorPos(editor);
    
    for (int i = editor->currentLength; i > pos; i--)
        editor->buffer[i] = editor->buffer[i - 1];
    
    editor->buffer[pos] = ch;
    editor->currentLength++;
    
    if (ch == '\n')
    {
        editor->cursorRow++;
        editor->cursorCol = 0;
    }
    else
    {
        editor->cursorCol++;
    }
    
    return true;
}

bool deleteChar(TextEditor* editor)
{
    int pos = getAbsoluteCursorPos(editor);
    if (pos >= editor->currentLength)
        return false;

    for (int i = pos; i < editor->currentLength - 1; i++)
        editor->buffer[i] = editor->buffer[i + 1];
    
    editor->currentLength--;
    editor->buffer[editor->currentLength] = 0;
    return true;
}

void moveToEndOfPreviousLine(TextEditor* editor)
{
    if (editor->cursorRow <= 0)
        return;
    
    editor->cursorRow--;
    editor->cursorCol = 0;
    
    int currentRow = 0;
    for (int i = 0; i < editor->currentLength; i++)
    {
        if (currentRow == editor->cursorRow)
        {
            if (i < editor->currentLength && editor->buffer[i] != '\n')
                editor->cursorCol++;
            else
                break;
        }
        if (editor->buffer[i] == '\n')
            currentRow++;
    }
}

bool backspace(TextEditor* editor)
{
    int pos = getAbsoluteCursorPos(editor);
    if (pos <= 0)
        return false;

    if (editor->cursorCol > 0)
    {
        editor->cursorCol--;
    }
    else
    {
        moveToEndOfPreviousLine(editor);
    }

    pos = getAbsoluteCursorPos(editor);
    
    for (int i = pos; i < editor->currentLength - 1; i++)
        editor->buffer[i] = editor->buffer[i + 1];
    
    editor->currentLength--;
    editor->buffer[editor->currentLength] = 0;
    return true;
}

void moveCursorLeft(TextEditor* editor)
{
    if (editor->cursorCol > 0)
    {
        editor->cursorCol--;
    }
    else
    {
        moveToEndOfPreviousLine(editor);
    }
}

void moveCursorRight(TextEditor* editor)
{
    int pos = getAbsoluteCursorPos(editor);
    if (pos >= editor->currentLength)
        return;

    if (pos < editor->currentLength && editor->buffer[pos] == '\n')
    {
        editor->cursorRow++;
        editor->cursorCol = 0;
    }
    else
    {
        editor->cursorCol++;
    }
}

void moveCursorUp(TextEditor* editor)
{
    if (editor->cursorRow > 0)
        editor->cursorRow--;
}

void moveCursorDown(TextEditor* editor)
{
    int totalRows = 0;
    for (int i = 0; i < editor->currentLength; i++)
        if (editor->buffer[i] == '\n')
            totalRows++;
    
    if (editor->cursorRow < totalRows)
        editor->cursorRow++;
}

void cleanupTextEditor(TextEditor* editor)
{
    if (editor->buffer != nullptr)
    {
        delete[] editor->buffer;
        editor->buffer = nullptr;
    }
    editor->maxSize = 0;
    editor->currentLength = 0;
    editor->cursorRow = 0;
    editor->cursorCol = 0;
   
}

int getAbsoluteCursorPos(const TextEditor* editor)
{
    int pos = 0;
    int currentRow = 0;
    int currentCol = 0;

    for (int i = 0; i < editor->currentLength; i++)
    {
        if (currentRow == editor->cursorRow && currentCol == editor->cursorCol)
            return i;

        if (editor->buffer[i] == '\n')
        {
            currentRow++;
            currentCol = 0;
        }
        else
        {
            currentCol++;
        }
    }

    return editor->currentLength;
}

void redrawEditor(TextEditor* editor)
{
    clearScreen();
    moveCursor(1, 1);
    setColor(GREEN);
    cout << "=== EDITING (ESC to save/discard, Enter for newline) ===" << endl;
    setColor(YELLOW);
    cout << "Buffer Size: " << editor->maxSize << " | Length: " << editor->currentLength << endl;
    setColor(WHITE);

    int displayRow = EDITOR_START_ROW;
    int currentRow = 0;
    int currentCol = 0;

    moveCursor(displayRow, EDITOR_START_COL);

    for (int i = 0; i < editor->currentLength; i++)
    {
        if (editor->buffer[i] == '\n')
        {
            cout << endl;
            currentRow++;
            displayRow++;
            moveCursor(displayRow, EDITOR_START_COL);
            currentCol = 0;
        }
        else
        {
            cout << editor->buffer[i];
            currentCol++;
        }
    }

    cout.flush();
}