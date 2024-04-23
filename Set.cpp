#include <iostream>
#include <set>
#include <string>

template<typename T>
void print_set(std::set<T>& s)
{
	std::cout << "[ ";
	for (typename std::set<T>::iterator itr = s.begin(); itr != s.end();
		++itr)
	{
		std::cout << *itr << " ";
	}
	std::cout << " ] " << std::endl;
}

class Todo2
{
	int priority;
	std::string job_desc;

public:
	Todo2(int prioirty, std::string job_desc)
		: priority(priority), job_desc(job_desc) {}

	bool operator<(const Todo2& t) const
	{
		if (priority == t.priority)
		{
			return job_desc < t.job_desc;
		}
		return priority > t.priority;
	}

	friend std::ostream& operator<<(std::ostream& o, const Todo2& td);
};

std::ostream& operator<<(std::ostream& o, const Todo2& td)
{
	o << "[ 중요도: " << td.priority << "] " << td.job_desc;
	return o;
}
int mainSet()
{
	std::set<int> s;
	s.insert(10);
	s.insert(50);
	s.insert(20);
	s.insert(40);
	s.insert(30);

	std::cout << "순서대로 정렬돼서 나온다." << std::endl;
	print_set(s);

	auto itr = s.find(20);
	if (itr != s.end())
	{
		std::cout << "yes" << std::endl;
	}
	else
	{
		std::cout << "no" << std::endl;
	}

	std::cout << "25가 s의 원소인가요? " << std::endl;
	itr = s.find(25);
	if (itr != s.end())
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::set<Todo2> todos;

	todos.insert(Todo2(1, "농구하기"));
	todos.insert(Todo2(2, "농구2하기"));
	todos.insert(Todo2(1, "농구1하기"));
	todos.insert(Todo2(3, "농구3하기"));
	todos.insert(Todo2(2, "농구22하기"));

	print_set(todos);

	std::cout << "-----" << std::endl;
	std::cout << "숙제를 끝냈다면!" << std::endl;

	todos.erase(todos.find(Todo2(2, "농구2하기")));
	print_set(todos);
	return 0;
	 
}