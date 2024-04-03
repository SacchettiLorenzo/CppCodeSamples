#include <iostream>
using namespace std;

#define length 8

int partition(int* array, int lo, int hi) {
	int pivot = array[hi];
	int index = lo - 1;

	for (size_t j = lo; j <= hi - 1; j++)
	{
		if (array[j] <= pivot) {
			index++;
			int tmp = array[index];
			array[index] = array[j];
			array[j] = tmp;
		}
	}

	index++;
	int tmpb = array[index];
	array[index] = array[hi];
	array[hi] = tmpb;
	return index;
}

void sort(int* array, int i, int j) {
	if (i >= j || i < 0) {
		return;
	}
		int p = partition(array,i,j);
		sort(array, i, p-1);
		sort(array, p+1, j);

}



int main()
{
	int array[length] = { 7,4,1,8,2,3,6,5 };
	sort(array, 0, length - 1);

	for (size_t i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}


