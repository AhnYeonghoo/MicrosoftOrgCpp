#include "EmployeeList.hpp"

void EmployeeList::AddEmployee(Employee *employee)
{
    employeeList[currentEmployee] = employee;
    currentEmployee++;
}

void EmployeeList::PrintEmployeeInfo()
{
    int totalPay = 0;

    for (int i = 0; i < currentEmployee; i++)
    {
        employeeList[i]->PrintInfo();
        totalPay += employeeList[i]->CalculatePay();
    }

    std::cout << "총 비용 : " << totalPay << "만원" << std::endl;
}