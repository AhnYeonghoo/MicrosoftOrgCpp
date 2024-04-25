#include <iostream>
#include <string>

class MyClass
{
public:
	int num;
	std::string name;
	void print()
	{
		std::cout << name << ": " << num << std::endl;
	}
};

void func_A(MyClass* mc)
{
	mc->num = 3;
}

void func_B(MyClass mc)
{
	mc.num = 21;
	std::cout << "Local copy of mc: ";
	mc.print();
}

void func(int arr[], int length)
{
	size_t test = sizeof(arr);
	for (int i = 0; i < length; i++)
	{
		std::cout << arr[i] << " ";
	}
}

int mainPointer()
{
	MyClass* pmc = new MyClass{ 108, "Nick" };
	std::cout << pmc << std::endl;

	MyClass mc = *pmc;
	MyClass* pcopy = &mc;
	
	pmc->print();


	return 0;
}