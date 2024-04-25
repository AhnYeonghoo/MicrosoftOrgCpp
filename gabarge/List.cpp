#include <iostream>
#include <list>

template<typename T>
void print_list(std::list<T>& lst)
{
	std::cout << "[ ";
	for (const auto& elem : lst)
	{
		std::cout << elem << " ";
	}
	std::cout << "]" << std::endl;
}


int mainList()
{
	std::list<int> lst;

	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);

	for (std::list<int>::iterator itr = lst.begin();
		itr != lst.end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}

	std::cout << "dddd------dddd" << std::endl;
	return 0;
}