#include "header.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int str_len(char arr[])
{
    int count = 0;
    while (arr[count] != '\0')
    {
        count++;
    }
    return count;
}

int str_cmp(char arr1[], char arr2[])
{
    int len1 = str_len(arr1);
    int len2 = str_len(arr2);

    if (len1 != len2)
        return -5;

    if (len1 == len2)
    {
        int i = 0;
        while (arr1[i] != '\0' && arr2[i] != '\0')
        {
            if (arr1[i] != arr2[i])
            {
                if (arr1[i] > arr2[i])
                    return 1;
                else
                    return -1;
            }
            i++;
        }
    }
    return 0;
}
void str_to_lower(char arr[])
{
    int i = 0;
    while (arr[i] != '\0')
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            arr[i] = arr[i] + 32;
        }
        i++;
    }
}
void str_to_capital(char arr[])
{
    int i = 0;
    while (arr[i] != '\0')
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            arr[i] = arr[i] - 32;
        }
        i++;
    }
}

void str_concat(char arr1[], char arr2[], int arr1_size)
{

    int len1 = str_len(arr1);
    int len2 = str_len(arr2);

    if (len1 + len2 + 1 > arr1_size)
    {
        cout << "not enough space " << endl;
        return;
    }
    int i = len1;
    int j = 0;
    while (arr2[j] != '\0')
    {
        arr1[i] = arr2[j];
        i++;
        j++;
    }
    arr1[i] = '\0';
}

void strcpy(char arr1[], char arr2[])

{

    int len1 = str_len(arr1);
    int len2 = str_len(arr2);
    if (len2 > len1)
    {
        cout << "not enough space " << endl;
        return;
    }
    int i = 0;
    while (arr2[i] != '\0')
    {
        arr1[i] = arr2[i];
        i++;
    }
    arr1[i] = '\0';
}