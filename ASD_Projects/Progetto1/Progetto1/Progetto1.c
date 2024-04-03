#include "Generic_data_manipulation.h"

void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

int com(int* a, int* b) {
	if (*a < *b)return -1;
	if (*a == *b)return 0;
	if (*a > *b)return 1;
}

//int com(double* a, double* b) {
//	if (*a < *b)return -1;
//	if (*a == *b)return 0;
//	if (*a > *b)return 1;
//}


int main()
{
	FILE* input = NULL;
	FILE* output = NULL;
	errno_t error;

	error = fopen_s(&input, "C:\\Users\\Lorenzo\\Desktop\\subset.csv", "r");
	error = fopen_s(&output, "C:\\Users\\Lorenzo\\Desktop\\result.csv", "a");
	//Dataset* dataset = GDM.new_Dataset(4,1000, &load_element_as_int, &load_element_as_char_array, &load_element_as_int, &load_element_as_double);
	//GDM.load_from_file(input, dataset);
	sort_records(input, output, 2, 1);

	
	/*int array[32] = { 7,4,1,8,2,3,6,5,7,4,1,8,2,3,6,5,7,4,1,8,2,3,6,5,7,4,1,8,2,3,6,5 };
	quick_sort_void(array, 0, 31, sizeof(int), com);
	merge_sort_void(array, 0, 31, sizeof(int), com);
	for (size_t i = 0; i < 31; i++)
	{
		printf("%d\n", array[i]);
	}*/
	
	
	GDM.sorting_fields = 2;
	//GDM.mergeSort(dataset, dataset->last_inserted, dataset->_Struct_size, &com);
	//GDM.quickSort(dataset, dataset->last_inserted, dataset->_Struct_size, &com);

	//TODO: move this to a dedicated function
	/*for (size_t i = 0; i < dataset->size; i++) {
		for (size_t j = 0; j < dataset->_Struct_size; j++)
		{
			switch (dataset->struct_type[j])
			{
			case T_int:
				fprintf(output, "%d", dataset->rows[i].fields[j].data.n);
				break;
			case T_string:
				fprintf(output, "%s", dataset->rows[i].fields[j].data.s);
				break;
			case T_double:
				fprintf(output, "%f", dataset->rows[i].fields[j].data.d);
				break;
			default:
				break;
			}
			if (j < dataset->_Struct_size - 1) {
				fprintf(output, "%s", ",");
			}
		}
		fprintf(output, "\n", "\0");
	}*/

	/*for (size_t i = 0; i < 20; i++)
	{
		printf("%d\n",dataset->rows[i].fields[GDM.sorting_fields].data.n);
	}*/
	//dataset->rows[0].fields->data.n
}




