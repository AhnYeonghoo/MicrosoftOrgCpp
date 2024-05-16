#include <iostream>

int main()
{
    std::cout << "Hello World!!" << std::endl;
    int i;
    char c;
    double d;
    float f;

    for (int i = 0; i < 10; i++)
    {
        std::cout << i << std::endl;
    }

    int sum = 0;

    for (int i = 1; i <= 10; i++)
    {
        sum += i;
    }
    std::cout << "합은: " << sum << std::endl;
    return 0;
}