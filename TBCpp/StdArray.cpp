#include <iostream>
#include <array>

int main()
{
    std::array<int, 3> a = {1, 2, 3};
    std::array<int, 3> b;

    b = a;

    std::array<int, 6> data = {1, 2, 3, 4, 5, 6};

    data.at(1) = 88;

    std::cout << "Index 2 location elemental: " << data.at(2) << std::endl;
    std::cout << "data Array is size: " << data.size() << std::endl;

    try
    {
        data.at(6) = 666;
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "data: ";
    for (int elem : data)
        std::cout << " " << elem;
    std::cout << std::endl;
}