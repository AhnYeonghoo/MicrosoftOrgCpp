
#include <iostream>

int *const cpObject = 0;
int *pObject;

struct X
{
    X(int i) : m_i(i) {}
    int m_i;
};

int main()
{
    pObject = cpObject;

    const X cx(10);
    const X *pcx = &cx;
    const X **ppcx = &pcx;

    X const cx2(20);
    X const *pcx2 = &cx2;
    X const **ppcx2 = &pcx2;

    return 0;
}