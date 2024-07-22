#include <iostream>
#include <cmath>

int main()
{
    using namespace std;

    short s = 1;
    int i = 1;
    long l = 1;
    long long ll = 1;

    cout << sizeof(short) << endl;
    cout << sizeof(int) << endl;
    cout << sizeof(long) << endl;
    cout << sizeof(long long) << endl;

    std::cout << std::pow(2, sizeof(short) * 8) << std::endl;
    std::cout << std::pow(2, sizeof(short) * 8 - 1) - 1 << std::endl;

    cout << "I Love you. " << endl;

    exit(0);

    return 0;
}