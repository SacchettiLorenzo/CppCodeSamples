#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//work with varaiable length array
// 
//int binomialBottUp(int n, int k) {
//	int C[n+1][k+1]; //
//	for (size_t k = 0; k < 7; k++)
//	{
//		for (size_t l = 0; l < 5; l++)
//		{
//			C[k][l] = 0;
//		}
//		
//	}
//	int i;
//	int j;
//	for (i = 0; i <= n; i++) {
//		for (j = 0; j <= min(i, k); j++) {
//			if (j == 0 || j == i) {
//				C[i][j] = 1;
//			}
//			else {
//				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
//			}
//		}
//
//		for (size_t k = 0; k < 7; k++)
//		{
//			for (size_t l = 0; l < 5; l++)
//			{
//				printf("%d ", C[k][l]);
//			}
//			printf("\n");
//		}printf("\n");
//
//	}
//	return C[n][k];
//}

int binomialNoMem(int n, int k) {
	int res = 1;
	for (size_t i = 1; i <= k; i++)
	{
		res = (res * (n - i + 1)) / i;
	}
	return res;
}

int main() {
	printf("%d", binomialBottUp(6, 4));
}