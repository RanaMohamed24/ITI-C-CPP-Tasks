#include "header.h"
#include <iostream>
using namespace std;
void swap_by_add(int &a, int &b){
    a = a + b;
    b = a - b;
    a = a - b;

 
}

void swap_by_xor(int &a, int &b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

   
}
void swap_by_multiply(int &a, int &b){

    if( a== 0 || b == 0 ){
        return; 
    } 
    else{      
    
        a = a * b;
        b = a / b;
        a = a / b;

    }
    
    
}