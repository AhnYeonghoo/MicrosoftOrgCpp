#include <iostream>

int main()
{
    int x;        // define a variable named x, of type int
    double width; // define a variable named width, of type double
    int a;
    int b;
    int y, z;
    int width2; // define an integer variable named width
    width2 = 5; // assignment of value 5 into variable width

    std::cout << width2;
    width2 = 10;
    std::cout << width2;

    int width3{5}; // define variable width and initialize with initial value

    int aa;     // no initializer (default initialization)
    int bb = 5; // initial value after qeuals sign(copy initialization)
    int c(6);   // initial value in parenthesis (direct initialization)

    int d{7};
    int e = {8};
    int f{};

    double pi{3.14159};
    double gravity{9.8};
    double phi{1.61803};

    [[maybe_unused]] double pi2{3.14159};
    [[maybe_unused]] double gravity2{9.8};
    [[maybe_unused]] double phi2{1.61803};

    return 0;
}