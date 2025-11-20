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
    
    return 0;

}