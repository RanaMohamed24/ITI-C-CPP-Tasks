#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include <string>

void newScreen(TextEditor& editor);
void displayScreen();
void exitScreen(TextEditor& editor);
void saveToFile(TextEditor& editor);
bool writeToFile(const std::string& filename, const char* data, int length, bool append);

#endif
