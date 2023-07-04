#include "Array.h"


void MonodimensionalArray() {
	int arr1[10]; //simple decleratrion of array of 10 elements
	int arr2[] = { 10, 20, 30, 40 }; // size of array depend on hggow many elements there are in the definition
	int arr3[6] = { 10, 20, 30, 40 }; // decleration with size and initialization 

	cout << "MonodimensionalArray arrays initialized" << endl;
}

void BidimensionalArray() {
	int arr1[10][10]; //simple decleratrion of array of 10x10 elements
	int arr2[3][4] = { 0, 1 ,2 ,3 ,4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 }; // The array will be filled in the definition order
	int arr3[3][4] = { {0,1,2,3}, {4,5,6,7}, {8,9,10,11} }; // same of arr2

	int arr4[3][4];
	for (int i = 0; i < 3; i++) {  //runtime definition with nested loops
		for (int j = 0; j < 4; j++) {
			 arr4[i][j] = i*j;
		}
	}

	cout << "BidimensionalArray arrays initialized" << endl;
}

void MultidimensionalArray() {
	int arr[5][5][5][5][5];
	int totalIteration = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				for (int t = 0; t < 5; t++)
				{
					for (int h = 0; h < 5; h++)
					{
						arr[i][j][k][t][h] = 1;
						totalIteration++;
					}
				}
			}
		}
	}
	cout << "Total iteration: " << totalIteration << endl;
}

void DynamicAllocation() {
	int length;
	cout << "inserisci la lunghezza dell'array" << endl;
	cin >> length;

	int* ptr; //pointer decleration

	ptr = new int[length]; // memory allocation 

	for (int i = 0; i < length; i++)
	{
		*(ptr + i) = 10 + i;		//definition of the value of the elements of the array
	}

	for (int i = 0; i < length; i++)
	{
		cout << *(ptr + i) << endl;
	}

	delete[] ptr; //release ptr memory
}


void ArraySize() {
	int arr[10];
	FindSize1(arr);
	FindSize2(arr);
	FindSize3(arr);
	float arr2[10];
	FindSizeGeneric(arr2);
}

void FindSize1(int arr[]) {
	cout << sizeof(arr) << endl;	//dimension of the arr pointer
}

void FindSize2(int(&arr)[10]) {
	cout << sizeof(arr) << endl;	// dimension of the array memory if the size is fixed
}

template <size_t n>
void FindSize3(int(&arr)[n]) {
	cout << sizeof(int)*n << endl;	// dimension of the array memory if the size isn't fixed
}

template <typename T, size_t n>
void FindSizeGeneric(T(&arr)[n]) {
	cout << sizeof(T) * n << endl;	//dimension of a generic array
}
