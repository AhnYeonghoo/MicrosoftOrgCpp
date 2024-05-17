#include <string.h>
#include <iostream>

class Test
{
    char c;

public:
    Test(char c)
    {
        this->c = c;
        std::cout << "생성자 호출" << c << std::endl;
    }

    ~Test() { std::cout << "소멸자 호출" << std::endl; }

    void SimpleFunction();
};