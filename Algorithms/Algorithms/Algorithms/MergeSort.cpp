#include <iostream>
using namespace std;

#define length 8

/**
 * @brief merge sort
 * 
 * @param array 
 * @param i 
 * @param j 
 * @pre
 * @post
 * @invariant
 * @details
 */
void sort(int* array, int i, int j) {
	int middle = (i + j) / 2;
	if (i < j) {
		sort(array, i, middle);
		sort(array, middle + 1, j);
	}
	int placeholder = 0; 
	int left = i; //i
	int right = middle + 1; //j
	int tmp[length]; 

	while (left <= middle && right <= j)
	{
		if (array[left] < array[right]) {
			tmp[placeholder] = array[left];
			left++;
		}
		else {
			tmp[placeholder] = array[right];
			right++;
		}
		placeholder++;
	}

	while (left <= middle)
	{
		tmp[placeholder] = array[left]; 
		left++;
		placeholder++;
	}

	while (right <= j)
	{
		tmp[placeholder] = array[right];
		right++;
		placeholder++;
	}


	for (size_t k = i; k <= j; k++)
	{
		array[k] = tmp[k-i];
	}

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


