#include <iostream>
#include <string>

#define MAX_SIZE (10000)
using namespace std;

template <typename T>
class Stack
{
private:
	T data[MAX_SIZE];
	int _top;

public:
	Stack()
	{
		_top = -1;
	}

	~Stack() {}

	void Push(T inputdata)
	{
		data[_top + 1] = inputdata;
		_top += 1;
	}

	T Pop()
	{
		T res = data[_top];
		_top -= 1;
		return res;
	}

	int Size()
	{
		return _top + 1;
	}

	bool Empty()
	{
		return Size() == 0 ? true : false;
	}

	T Top()
	{
		T res = data[_top];
		return res;
	}
};

int mainStack()
{
	ios_base::sync_with_stdio(false);
	cout.tie(0); cin.tie(0);

	Stack<int> s;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string com;
		cin >> com;
		if (com == "push")
		{
			int data;
			cin >> data;
			s.Push(data);
		}
		else if (com == "pop")
		{
			if (s.Empty())
			{
				cout << "-1\n";
			}
			else
			{
				cout << s.Pop() << "\n";
			}
		}
		else if (com == "size")
		{
			cout << s.Size() << endl;
		}
		else if (com == "empty")
		{
			cout << s.Empty() << endl;
		}
		else
		{
			if (s.Empty())
			{
				cout << "-1\n";
			}
			else
			{
				cout << s.Top() << endl;
			}
		}
	}

	return 0;
}