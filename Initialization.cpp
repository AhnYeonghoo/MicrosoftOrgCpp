#include <iostream>
using namespace std;

class MyClass
{
public:
	MyClass(int myInt) {}
	void set_int(int myInt) { m_int = myInt; }
	int get_int() const { return m_int; }
private:
	int m_int = 7;
};
class MyException : public exception {};

class BaseClass
{
public:
	BaseClass(int n) : m_int(n) {}
private:
	int m_int;
};


struct MyAggregate
{
	int myInt;
	char myChar;
};

struct MyAggregate2
{
	int myInt;
	char myChar = 'Z';
};


int mainInitialization()
{
	int i = 5;
	MyClass mc1{ i };
	MyClass mc2 = mc1;
	int i2 = mc2.get_int();

	try {
		throw MyException(); 
	}
	catch (MyException ex)
	{
		cout << ex.what();
	}

	MyAggregate agg1{ 1, 'c' };
	MyAggregate2 agg2{ 2 };
	cout << "agg1: " << agg1.myChar << ": " << agg1.myInt << endl;
	cout << "agg2: " << agg2.myChar << ": " << agg2.myInt << endl;

	int myArr1[]{ 1,2,3,4 };
	int myArr2[3] = { 5, 6, 7 };
	int myArr3[5] = { 8, 9, 10 };
	cout << "myArr1: ";
	for (int i : myArr1)
	{
		cout << i << " ";
	}

	return 0;
}