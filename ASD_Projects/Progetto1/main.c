#include "Generic_data_manipulation.h"


/* void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

int com(int* a, int* b) {
	if (*a < *b)return -1;
	if (*a == *b)return 0;
	if (*a > *b)return 1;
} */

//int com(double* a, double* b) {
//	if (*a < *b)return -1;
//	if (*a == *b)return 0;
//	if (*a > *b)return 1;
//}


int main()
{
	FILE* input = NULL;
	FILE* output = NULL;

    input = fopen("/home/lorenzo/Documents/C/CppCodeSamples/ASD_Projects/Progetto1/records.csv", "r");
    output = fopen("result.csv", "a");
	sort_records(input, output, 3, 2);

	/*TODO: check with quick_sort()*/
	/*int array[32] = { 7,4,1,8,2,3,6,5,7,4,1,8,2,3,6,5,7,4,1,8,2,3,6,5,7,4,1,8,2,3,6,5 };
	quick_sort_void(array, 0, 31, sizeof(int), com);
	merge_sort_void(array, 0, 31, sizeof(int), com);
	for (size_t i = 0; i < 31; i++)
	{
		printf("%d\n", array[i]);
	}
    */

}




