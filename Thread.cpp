#include <iostream>
#include <string>
#include <map>

std::string download(std::string url)
{
	return "dD";
}
int mainThreadConcept()
{
	int bef = 1, cur = 1;
	for (int i = 0; i < 98; i++)
	{
		int temp = cur;
		cur = cur + bef;
		bef = temp;
	}

	std::cout << "F100: " << cur << std::endl;

	std::map<std::string, std::string> url_and_content;

	for (auto itr = url_and_content.begin(); itr != url_and_content.end();
		++itr)
	{
		const std::string& url = itr->first;

		itr->second = download(url);
	}


	return 0;
}