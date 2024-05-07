#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << 4 << std::endl;
    int x{5};
    std::cout << x << std::endl;
    std::cout << "Hello "
              << "World!" << std::endl;
    std::cout << "x is equal to: " << x << std::endl;

    std::cout << "Hi! " << std::endl; // std::endl will casue the
    // cursor to move to the next line

    std::cout << "my name is alex. " << std::endl;

    std::cout << "x is equal to : " << x << '\n';
    std::cout << "Yep. "
              << "\n";
    std::cout << "And That`s all, folks!\n";

    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y;
    std::cout << "You entered " << y << std::endl;

    return 0;
}