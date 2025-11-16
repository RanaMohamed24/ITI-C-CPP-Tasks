#include "header.h"
#include <iostream>


using namespace std;

int main() {
    clearScreen();
    
    printColoredText("Hello Rana!", RED, 2, 10);
    printColoredText("Green text!", GREEN, 5, 15);
    printColoredText("Blue text!", BLUE, 8, 20);
    

    delay(5);
    clearScreen();
    return 0;

 
    
}


     
 


