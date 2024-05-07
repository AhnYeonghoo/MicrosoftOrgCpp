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

int main()
{
    std::cout << "Enter an integer: ";
    int num{};
    std::cin >> num;
    std::cout << num << " doubled is: " << num * 2 << std::endl;

    GetValueFromUser();

    return 0;
}