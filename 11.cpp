#include <iostream>

int ChangeVal(int *p)
{
    *p = 3;
    return 0;
}

int ChangeVal(int &p)
{
    p = 3;
    return 0;
}

int main()
{
    int number = 5;

    std::cout << number << std::endl;
    ChangeVal(&number);
    std::cout << number << std::endl;

    int a = 3;
    int &anotherA = a;

    anotherA = 5;
    std::cout << a << std::endl;
    std::cout << anotherA << std::endl;

    int number2 = 5;
    std::cout << number2 << std::endl;
    ChangeVal(number2);
    std::cout << number2 << std::endl;

    return 0;
}