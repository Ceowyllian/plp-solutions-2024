#include <iostream>



void subset(int* arr, int size) {
    unsigned long long boolean = 1;
    for (int i = 0; i < size; i++) {
        boolean <<= 1;
        boolean++;
    }

    while (boolean != 0) {
        for (int i = 0; i < size; i++) {
            if ((1 << i) & boolean);
        }
    }
}



int main()
{
    int* arr = new int[4];
    for (int i = 0; i < 4; i++)
        arr[i] = i;

    subset(arr, 0, 4);
}
