#include "Generic_data_manipulation.h"

void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

int magg(Var a, Var b) {
	if (a.data.n > b.data.n) {
		return 1;
	}

	if (a.data.n == b.data.n) {
		return 0;
	}
	
	if (a.data.n < b.data.n) {
		return -1;
	}
}


int main()
{
	FILE* fp = NULL;
	errno_t error;

	error = fopen_s(&fp, "C:\\Users\\Lorenzo\\Desktop\\subset.csv", "r");
	Dataset* dataset = GDM.new_Dataset(4,20000001, &load_element_as_int, &load_element_as_char_array, &load_element_as_int, &load_element_as_double);
	GDM.load_from_file(fp, dataset);
	
	//dataset->rows[0].fields->data.n
	merge_sort(dataset, dataset->last_inserted, sizeof(dataset->rows->fields->data), &magg);
}

void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*,const void*)) {
	int res = comparator(((Dataset*)base)->rows[0].fields[0], ((Dataset*)base)->rows[1].fields[0], 1, compar);
	printf("%d\n", res);
}


