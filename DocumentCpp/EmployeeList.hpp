#include <iostream>
#include <string>
#include "Employee.hpp"

class EmployeeList
{
    int allocEmployee;
    int currentEmployee;
    Employee **employeeList;

public:
    EmployeeList(int allocEmployee)
        : allocEmployee(allocEmployee)
    {
        employeeList = new Employee *[allocEmployee];
        currentEmployee = 0;
    }

    void AddEmployee(Employee *employee);

    int CurrentEmployeeNum()
    {
        return currentEmployee;
    }

    void PrintEmployeeInfo();

    ~Employee()
    {
        for (int i = 0; i < currentEmployee; i++)
        {
            delete employeeList[i];
        }
        delete[] employeeList;
    }
}