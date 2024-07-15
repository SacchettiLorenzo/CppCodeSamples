#include <iostream>
using namespace std;

#define length 8

/**
 * @brief selection sort
 * 
 * @param array 
 * @pre the array shold be not empty
 * @post sort distructively the given array
 * @invariant array[0..i-1] is sorted, array[0..n-1] is not sorted
 * @details for each element it check if avery other element is greater or smaller so the 
 * 			worst case is O(n^2) and the best case is W(n^2) this algorithm is not optimal
 */
void sort(int* array) {
	for (size_t i = 0; i < length-1; i++)
	{
		int k = i;
		//search the greatest
		for (size_t j = i+1; j < length; j++)
		{
			if (array[k] > array[j]) {
				k = j;
			}
		}
		//smap
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


