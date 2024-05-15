#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define bufferSpan 16
//#define log 1

/**
 * @brief Accepted types
 * 
 */
typedef enum _Type { T_int, T_string, T_double, T_float , T_bool, T_struct, T_void, T_dataset} Type;

/**
 * @brief A single variable
 * 
 */
typedef struct _Var {
	union { int n; char* s; double d; float f; bool b; void* v; } data;
} Var;

/**
 * @brief Array of variables of different type
 * 
 */
typedef struct _Struct {
	Var* fields;
}Struct;

/**
Support variable
*/
static Struct* tmp;
static void* tmp_void_sort; //mode this inside merge_sort_void

/**
 * @brief dataset containing rows of variables of different type and support informations
 * 
 */
typedef struct _Dataset {
	Type* struct_type;
	Type type;
	int _Struct_size;
	int last_inserted;
	int size;
	Struct* rows;
	int expected_rows;
} Dataset;

/**
Pointers to functions
*/
typedef void (*_Struct_functions)(char**, int, int, int, Dataset*);
static _Struct_functions* functions; //TODO: move inside new_Dataset() and check if work. recently removed "= NULL"
typedef int (*FuncPtr)(const void*,const void*);

/**
 * @brief Create and initialize a new dataset
 * 
 * @param struct_size the number of variables in a single row
 * @param expected_rows the number of expected rows in the dataset (for better memory management)
 * @param ... array of functions used to parse data from text
 * @return Dataset* 
 */
Dataset* new_Dataset(int struct_size, int expected_rows, ...);

/**
 * @brief load the data from the file into the dataset
 * 
 * @param fp pointer to a file
 * @param dataset pointer to a dataseet
 */
void laod_from_file(FILE* fp, Dataset* dataset);

/**
 * @brief read the file line by line
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param n 
 * @param stream pointer to file 
 * @return size_t number of char read in one single line
 */
size_t getline_(char** lineptr, size_t* n, FILE* stream);

/**
 * @brief add a new record to the dataset
 * 
 * @param dataset pointer to dataset
 */
void new_record_allocation_function(Dataset* dataset);

/**
 * @brief load the data from the file as integer
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param i starting position within the row for reading
 * @param j ending position within the row for reading
 * @param column the index of the element in the row
 * @param dataset pointer to dataset
 */
void load_element_as_int(char** lineptr, int i, int j, int column, Dataset* dataset);

/**
 * @brief load the data from the file as char array
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param i starting position within the row for reading
 * @param j ending position within the row for reading
 * @param column the index of the element in the row
 * @param dataset pointer to dataset
 */
void load_element_as_char_array(char** lineptr, int i, int j, int column, Dataset* dataset);

/**
 * @brief load the data from the file as double
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param i starting position within the row for reading
 * @param j ending position within the row for reading
 * @param column the index of the element in the row
 * @param dataset pointer to dataset
 */
void load_element_as_double(char** lineptr, int i, int j, int column, Dataset* dataset);

/**
 * @brief load the data from the file as float
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param i starting position within the row for reading
 * @param j ending position within the row for reading
 * @param column the index of the element in the row
 * @param dataset pointer to dataset
 */
void load_element_as_float(char** lineptr, int i, int j, int column, Dataset* dataset);

/**
 * @brief load the data from the file as boolean
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param i starting position within the row for reading
 * @param j ending position within the row for reading
 * @param column the index of the element in the row
 * @param dataset pointer to dataset
 * @note unimplemented
 */
void load_element_as_boolean(char** lineptr, int i, int j, int column, Dataset* dataset);

/**
 * @brief load the data from the file as struct
 * 
 * @param lineptr pointer to char* used to store the lines of the file
 * @param i starting position within the row for reading
 * @param j ending position within the row for reading
 * @param column the index of the element in the row
 * @param dataset pointer to dataset
 * @note unimplemented
 */
void load_element_as_struct(char** lineptr, int i, int j, int column, Dataset* dataset);

/**
 * @brief compare two variables of type Var with a list of comparing functions. 
 * If a comparing function does not provide a non 0 result (means first and second are equal) the next comparing funtion will be executed.
 * The provided function are executed in order thus decreasing the effectiveness of the last ones
 * 
 * @param first first variable to comapare
 * @param second second variable to compare
 * @param num_comparation number of comparing function available for execution
 * @param ... array of function of size num_comparation
 * @return int 
 */
int comparator(Var first, Var second, int num_comparation, ...);

/**
 * @brief compare to variable. the provided variables are treated as integer
 * 
 * @param a pointer to variable
 * @param b pointer to variable
 * @return int 
 */
int default_int_sort_function(const void* a,const void* b);

/**
 * @brief compare to variable. the provided variables are treated as float
 *
 * @param a pointer to variable
 * @param b pointer to variable
 * @return int
 */
int default_float_sort_function(const void* a,const void* b);

/**
 * @brief compare to variable. the provided variables are treated as double
 *
 * @param a pointer to variable
 * @param b pointer to variable
 * @return int
 */
int default_double_sort_function(const void* a,const void* b);

/**
 * @brief compare to variable. the provided variables are treated as string
 *
 * @param a pointer to variable
 * @param b pointer to variable
 * @return int
 */
int default_string_sort_function(const void* a,const void* b);


/**
 * @brief sort records with a given algorithm
 * 
 * @param infile pointer to file containing the dataset
 * @param outfile pointer to file for the output of the sorted data
 * @param field number of field in the dataset for each row
 * @param algo number of the algorithm. 1: merge sort 2: quick sort
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

/**
 * @brief use merge sort to sort the provided data
 * 
 * @param base pointer to the data to be sorted by
 * @param nitems number of items in the record
 * @param size number of element to sort (rows)
 * @param compar pointer to comparing function
 */
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief implementation of merge sort for the type Dataset
 * 
 * @param dataset pointer to dataset
 * @param i left index
 * @param j right index
 * @param compar pointer to comparing function
 */
void merge_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*));

/**
 * @brief implementation of merge sort for generic data
 * 
 * @param dataset pointer to dataset
 * @param i left index
 * @param j right index
 * @param compar pointer to comparing function
 */
void merge_sort_void(void* base, int i, int j, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief use quick sort to sort the provided data
 * 
 * @param base pointer to the data to be sorted by
 * @param nitems number of items in the record
 * @param size number of element to sort (rows)
 * @param compar pointer to comparing function
 */
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief implementation of quick sort for the type Dataset
 * 
 * @param dataset pointer to dataset
 * @param i left index
 * @param j right index
 * @param compar pointer to comparing function
 */
void quick_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*));

/**
 * @brief implementation of quick sort for generic data
 * 
 * @param dataset pointer to dataset
 * @param i left index
 * @param j right index
 * @param compar pointer to comparing function
 */
void quick_sort_void(void* base, int i, int j, size_t size, int (*compar)(const void*, const void*));


struct generic_data_manipulation {
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
	int(*default_int_sort_function)(const void*, const void*);
    int(*default_float_sort_function)(const void*, const void*);
    int(*default_double_sort_function)(const void*, const void*);
    int(*default_string_sort_function)(const void*, const void*);

};

/**
 * @brief object containing pointers for operating the library
 * 
 */
static struct generic_data_manipulation GDM = { 0,0,NULL,&new_Dataset, &laod_from_file, &new_record_allocation_function,&comparator,&sort_records,&merge_sort,&quick_sort,&default_int_sort_function,&default_float_sort_function,&default_double_sort_function,&default_string_sort_function};