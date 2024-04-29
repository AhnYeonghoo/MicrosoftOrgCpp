#include <iostream>

void GetValueFromUser()
{
    std::cout << "Enter an Integer: ";
    int input{};
    std::cin >> input;
}

int ReturnFive()
{
    return 5;
}

int GetValueFromUser2()
{
    std::cout << "Enter an Integer: ";
    int input{};
    std::cin >> input;

    return input;
}

int GetValueFromUserUB()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
}
int main()
{
    std::cout << "Enter an Integer: ";
    int num{};
    std::cin >> num;

    std::cout << num << " Doubled is : " << num * 2 << "\n";

    GetValueFromUser();

    std::cout << num << "doubled is: " << num * 2 << std::endl;

    return 0;
}