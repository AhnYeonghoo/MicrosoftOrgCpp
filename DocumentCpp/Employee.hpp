#include <iostream>
#include <string>

class Employee
{
private:
    std::string name;
    int age;

    std::string position;
    int rank;

public:
    Employee(std::string name, int age, std::string position, int rank)
        : name(name), age(age), position(position), rank(rank) {}

    Employee(const Employee &employee)
    {
        name = employee.name;
        age = employee.age;
        position = employee.position;
        rank = employee.rank;
    }

    Employee() = default;

    void PrintInfo();
    int CalculatePay();
};