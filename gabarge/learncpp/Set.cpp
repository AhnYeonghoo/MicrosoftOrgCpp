#include <iostream>
#include <set>

template <typename T>
void PrintSet(std::set<T> &s)
{
    std::cout << "[ ";
    for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        std::cout << *itr << " ";
    }
    std::cout << " ] " << std::endl;
}

int main()
{
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "순서대로 정렬되어서 나온다.";
}