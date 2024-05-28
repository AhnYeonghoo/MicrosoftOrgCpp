#include <iostream>

int i = 0;

namespace A
{
    namespace B
    {
        int i = 2;

        void F()
        {
            std::cout << "F() i value = " << i << std::endl;
        }
    }

    void G()
    {
        std::cout << "G() i value = " << i << std::endl;
    }
}

int main()
{
    A::B::F();
    A::G();
}