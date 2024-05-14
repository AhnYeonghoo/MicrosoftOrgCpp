
#include <vector>
#include <iostream>

template <typename T>
void print_vector(std::vector<T> &vec)
{
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
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

    for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
    {
        std::cout << "Vec의 " << i + 1 << " 번째 원소 :: " << vec[i] << std::endl;
    }

    std::vector<int>::iterator itr = vec.begin() + 2;
    std::cout << *itr << std::endl;

    for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    std::vector<int> vec2;
    vec2.push_back(10);
    vec2.push_back(20);
    vec2.push_back(30);
    vec2.push_back(40);
    std::cout << "처음 벡터 상태" << std::endl;
    print_vector(vec2);
    std::cout << "---------------------" << std::endl;

    vec2.insert(vec.begin() + 2, 15);
    print_vector(vec2);
    std::cout << "--------------------" << std::endl;
    vec.erase(vec2.begin() + 3);
    print_vector(vec2);
}