#include <iostream>

int main()
{
    int *p = new int;
    *p = 10;
    std::cout << *p << std::endl;

    delete p;

    const int arrSize = 10;
    int *list = new int[arrSize];
    for (size_t i = 0; i < arrSize; i++)
    {
        list[i] = i + 1;
    }

    for (size_t i = 0; i < arrSize; i++)
    {
        std::cout << i << "th element of list : " << list[i] << std::endl;
    }

    delete[] list;

    return 0;
}