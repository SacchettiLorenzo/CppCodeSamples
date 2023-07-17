

#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <stdexcept>

using namespace std;

void matrixMultiplication();
void squareMatrixMultiplication();
void initMatrix(int*a, int*b,int*c,int n);
void initMatrix(int* a, int* b, int* c, int n, int m, int p);
void printMatrix(int* t, int n);
void printMatrix(int* t, int a, int b);

int main()
{
    srand(static_cast<unsigned int>(time(0)));
	//squareMatrixMultiplication();

	matrixMultiplication();
	

}

void matrixMultiplication(){
	//matrix with form a[M][N]  e b[N][P]
	int n = 1 << 2; //4
	int m = 1 << 3; //8
	int p = 1 << 2; //4

	size_t bytesA = n * m * sizeof(int);
	size_t bytesB = n * p * sizeof(int);
	size_t bytesC = m * p * sizeof(int);

	int* a, * b, * c;

	a = (int*)malloc(bytesA);
	b = (int*)malloc(bytesB);
	c = (int*)malloc(bytesC);
	
	initMatrix(a, b, c, n,m,p);

	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < p; j++)
		{

			int temp = 0;
			for (size_t k = 0; k < n; k++)
			{
				temp += (a[i * m + k] * b[k * n + j]);
			}
			c[i * m + j] = temp;
		}
	}

	printMatrix(c, m, p);

	
	
}

void squareMatrixMultiplication() {
	
	int n = 1 << 3;

	size_t bytes = n * n * sizeof(int);

	int* a, * b, * c;

	a = (int*)malloc(bytes);
	b = (int*)malloc(bytes);
	c = (int*)malloc(bytes);

	initMatrix(a, b, c, n);

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			
			register int temp = 0;
			for (size_t k = 0; k < n; k++)
			{
				temp += a[i * n + k] * b[k * n + j];
			}
			c[i * n + j] = temp;
		}
	}

	printMatrix(c, n);
}



void initMatrix(int* a, int* b, int* c,int n) {
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			a[i * n + j] = rand() % 100; 
			b[i * n + j] = rand() % 100;
			c[i * n + j] = 0;
		}
	}

	printMatrix(a, n);
	printMatrix(b, n);
}

void initMatrix(int* a, int* b, int* c, int n, int m, int p) {
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			a[i * m + j] = rand() % 100;
			
		}
	}

	printMatrix(a, m, n);

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < p; j++)
		{
			
			b[i * n + j] = rand() % 100;
			
		}
	}

	printMatrix(b, n, p);

	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < p; j++)
		{
			c[i * m + j] = 0;
		}
	}

	printMatrix(c, m, p);
}

void printMatrix(int* t, int n) {
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			cout << t[i * n + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printMatrix(int* t, int a, int b) {
	for (size_t i = 0; i < a; i++)
	{
		for (size_t j = 0; j < b; j++)
		{
			cout << t[i * a + j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}

