#include <iostream>

struct DataType1
{
    char c[10];
    double d;
    int n;
};

struct DataType2
{
    int n;
    char c[10];
    double d;
};

int main()
{
    std::cout << sizeof(DataType1) << std::endl;
    std::cout << sizeof(DataType2) << std::endl;
}