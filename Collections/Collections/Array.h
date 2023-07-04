#include <iostream>
using namespace std;


void MonodimensionalArray();
void BidimensionalArray();
void MultidimensionalArray();
void DynamicAllocation();
void ArraySize();
void FindSize1(int arr[]);
void FindSize2(int(&arr)[10]);
template <size_t n>
void FindSize3(int(&arr)[n]);
template <typename T, size_t n>
void FindSizeGeneric(T (&arr)[n]);
