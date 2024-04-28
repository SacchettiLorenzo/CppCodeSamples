#include "Generic_data_manipulation.h"
#include "UnitTest.h"

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

    input = fopen("records.csv", "r");
    output = fopen("result.csv", "a");
    Dataset* dataset = GDM.new_Dataset(4, 20000000, &load_element_as_int, &load_element_as_char_array, &load_element_as_int, &load_element_as_double);
    GDM.load_from_file(input, dataset);

    GDM.sorting_fields = 0;
    GDM.mergeSort(dataset, dataset->last_inserted, dataset->_Struct_size, GDM.default_int_sort_function);

    UT.assert_true(dataset->rows[1].fields[GDM.sorting_fields].data.n > dataset->rows[0].fields[GDM.sorting_fields].data.n);

    UT.assert_true(dataset->rows[1000].fields[GDM.sorting_fields].data.n > dataset->rows[999].fields[GDM.sorting_fields].data.n);
}




