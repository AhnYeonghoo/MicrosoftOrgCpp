#include <iostream>
using namespace std;

int fLogMemory = 0;
int cBlocksAllocated = 0;

void *operator new(size_t stAllocateBlock)
{
    static int fInOpNew = 0;

    if (fLogMemory && !fInOpNew)
    {
        fInOpNew = 1;
        clog << "Memory block " << ++cBlocksAllocated
             << " allocated for " << stAllocateBlock << " bytes\n";
        fInOpNew = 0;
    }
    return malloc(stAllocateBlock);
}

void operator delete(void *pvMem)
{
    static int fInOpDelete = 0;
    if (fLogMemory && !fInOpDelete)
    {
        fInOpDelete = 1;
        clog << "Memory Block " << cBlocksAllocated--
             << " deallocated\n";
        fInOpDelete = 0;
    }
    free(pvMem);
}

int main(int argc, char *argv[])
{
    fLogMemory = 1;
    for (int i = 0; i < atoi(argv[1]); i++)
    {
        char *pMem = new char[10];
        delete[] pMem;
    }
    fLogMemory = 0;
    return cBlocksAllocated;
}