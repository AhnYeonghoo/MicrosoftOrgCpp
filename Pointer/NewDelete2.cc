#include <iostream>
#include <new>
using namespace std;
#define BIG_NUMBER 10000000000LL
int main()
{
    try
    {
        int *pi = new int[BIG_NUMBER];
    }
    catch (const bad_alloc &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
}