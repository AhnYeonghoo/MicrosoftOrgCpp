#include <iostream>

namespace MySpace1
{
    int DoSomething(int a, int b)
    {
        return a + b;
    }
    namespace InnerSpace
    {
        int MyFunction()
        {
            return 5;
        }
    }
}

namespace MySpace2
{
    int DoSomething(int a, int b)
    {
        return a * b;
    }
}

using namespace std;

int main()
{
    cout << MySpace1::DoSomething(1, 3) << endl;
    cout << MySpace2::DoSomething(1, 3) << endl;
    cout << MySpace1::InnerSpace::MyFunction() << endl;
    return 0;
}
