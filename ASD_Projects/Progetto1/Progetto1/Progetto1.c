#include "Generic_data_manipulation.h"

void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

int com(int* a, int* b) {
	if (*a < *b)return -1;
	if (*a == *b)return 0;
	if (*a > *b)return 1;
}


int main()
{
	FILE* fp = NULL;
	errno_t error;

	error = fopen_s(&fp, "C:\\Users\\Lorenzo\\Desktop\\subset.csv", "r");
	Dataset* dataset = GDM.new_Dataset(4,20, &load_element_as_int, &load_element_as_char_array, &load_element_as_int, &load_element_as_double);
	GDM.load_from_file(fp, dataset);

	
	int array[8] = { 7,4,1,8,2,3,6,5 };
	
	

	GDM.sorting_fields = 2;
	GDM.mergeSort(dataset, dataset->last_inserted, dataset->_Struct_size, &com);

	for (size_t i = 0; i < 20; i++)
	{
		printf("%d\n",dataset->rows[i].fields[GDM.sorting_fields].data.n);
	}
	//dataset->rows[0].fields->data.n
}




