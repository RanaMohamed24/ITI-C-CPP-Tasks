#ifndef EDITOR_H
#define EDITOR_H

#include "types.h"

void initTextEditor(TextEditor* editor, int size);
void cleanupTextEditor(TextEditor* editor);
bool insertChar(TextEditor* editor, char ch);
bool deleteChar(TextEditor* editor);
bool backspace(TextEditor* editor);
void moveCursorLeft(TextEditor* editor);
void moveCursorRight(TextEditor* editor);
void moveCursorUp(TextEditor* editor);
void moveCursorDown(TextEditor* editor);
int getAbsoluteCursorPos(const TextEditor* editor);
void redrawEditor(TextEditor* editor);
void moveToEndOfPreviousLine(TextEditor* editor);

#endif
