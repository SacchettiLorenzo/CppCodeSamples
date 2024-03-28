#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define bufferSpan 16
//#define log 'log'


typedef enum _Type { T_int, T_string, T_double, T_float , T_bool, T_struct, T_dataset} Type;

typedef struct _Var {
	Type type; 
	union { int n; char* s; double d; float f; bool b; void* v; } data;
} Var;

typedef struct _Struct {
	Var* fields;
}Struct;

/**
Support variable
*/
Struct* tmp;

typedef struct _Dataset {
	Type type;
	int _Struct_size;
	int last_inserted;
	Struct* rows;
	int expected_rows;
} Dataset;

/**
Pointers to functions
*/
typedef void (*_Struct_functions)(char**, int, int, int, Dataset*);
_Struct_functions* functions = NULL; //TODO: move inside new_Dataset()
typedef int (*FuncPtr)(const void*,const void*);

Dataset* new_Dataset(int struct_size, int expected_rows, ...);
void laod_from_file(FILE* fp, Dataset* dataset);
size_t getline(char** lineptr, size_t* n, FILE* stream);
void new_record_allocation_function(Dataset* dataset);


void load_element_as_int(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_char_array(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_double(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_float(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_boolean(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_struct(char** lineptr, int i, int j, int column, Dataset* dataset);

int comparator(Var first, Var second, int num_comparation, ...);

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void merge_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*));

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void quick_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*));

static struct generic_data_manipulation {
	int length;
	size_t sorting_fields;
	Dataset* dataset;
	Dataset* (*new_Dataset)(int,int,...);
	void(*load_from_file)(FILE* fp, Dataset* dataset);
	void(*new_record_allocation_function)(Dataset* dataset);
	int(*comparator)(Var, Var, int, ...);
	void(*SortRecords)(FILE*, FILE*, size_t, size_t);
	void(*mergeSort)(void*, size_t, size_t, int(*)(const void*, const void*)); 
	void(*quickSort)(void*, size_t, size_t, int(*)(const void*, const void*)); 
}GDM = { 0,0,{NULL},&new_Dataset, &laod_from_file, &new_record_allocation_function,&comparator,&sort_records,&merge_sort,&quick_sort};


Dataset* new_Dataset(int struct_size, int expected_rows,... /*variadic function for the functions*/) {
	functions = (_Struct_functions*)malloc(struct_size * sizeof(_Struct_functions*));

	if (functions == NULL) {
		//TODO: do something
	}

	va_list ptr;
	va_start(ptr, struct_size);
	for (size_t i = 0; i < struct_size; i++)
	{
		functions[i] = va_arg(ptr, _Struct_functions);
	}
	va_end(ptr);
	if (GDM.length == 0) {
		GDM.dataset = (Dataset*)malloc(sizeof(Dataset));
		GDM.length++;
		
	}
	else {
		GDM.dataset = (Dataset*)realloc(GDM.dataset, GDM.length * sizeof(Dataset)); //TODO: check if works
		//realloc
	}

	if (GDM.dataset + (GDM.length - 1) != NULL) {
		(GDM.dataset + (GDM.length - 1))->_Struct_size = struct_size;
		(GDM.dataset + (GDM.length - 1))->last_inserted = 0;
		(GDM.dataset + (GDM.length - 1))->expected_rows = expected_rows;
		(GDM.dataset + (GDM.length - 1))->type = T_dataset;
		return GDM.dataset + (GDM.length - 1);
	}
}

void laod_from_file(FILE* fp, Dataset* dataset) {
	char* line = NULL;
	size_t len = 0;
	line = (char*)malloc(len * sizeof(char));
	int read;

	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		int left = 0, right = 0;
		int columns_counter = 0;

		
		GDM.new_record_allocation_function(dataset);

		for (size_t i = 0; i < read; i++)
		{
			if ((line[i]) == ',') {
				right = i - 1;
				functions[columns_counter](&line, left, right, columns_counter, dataset);
				left = i + 1;
				columns_counter++;
			}
		}
		right = read;
		functions[columns_counter](&line, left, right, columns_counter, dataset);

	}
}

size_t getline(char** lineptr, size_t* n, FILE* stream) {
	char* bufptr = NULL;
	char* p = bufptr;
	size_t size;
	int c;
	int char_counter = 0;

	if (lineptr == NULL) {
		return -1;
	}
	if (stream == NULL) {
		return -1;
	}
	if (n == NULL) {
		return -1;
	}
	bufptr = *lineptr;
	size = *n;

	c = fgetc(stream);
	if (c == EOF) {
		return -1;
	}
	if (bufptr == NULL) {
		bufptr = (char*)malloc(bufferSpan);
		if (bufptr == NULL) {
			return -1;
		}
		size = bufferSpan;
	}
	p = bufptr;
	while (c != EOF) {
		if ((p - bufptr) > (size - 1)) {
			size = size + bufferSpan;
			bufptr = (char*)realloc(bufptr, size);
			if (bufptr == NULL) {
				return -1;
			}
		}
		*p++ = c;
		if (c == '\n') {
			break;
		}
		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}

void new_record_allocation_function(Dataset* dataset) {

	if ((*dataset).last_inserted == 0) {
		(*dataset).rows = (Struct*)malloc((*dataset).expected_rows * sizeof(Struct));
	}

	//TODO: check if more  memory should be allocated for dataset.rows
	if ((*dataset).rows != NULL) {
		(*dataset).rows[(*dataset).last_inserted].fields = (Var*)malloc((*dataset)._Struct_size * sizeof(Var));
		(*dataset).last_inserted++;
	}
}

void load_element_as_int(char** lineptr, int i, int j, int column, Dataset* dataset) {

	int placeholder = 0;

	for (size_t index = i; index <= j; index++)
	{
		placeholder *= 10;
		placeholder += (int)(*lineptr)[index] - '0';
	}

	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].type = T_int;
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.n = placeholder;

#if log == 'log'
	printf("%d\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.n);
#endif 

}

void load_element_as_char_array(char** lineptr, int i, int j, int column, Dataset* dataset) {
	char* placeholder = (char*)malloc(((j - i) + 1 + 1) + sizeof(char));
	if (placeholder == NULL) {
		//TODO:do something
	}
	else {
		for (size_t index = i; index <= j; index++)
		{
			((char*)placeholder)[index - i] = (char)(*lineptr)[index];
		}

		((char*)placeholder)[j - i + 1] = '\0';
	}
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].type = T_string;
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.s = placeholder;

#if log == 'log'
	printf("%s\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.s);
#endif
}

void load_element_as_double(char** lineptr, int i, int j, int column, Dataset* dataset) {
	char* placeholder = (char*)malloc(((j - i) + 1) + sizeof(char));
	double d_placeholder = 0;
	if (placeholder == NULL) {
		//TODO:do something
	}
	else {
		for (size_t index = i; index <= j; index++)
		{
			((char*)placeholder)[index - i] = (char)(*lineptr)[index];
		}
	}

	if (placeholder == NULL) {
		//TODO:do something
	}
	d_placeholder = strtod(placeholder, NULL);
	
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].type = T_double;
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d = d_placeholder;

#if log == 'log'
	printf("%f\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d);
#endif
}

void load_element_as_float(char** lineptr, int i, int j, int column, Dataset* dataset) {
	char* placeholder = (char*)malloc(((j - i) + 1) + sizeof(char));
	float d_placeholder = 0;
	if (placeholder == NULL) {
		//TODO:do something
	}
	else {
		for (size_t index = i; index <= j; index++)
		{
			((char*)placeholder)[index - i] = (char)(*lineptr)[index];
		}
	}

	if (placeholder == NULL) {
		//TODO:do something
	}
	d_placeholder = strtof(placeholder, NULL);

	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].type = T_double;
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.f = d_placeholder;

#if log == 'log'
	printf("%f\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d);
#endif
}

void load_element_as_boolean(char** lineptr, int i, int j, int column, Dataset* dataset){}

void load_element_as_struct(char** lineptr, int i, int j, int column, Dataset* dataset){}

int comparator(Var first, Var second, int num_comparation, ...) {

	va_list ptr;
	va_start(ptr, num_comparation);
	int result = 0;

	for (size_t i = 0; i < num_comparation; i++)
	{
		FuncPtr func_ptr = va_arg(ptr, FuncPtr);
		result = (func_ptr)(&first.data, &second.data);

		if (result != 0) break;
	}

	va_end(ptr);

	if (result >= 1) {
		return 1;
	}

	if (result <= -1) {
		return -1;
	}

	return result;
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo){
	switch (algo)
	{
	case 1:
		//GDM.mergeSort
		break;
	case 2:
		//GDM.quickSort
	default:
		break;
	}
}

void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)){
if(((Dataset*)base)->type == T_dataset){
	 tmp = (Struct*)malloc(nitems * sizeof(Struct*));
	 merge_sort_Dataset((Dataset*)base, 0, nitems-1, compar);
	}else{
		//use compar function
	}
}

void merge_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*)) {
	int middle = (i + j) / 2;
	if (i < j) {
		merge_sort_Dataset(dataset, i, middle, compar);
		merge_sort_Dataset(dataset, middle + 1, j, compar);
	}

	int placeholder = 0;
	int left = i; //i
	int right = middle + 1; //j

	while (left <= middle && right <= j)
	{
		if(comparator(dataset->rows[left].fields[GDM.sorting_fields], dataset->rows[right].fields[GDM.sorting_fields],1,compar) == -1){
			tmp[placeholder] = dataset->rows[left];
			left++;
		}
		else {
			tmp[placeholder] = dataset->rows[right];
			right++;
		}
		placeholder++;
	}

	while (left <= middle)
	{
		tmp[placeholder] = dataset->rows[left];
		left++;
		placeholder++;
	}

	while (right <= j)
	{
		tmp[placeholder] = dataset->rows[right];
		right++;
		placeholder++;
	}

	for (size_t k = i; k <= j; k++)
	{
		dataset->rows[k] = tmp[k - i];
	}

}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)){
	
}

void quick_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*)) {

}