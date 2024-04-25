#include <iostream>
using namespace std;

int mainAuto()
{
	int count = 10;
	int& countRef = count;
	auto myAuto = countRef;

	countRef = 11;
	cout << count << " ";

	myAuto = 12;
	cout << count << endl;

	auto A = { 1, 2 };
	auto B = { 3 };
	auto C{ 4 };
	

	return 0;
}