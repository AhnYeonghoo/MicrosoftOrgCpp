
#include <malloc.h>
#include <memory.h>

class Blanks
{
public:
    Blanks() {}
    void *operator new(size_t stAllocateBlock, char chInit);
};

void *Blanks::operator new(size_t stAllocateBlock, char chInit)
{
    void *pvTemp = malloc(stAllocateBlock);
    if (pvTemp != 0)
    {
        memset(pvTemp, chInit, stAllocateBlock);
    }
    return pvTemp;
}

class MyClass
{
public:
    void *operator new[](size_t)
    {
        return 0;
    }
    void operator delete[](void *)
    {
    }
};

int main()
{
    Blanks *a5 = new (0xa5) Blanks;

    MyClass *pMyClass = new MyClass[5];
    delete[] pMyClass;
    return a5 != 0;
}