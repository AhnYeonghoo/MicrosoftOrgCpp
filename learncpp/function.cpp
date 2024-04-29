
#include <iostream>

void DoPrint()
{
    std::cout << "In DoPrint()\n";
}

void DoB()
{
    std::cout << "In DoB()\n";
}

void DoA()
{
    std::cout << "Starting DoA()\n";
    DoB();
    std::cout << "Ending DoA()\n";
}

int main()
{
    std::cout << "Starting Main()\n";
    DoPrint();
    std::cout << "Ending Main()\n";

    return 0;
}