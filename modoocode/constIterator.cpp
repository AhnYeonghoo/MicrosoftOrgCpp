#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T> &vec)
{
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); itr++)
    {
        std::cout << *itr << std::endl;
    }
}

int main()
{
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "초기 vec 상태 " << std::endl;
    print_vector(vec);

    std::vector<int>::iterator itr = vec.begin() + 2;

    *itr = 50;
    std::cout << "0000000" << std::endl;
    print_vector(vec);

    std::vector<int>::const_iterator citer = vec.cbegin() + 2;
    //*citr = 30 불가능

    std::cout << "역으로 vec 출력하기!" << std::endl;

    std::vector<int>::reverse_iterator r_iter = vec.rbegin();
    for (; r_iter != vec.rend(); r_iter++)
        std::cout << *r_iter << std::endl;
}