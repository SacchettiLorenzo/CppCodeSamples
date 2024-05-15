#include <iostream>
#include "Heap.h"
using namespace std;

void sort(std::vector<int>* vec) {
	std::vector<int> sorted;
	for (size_t i = (*vec).size()-1; i > 0; i--)
	{
		sorted.push_back((*vec)[0]);
		std::swap((*vec)[i], (*vec)[0]);
		if (i > 0) {
		(*vec).resize((*vec).size() - 1); //this should be resized only logically
		heapify(vec, 0);
		}

	}
	
	for (size_t i = 0; i < sorted.size(); i++)
	{
		(*vec).push_back(sorted[sorted.size() - 1 -i]);
	}
	/*this implementation use a temporary vector to store the sorted data because the 
	data structure lack of a heap-size parameter to be changed at will*/
}

int main()
{
	std::vector<int> vec;

	insert(&vec, 10);
	insert(&vec, 20);
	insert(&vec, 15);
	insert(&vec, 1);
	insert(&vec, 16);
	insert(&vec, 10);
	insert(&vec, 20);
	insert(&vec, 15);
	insert(&vec, 1);
	insert(&vec, 16);
	insert(&vec, 10);
	insert(&vec, 20);
	insert(&vec, 15);
	insert(&vec, 1);
	insert(&vec, 16);
	insert(&vec, 10);
	insert(&vec, 20);
	insert(&vec, 15);
	insert(&vec, 1);
	insert(&vec, 16);

	sort(&vec);

	for (size_t i = 0; i < vec.size()-1; i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}
