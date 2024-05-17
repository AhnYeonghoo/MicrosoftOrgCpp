#include <iostream>

class Array
{
private:
    const int dim;
    int *size;

private:
    struct Address
    {
        int level;
        void *next;
    };
    Address *top;

public:
    Array(int dim, int *arraySize) : dim(dim)
    {
        size = new int[dim];
        for (int i = 0; i < dim; i++)
            size[i] = arraySize[i];
        top = new Address;
        top->level = 0;
        InitializeAddress(top);
    }

    ~Array()
    {
        DeleteAddress(top);
        delete[] size;
    }

    void InitializeAddress(Address *current);
    void DeleteAddress(Address *current);
}