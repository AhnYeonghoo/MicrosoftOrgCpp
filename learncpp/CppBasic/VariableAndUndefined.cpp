#include <iostream>

void DoNothing(int &)
{
}
int main()
{
    int x;

    std::cout << x << '\n';
    DoNothing(x);

    std::cout << x << '\n';

    std::cout << sizeof(int) << '\n';
    return 0;
}