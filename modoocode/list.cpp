#include <iostream>
#include <list>

template <typename T>
void print_list(std::list<T> &lst)
{
    std::cout << "[ ";
    for (const auto &elem : lst)
    {
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

int main()
{
    std::list<int> lst;

    lst.push_back(10);
    lst.push_back(10);
    lst.push_back(10);
    lst.push_back(10);

    for (std::list<int>::iterator i = lst.begin(); i != lst.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    std::cout << "---------------------" << std::endl;

    std::cout << "처음 리스트의 상태" << std::endl;

    print_list(lst);

    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++)
    {
        if (*itr == 10)
        {
            lst.insert(itr, 50);
        }
    }

    print_list(lst);

    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); lst++)
    {
        if (*itr == 10)
        {
            lst.erase(itr);
        }
    }

    print_list(lst);
}
