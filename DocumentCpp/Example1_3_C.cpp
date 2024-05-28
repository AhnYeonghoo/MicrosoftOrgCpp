#include <iostream>

int var;
int F() { return var; }

namespace
{
    int var;
    int F() { return var; }
}

int main()
{
    int m = var;
    int k = F();
}