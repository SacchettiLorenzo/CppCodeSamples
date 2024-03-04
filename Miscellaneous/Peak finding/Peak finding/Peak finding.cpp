#include <iostream>
#include <stdlib.h> 

using namespace std;

void initArray(int*, int);
void peekFinding(int*, int); //find all peaks
void peekFindingDivide(int*, int, int); //find first peak
void peekFinding2D(int*, int);

const int LENGTH = 10;
int set[LENGTH];
int step = 0;

int main()
{
	srand(time(NULL));
	initArray(set, LENGTH);
	step = 0;
	peekFinding(set, LENGTH);
	cout << "Step: " << step << endl;
	step = 0;
	peekFindingDivide(set, 0, LENGTH - 1);
	cout << "Step: " << step << endl;
}

void initArray(int* set, int length) {
	for (size_t i = 0; i < length; i++)
	{
		set[i] = rand() % 100;
		cout << set[i] << " ";
	}
	cout << endl;
}

void peekFinding(int* set, int length) {
	for (size_t i = 0; i < length; i++)
	{
		if (set[i - 1] <= set[i] && set[i] >= set[i + 1]) {
			cout << set[i] << " ";
		}
		step++;
	}
}

void peekFindingDivide(int* set, int i, int j) {
	int p = (i + j) / 2;
	step++;

	if ((set[p - 1] <= set[p]) && (set[p] >= set[p + 1])) {
		cout << set[p] << " ";

	}
	else {

		if (set[p - 1] > set[p]) {
			peekFindingDivide(set, i, p - 1);

		}
		else {
			peekFindingDivide(set, p + 1, j);
		}
	}

}


void peekFinding2D(int* set, int length) {

}