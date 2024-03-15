#include <iostream>


void subset(int* arr, int size) {
    unsigned long long boolean = std::pow(2, size) - 1;

    while (boolean != 0) {
        std::cout << "[ ";
        for (int i = 0; i < size; i++) {
            if ((static_cast<unsigned long long>(1) << i) & boolean)
                std::cout << arr[i] << ' ';
        }
        std::cout << "]\n";
        boolean--;
    }
}



int main()
{
    int* arr = new int[4];
    for (int i = 0; i < 4; i++)
        arr[i] = i;

    subset(arr, 4);
}
