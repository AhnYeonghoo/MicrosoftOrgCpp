
#include <iostream>
#include <cstdio>

int main()
{
    enum COLOR
    {
        RED = 1,
        GREEN,
        BLUE
    };
    std::printf("%d, %d, %d\n", COLOR::RED, COLOR::GREEN, COLOR::BLUE);
    std::printf("%d, %d, %d\n", RED, GREEN, BLUE);
    return EXIT_SUCCESS;
}