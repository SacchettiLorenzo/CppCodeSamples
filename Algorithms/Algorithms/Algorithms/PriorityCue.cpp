#include <iostream>
#include "Heap.h"


/*this example of priority cue use integer
it is possible to use any kind of type but
the integer should be removed in exchange for
a property of the specifi type instace(new_key)
*/
int maximum(std::vector<int> vec) {
	return vec[0];
 }

int extract_max(std::vector<int> vec) {
	int max = maximum(vec);
	extract(&vec);
	return max;
}

void heap_increase(std::vector<int>* vec, int index, int new_key) {
	if (new_key > (*vec)[index]) {
		(*vec)[index] = new_key;
		while (index > 0 && (*vec)[Parent(index)] < (*vec)[index]) {
			std::swap((*vec)[index], (*vec)[Parent(index)]);
			index = Parent(index);
		}
	}
}



int main()
{
	std::vector<int> vec;

	insert(&vec, 10);
	insert(&vec, 20);
	insert(&vec, 15);
	insert(&vec, 1);
	insert(&vec, 16);
	insert(&vec, 17);
	insert(&vec, 21);
	insert(&vec, 8);
	insert(&vec, 30);

	heap_increase(&vec, 1, 40);
	

	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}