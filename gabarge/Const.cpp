#include <iostream>

class Date
{
public:
	Date(int mn, int dy, int yr);
	int getMonth() const;
	void setMonth(int mn);
private:
	int month;
};

Date::Date(int mn, int dy, int yr)
{
	month = mn;
}
int Date::getMonth() const
{
	return month;
}

void Date::setMonth(int mn)
{
	month = mn;
}

int mainConst()
{
	const int i = 5;
	const int maxarray = 255;
	char store_char[maxarray];

	char this_char{ 'a' }, that_char{ 'b' };
	char* mybuf = &this_char, * yourbuf = &that_char;
	char* const aptr = mybuf;
	*aptr = 'c';

	Date MyDate(7, 4, 1998);
	const Date BirthDate(1, 18, 1953);
	MyDate.setMonth(4);

	return 0;

}