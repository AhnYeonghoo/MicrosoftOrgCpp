
#include <iostream>
#include <memory>

class A
{
    int *data;

public:
    A()
    {
        std::cout << "자원을 흭득함" << std::endl;
        data = new int[100];
    }

    void some()
    {
        std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl;
    }

    ~A()
    {
        std::cout << "자원을 해제함" << std::endl;
        delete[] data;
    }
};

void DoSomething()
{
    std::unique_ptr<A> pa(new A());
    std::cout << "pa: ";
    pa->some();

    std::unique_ptr<A> pb = std::move(pa);
    std::cout << "pb: ";
    pb->some();
}
int main()
{
    DoSomething();
}