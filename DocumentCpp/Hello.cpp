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

    int luckyNumber = 3;
    std::cout << "내 비밀 수를 맞추어보세요~" << std::endl;

    int userInput;

    while (1)
    {
        std::cout << "입력: ";
        std::cin >> userInput;
        if (luckyNumber == userInput)
        {
            std::cout << "맞추셨습니다~~" << std::endl;
            break;
        }
        else
        {
            std::cout << "다시 생각해보세요~" << std::endl;
        }
    }
    return 0;
}