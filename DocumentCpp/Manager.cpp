#include "EmployeeList.hpp"

class Manager
{
    std::string name;
    int age;

    std::string position;
    int rank;
    int yearOfService;

public:
    Manager(std::string name, int age, std::string position, int rank,
            int yearOfService)
        : yearOfService(yearOfService), name(name), age(age), position(position), rank(rank)
    {
    }

    Manager(const Manager &manager)
    {
        name = manager.name;
        age = manager.age;
        position = manager.position;
        rank = manager.rank;
        yearOfService = manager.yearOfService;
    }

    Manager() = default;

    int CalculatePay()
    {
        return 200 + rank * 50 + 5 * yearOfService;
    }

    void PrintInfo()
    {
        std::cout << name << " (" << position << " , " << age << ", "
                  << yearOfService << "년차) ==> " << CalculatePay() << "만원" << std::endl;
    }
}