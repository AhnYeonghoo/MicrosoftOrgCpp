#include <iostream>
#include <thread>
using std::thread;

void func1()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Thread 1 working \n";
	}
}

void func2()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Thread 2 working \n";
	}
}

void func3()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Thread 3 working \n";
	}
}

int mainThread2()
{
	thread t1(func1);
	thread t2(func2);
	thread t3(func3);
	t1.join();
	t2.join();
	t3.join();

	return 0;
}