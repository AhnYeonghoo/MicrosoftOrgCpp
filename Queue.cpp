#include <iostream>
#include <string>

#define MAX_SIZE (10000)
using namespace std;

template<typename T>
class Queue
{
private:
	T data[MAX_SIZE];
	int front;
	int back;

public:
	Queue()
	{
		front = -1;
		back = -1;
	}
	~Queue() {}
	
	void Push(T input)
	{
		this->data[this->back + 1] = input;
		this->back += 1;
		return;
	}

	T Pop()
	{
		T res = this->data[this->front + 1];
		this->front+=1;
		return res;
	}

	int Size()
	{
		return this->back - this->front;
	}

	bool Empty()
	{
		return this->Size() == 0 ? true : false;
	}

	T Front()
	{
		T res = this->data[this->front + 1];
		return res;
	}

	T Back()
	{
		T res = this->data[this->back];
		return res;
	}

};