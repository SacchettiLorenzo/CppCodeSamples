#include "Heap.h"

int Parent(int i)
{
	if (i != 0) {
		return i / 2;
	}
}

int Left(std::vector<int>* vec, int i)
{
	if (2 * i <= (*vec).size()) {
		return 2 * i;
	}
	else {
		return i;
	}
}

int Right(std::vector<int>* vec , int i)
{
	if ((2 * i) + 1 <= (*vec).size()) {
		return (2 *i)+1;
	}
	else {
		return i;
	}
}

void insert(std::vector<int>* vec, int x)
{
	(*vec).resize((*vec).size() + 1);
	int i = (*vec).size()-1;
	(*vec)[i] = x;
	while (i > 0 && (*vec)[Parent(i)] < (*vec)[i])
	{
		int tmp = (*vec)[i];
		(*vec)[i] = (*vec)[Parent(i)];
		(*vec)[Parent(i)] = tmp;

		i = Parent(i);
	}
}

void extract(std::vector<int>* vec)
{
	(*vec)[0] = (*vec)[(*vec).size() - 1];
	(*vec).resize((*vec).size() - 1);
	heapify(vec, 0);
}

void heapify(std::vector<int>* vec, int i)
{
	int largest;

	if (Left(vec, i) <= (*vec).size() - 1 && (*vec)[Left(vec, i)] > (*vec)[i]) {
		largest = Left(vec, i);
	}
	else {
		largest = i;
	}

	if (Right(vec, i) <= (*vec).size() - 1 && (*vec)[Right(vec, i)] > (*vec)[largest]) {
		largest = Right(vec, i);
	}

	if (largest != i) {
		std::swap((*vec)[i], (*vec)[largest]);
		heapify(vec, largest);
	}
}

