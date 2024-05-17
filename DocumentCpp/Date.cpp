#include <iostream>

class Date
{
    int year;
    int month;
    int day;

public:
    void SetDate(int year, int month, int date);
    void AddDay(int inc);
    void AddMonth(int inc);
    void AddYear(int inc);
    Date(int year, int month, int day)
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    Date()
    {
        year = 2012;
        month = 7;
        day = 12;
    }

    int GetCurrentMonthTotalDays(int year, int month);
    void ShowDate();
};

void Date::SetDate(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month)
{
    static int monthDay[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month != 2)
    {
        return monthDay[month - 1];
    }
    else if (year % 4 == 0 && year % 100 != 0)
    {
        return 29;
    }
    else
    {
        return 28;
    }
}

void Date::AddDay(int inc)
{
    while (true)
    {
        int currentMonthTotalDays = GetCurrentMonthTotalDays(this->year, this->month);

        if (this->day + inc <= currentMonthTotalDays)
        {
            this->day += inc;
            return;
        }
        else
        {
            inc -= (currentMonthTotalDays - this->day + 1);
            this->day = 1;
            AddMonth(1);
        }
    }
}

void Date::AddMonth(int inc)
{
    AddYear((inc + this->month - 1) / 12);
    this->month = this->month + inc % 12;
    this->month = (this->month == 12 ? 12 : this->month % 12);
}

void Date::AddYear(int inc)
{
    this->year += inc;
}

void Date::ShowDate()
{
    std::cout << "오늘은 " << year << " 년" << month << " 월" << day << " 일 입니다. " << std::endl;
}