#include <iostream>

int main()
{
    int ArraySize;
    std::cout << "ArraySize: ";
    ArraySize = 10;

    int *list = new int[ArraySize];
    for (int i = 0; i < ArraySize; i++)
    {
        list[i] = 0;
    }

    for (int i = 0; i < ArraySize; i++)
    {
        std::cout << i << "th Element of List: " << list[i] << std::endl;
    }

    delete[] list;
    return 0;
}