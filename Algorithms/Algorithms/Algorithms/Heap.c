#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int left(int i, int heap_length) {
	if ((2 * i) + 1 < heap_length) {
		return (2 * i) + 1;
	}
	else {
		return i;
	}
}

int right(int i, int heap_length) {
	if ((2 * i) + 2 < heap_length) {
		return (2 * i) + 2;
	}
	else {
		return i;
	}
}

int parent(i) {
	if ((i - 1) / 2 > 0) {
		return (i - 1) / 2;
	}
	else {
		return i;
	}
}

void maxHeapify(int heap[], int i, int heap_length) {
	
	int index_largest = i; 
	if (heap[left(i, heap_length)] > heap[index_largest]) {
		index_largest = left(i, heap_length);
	}

	if (heap[right(i, heap_length)] > heap[index_largest]) {
		index_largest = right(i, heap_length);
	}

	
	if (i != index_largest) {
		int tmp = heap[i];
		heap[i] = heap[index_largest];
		heap[index_largest] = tmp;
		maxHeapify(heap, index_largest, heap_length);
	}
}

void buildMaxHeap(int arr[], int N) {
	int startIdx = (N / 2) - 1;
	//a partire dal primo elemento non foglia andando a ritroso
	
	for (int i = startIdx; i >= 0; i--) {
		maxHeapify(arr, i, N);
	}
}


int main() {
	int heap[10] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15 };
	printf("%d\n", heap[left(0,10)]);
	printf("%d\n", heap[right(0, 10)]);
	for (size_t i = 0; i < 10; i++)
	{
		printf("%d ", heap[i]);
	}
	printf("\n");
	//maxHeapify(heap, 0, 10);
	buildMaxHeap(heap, 10);
	for (size_t i = 0; i < 10; i++)
	{
		printf("%d ", heap[i]) ;
	}
}