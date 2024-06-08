#include <iostream>

int main()
{
    int x = 0;
    std::cout << x << std::endl;
    std::cout << &x << std::endl;
    {
        int x = 1;
        std::cout << x << std::endl;
        std::cout << &x << std::endl;
    }

    {
        int x = 2;
        std::cout << x << std::endl;
        std::cout << &x << std::endl;
    }
    {
        int x = 3;
        {
            int x = 4;
            std::cout << x << std::endl;
            std::cout << &x << std::endl;
        }
    }
    std::cout << x << std::endl;
    std::cout << &x << std::endl;

    return 0;
}