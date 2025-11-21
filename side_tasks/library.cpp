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

void Array2D(int arr[][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }
}

void DisplayArray(int arr[][MAX], int rows, int cols) {
     cout << "The Array is:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}