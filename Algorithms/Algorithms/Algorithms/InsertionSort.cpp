#include <iostream>
using namespace std;

#define length 8

/**
 * @brief insertion sort
 * 
 * @param array 
 * @pre
 * @post
 * @invariant  array[0..i-1] is sorted, array[0..n-1] is not sorted
 * @details for each element in the unsorted part array, look for the right spot to go in the sorted portion of the array.
 * 			the element in the sorted portion are shifted to make room for the new element
 * 			worst case is O(n^2) and the best case is W(n) this algorithm is optimal if the array in almost sorted
 */
void sort(int* array) {
	int key;
	int j;
	for (size_t i = 1; i < length; i++)
	{
		key = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
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


