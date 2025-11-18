#include "header.h"
#include <iostream>
using namespace std;

int main()
{
    char str[] = "Hello,Rana";
    int length = str_len(str);
    cout << "Length of the string is: " << length << endl;

    char str1[] = "hi";
    char str2[] = "hello";
    int result1 = str_cmp(str1, str2);
    cout << "result: " << result1 << endl;

    char str3[] = "hello";
    int result2 = str_cmp(str2, str3);
    cout << "result: " << result2 << endl;

    char str4[] = "cat";
    char str5[] = "act";
    int result3 = str_cmp(str4, str5);
    cout << "result: " << result3 << endl;

    int result4 = str_cmp(str4, str4);
    cout << "result: " << result4 << endl;

    char str6[] = "RANA";
    str_to_lower(str6);
    cout << "lowercase : " << str6 << endl;

    str_to_capital(str2);
    cout << "Capital : " << str2 << endl;

    char name1[20] = "ranona";
    char name2[] = "mohamed";
    str_concat(name1, name2, 20);
    cout << "test After concat : " << name1 << endl;

    char name3[6] = "salma";
    char name4[] = "yasser";
    str_concat(name3, name4, 6);
    cout << "test after concat : " << name3 << endl;

    char copy[] = "ranona";
    char test[] = "liunxx";
    strcpy(copy, test);
    cout << "test copy : " << copy << endl;

    return 0;
}