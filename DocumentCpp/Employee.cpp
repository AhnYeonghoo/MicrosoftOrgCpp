#include "Employee.hpp"

void Employee::PrintInfo()
{
    std::cout << name << " (" << position << " , " << age << ") ==> "
              << CalculatePay() << " 만원 " << std::endl;
}

int Employee::CalculatePay()
{
    return 200 + rank * 50;
}