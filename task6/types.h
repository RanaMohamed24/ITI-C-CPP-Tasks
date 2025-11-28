#ifndef TYPES_H
#define TYPES_H

const int MAX_BUFFER_SIZE = 10000;
const int MIN_BUFFER_SIZE = 1;
const int MIN_PRINTABLE_CHAR = 32;
const int MAX_PRINTABLE_CHAR = 126;
const int EDITOR_START_ROW = 3;
const int EDITOR_START_COL = 1;

enum Color
{
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

enum Key
{
    KeyNone = 0,
    KeyUp,
    KeyDown,
    KeyLeft,
    KeyRight,
    KeyEnter,
    KeyBackspace,
    KeyEsc,
    KeyDelete,
    KeyChar
};

struct TextEditor
{
    char* buffer;
    int maxSize;
    int currentLength;
    int cursorRow;
    int cursorCol;
    int scrollOffset;
};

#endif
