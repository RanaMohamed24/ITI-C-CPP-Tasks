#include "header.h"
#include <cstdlib>
#include <iostream>

using namespace std;


int main(){

    int x = 5;
    int y = 10;

   

    swap_by_add(x, y);

     cout << "After : x = " << x << ", y = " << y << endl;
  


    int a = 15;
    int b = 20;

    swap_by_xor(a, b);
    cout << "After : a = " << a << ", b = " << b << endl;


    int i = 20;
    int j = 10;

    swap_by_multiply(i, j);
        cout << "After : i = " << i << ", j = " << j << endl;

    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    int arr[MAX][MAX];

    Array2D(arr, rows, cols);
    DisplayArray(arr, rows, cols);
    
    return 0;

}