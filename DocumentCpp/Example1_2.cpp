#include <iostream>

namespace A
{
    int i;
    double d;

    namespace B
    {
        int b;
        void F();
    }

    inline namespace C
    {
        int c;
        void G();
    }
}

int i = 1; // 파일 전체에 영향을 주는 전역 변수

int main()
{
    // 사용 시점에서 i가 해당 블록 위에 없어 다음 상위 블록에 있는 전역 변수를 찾음
    std::cout << "i value = " << i << "\n";

    int i = 10; // main 함수 마지막 부분까지 범위를 가짐

    std::cout << "i value = " << i << std::endl;

    {
        int i = 100;
        std::cout << "i value = " << i << std::endl;
    }

    {
        std::cout << "i value = " << i << std::endl;
    }

    int var = A::B::b;
    void A::B::F() {}
}
