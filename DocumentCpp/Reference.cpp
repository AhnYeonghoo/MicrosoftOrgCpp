#include <iostream>

int ChangeVal(int *p)
{
    *p = 3;
    return 0;
}

int ChangeVal(int &p)
{
    p = 2;
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

    std::cout << anotherA << std::endl;
    std::cout << a << std::endl;

    std::cout << number << std::endl;
    ChangeVal(number);
    std::cout << number << std::endl;

    int x;
    int &y = x;
    int &z = y;

    x = 1;
    std::cout << x << " " << y << " " << z << std::endl;
    y = 2;
    std::cout << x << " " << y << " " << z << std::endl;
    z = 3;
    std::cout << x << " " << y << " " << z << std::endl;
}