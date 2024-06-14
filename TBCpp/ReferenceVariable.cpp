#include <iostream>

int ChangeValue(int &p)
{
    p = 3;
    return 0;
}

int main()
{
    int a = 3;
    int &anotherA = a;

    anotherA = 5;
    std::cout << a << std::endl;
    std::cout << anotherA << std::endl;

    int number = 5;

    std::cout << number << std::endl;
    ChangeValue(number);
    std::cout << number << std::endl;

    return 0;
}