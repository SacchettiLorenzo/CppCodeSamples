#include <iostream>
using namespace std;

#define length 8

void sort(int* array) {
	for (size_t i = 0; i < length-1; i++)
	{
		int k = i;
		for (size_t j = i+1; j < length; j++)
		{
			if (array[k] > array[j]) {
				k = j;
			}
		}
		int tmp = array[i];
		array[i] = array[k];
		array[k] = tmp;
	}
}

int main()
{
	int array[length] = { 7,4,1,8,2,3,6,5 };
	sort(array);

	for (size_t i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}


