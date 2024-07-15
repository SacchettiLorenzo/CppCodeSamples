#include <iostream>
#include <stdlib.h> 

using namespace std;

void initArray(int*, int);
void peakFinding(int*, int); //find all peaks
void peakFindingDivide(int*, int, int); //find first peak
void peakFinding2D(int*, int);
void peakFindMax(int* set, int length);

const int LENGTH = 10;
int set[LENGTH];
int step = 0;

int main()
{
	srand(time(NULL));
	initArray(set, LENGTH);
	step = 0;
	peakFinding(set, LENGTH);
	cout << "Step peak finding: " << step << endl;
	step = 0;
	peakFindingDivide(set, 0, LENGTH - 1);
	cout << "Step peak finding divide: " << step << endl;
	step = 0;
	peakFindMax(set, LENGTH);
	cout << "Step peak find max: " << step << endl;
}

/**
 * @brief init the array with random values
 * 
 * @param set pointer to integer array
 * @param length length of the array
 * @pre length>0
 * @post create a random integer array
 */
void initArray(int* set, int length) {
	for (size_t i = 0; i < length; i++)
	{
		set[i] = rand() % 100;
		cout << set[i] << " ";
	}
	cout << endl;
}

/**
 * @brief find all the peaks in a set of integer
 * 
 * @param set pointer to integer array
 * @param length length of the array
 * @pre length>0
 * @post find all the peaks in an array
 */
void peakFinding(int* set, int length) {
	for (size_t i = 0; i < length; i++)
	{
		if (set[i - 1] <= set[i] && set[i] >= set[i + 1]) {
			cout << set[i] << " ";
		}
		step++;
	}
}

/**
 * @brief find all the peaks in a set of integer using recursive calls
 * 
 * @param set pointer to integer array
 * @param i 
 * @param j 
 * @pre i>=0 j>=0
 * @post find all the peaks in an array
 */
void peakFindingDivide(int* set, int i, int j) {
	int p = (i + j) / 2;
	step++;

	if ((set[p - 1] <= set[p]) && (set[p] >= set[p + 1])) {
		cout << set[p] << " ";

	}
	else {

		if (set[p - 1] > set[p]) {
			peakFindingDivide(set, i, p - 1);

		}
		else {
			peakFindingDivide(set, p + 1, j);
		}
	}

}

/**
 * @brief find the highest peak in the array
 * 
 * @param set pointer to integer array
 * @param length length of the array
 * @pre length>0
 * @post find the highest peak
 */
void peakFindMax(int* set, int length) {
    int max = 0;
for (size_t i = 0; i < length; i++)
	{
		if(set[i] > set[max]){
            max = i;
        }
		step++;
	}
    cout << set[max] << endl;
}

void peakFinding2D(int* set, int length) {

}