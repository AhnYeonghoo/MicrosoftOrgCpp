#include <iostream>

using namespace std;

int AddTwoNumbers(int num_a, int num_b)
{
    int sum = num_a + num_b;
    return sum;
}

int MultiplyTwoNumbers(int a, int b)
{
    int sum = a * b;
    return sum;
}

int SubTwoNumbers(int a, int b)
{
    return a - b;
}

int DivideTwoNumbers(int a, int b)
{
    return a / b;
}

void PrintHello()
{
    cout << "Hello " << endl;
}
int main()
{
    cout << 1 + 2 << endl;
    cout << 3 + 4 << endl;
    cout << 8 + 13 << endl;

    cout << AddTwoNumbers(1, 2) << endl;
    cout << AddTwoNumbers(3, 4) << endl;
    cout << AddTwoNumbers(8, 13) << endl;

    return 0;
}