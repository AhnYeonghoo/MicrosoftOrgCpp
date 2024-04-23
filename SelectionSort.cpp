#include <iostream>

void selection_sort(int* arr, int n)
{
	int last = n - 1;
	for (int i = 0; i < n; i++)
	{
		int _max = 0;
		int _index = -1;
		for (int j = 0; j <= last; j++)
		{
			if (_max < arr[j])
			{
				_max = arr[j];
				_index = j;
			}
		}

		int temp = arr[last];
		arr[last] = arr[_index];
		arr[_index] = temp;
		last = last - 1;
	}
}