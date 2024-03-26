#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define OS 'w'
#define bufferSpan 16
#define log 'log'

#if OS == 'w'
size_t getline(char** lineptr, size_t* n, FILE* stream);
#endif

typedef enum _Type { T_int, T_string, T_double, T_float , T_bool, T_struct} Type;

typedef struct _Var {
	Type type; 
	union { int n; char* s; double d; float f; bool b; struct str; } data;
} Var;

typedef struct _Struct {
	Var* fields;
}Struct;

typedef struct _Dataset {
	int _Struct_size;
	int last_inserted;
	Struct* rows;
	int expected_rows;
} Dataset;

typedef int (*FuncPtr)(Var,Var);

int comparator(Var first, Var second, int num_comparation, ...) {
	va_list ptr;
	va_start(ptr, num_comparation);
	int result = 0;
	
	for (size_t i = 0; i < num_comparation; i++)
	{
		FuncPtr func_ptr =  va_arg(ptr, FuncPtr);
		result = (func_ptr)(first, second);
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

void new_record_allocation_function(Dataset* dataset);
void load_element_as_int(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_char_array(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_double(char** lineptr, int i, int j, int column, Dataset* dataset);
void load_element_as_float(char** lineptr, int i, int j, int column, Dataset* dataset);

typedef void (*_Struct_functions)(char**, int, int, int, Dataset*);
_Struct_functions* functions = NULL;

Dataset* new_Dataset(int struct_size, int expected_rows, ...);
void laod_from_file(FILE* fp, Dataset* dataset);

struct generic_data_manipulation {
	int length;
	Dataset* dataset;
	Dataset* (*new_Dataset)(int,int,...);
	void(*load_from_file)(FILE* fp, Dataset* dataset);
	void(*new_record_allocation_function)(Dataset* dataset);
}GDM = { 0,{NULL},&new_Dataset, &laod_from_file, &new_record_allocation_function};

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
		if (GDM.dataset != NULL) {
			GDM.length++;
			(GDM.dataset + (GDM.length - 1))->_Struct_size = struct_size;
			(GDM.dataset + (GDM.length - 1))->last_inserted = 0;
			(GDM.dataset + (GDM.length - 1))->expected_rows = expected_rows;
			return GDM.dataset + (GDM.length - 1);
		}
	}
	else {
		//realloc
	}
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

	//TODO: check if flaceholder is empty
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

	//TODO: check if flaceholder is empty
	d_placeholder = strtof(placeholder, NULL);

	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].type = T_double;
	(*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.f = d_placeholder;

#if log == 'log'
	printf("%f\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d);
#endif
}

void load_element_as_boolean(){}

void load_element_as_struct(){}

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

#if OS == 'w'

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

#endif