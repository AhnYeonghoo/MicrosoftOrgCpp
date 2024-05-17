#include <iostream>
#include <string>

class Employee
{
protected:
    std::string name;
    int age;

    std::string position;
    int rank;

public:
    Employee(std::string name, int age, std::string position, int rank)
        : name(name), age(age), position(position), rank(rank) {}

    Employee(const Employee &em)
    {
        name = em.name;
        age = em.age;
        position = em.position;
        rank = em.rank;
    }

    Employee() = default;

    void PrintInfo()
    {
        std::cout << name << " (" << position << " , " << age
                  << ") ==> " << CalculatePay() << "만원" << std::endl;
    }

    int CalculatePay()
    {
        return 200 + rank * 50;
    }
};

class Manager : public Employee
{
    int yearOfService;

public:
    Manager(std::string name, int age, std::string position, int rank,
            int yearOfService) : yearOfService(yearOfService), Employee(name, age, position, rank) {}

    Manager(const Manager &m)
        : Employee(m.name, m.age, m.position, m.rank)
    {
        yearOfService = m.yearOfService;
    }

    Manager() : Employee() {}

    int CalculatePay()
    {
        return 200 + rank * 50 + 5 * yearOfService;
    }

    void PrintInfo()
    {
        std::cout << name << " (" << position << " , " << age << ", "
                  << yearOfService << "년차) ==> " << CalculatePay() << "만원"
                  << std::endl;
    }
};

class EmployeeList
{
    int allocEmployee;
    int currentEmployee;
    Employee **employeeList;

public:
    EmployeeList(int allocEmployee) : allocEmployee(allocEmployee)
    {
        employeeList = new Employee *[allocEmployee];
        currentEmployee = 0;
    }

    void AddEmployee(Employee *employee)
    {
        employeeList[currentEmployee] = employee;
        currentEmployee++;
    }

    int currentEmployeeNum() { return currentEmployee; }

    void PrintEmployeeInfo()
    {
        int total = 0;

        for (int i = 0; i < currentEmployee; i++)
        {
            employeeList[i]->PrintInfo();
            total += employeeList[i]->CalculatePay();
        }

        std::cout << "총 비용: " << total << "만원" << std::endl;
    }

    ~EmployeeList()
    {
        for (int i = 0; i < currentEmployee; i++)
        {
            delete employeeList[i];
        }
        delete[] employeeList;
    }
}
