#include "Generic_data_manipulation.h"

Dataset* new_Dataset(int struct_size, int expected_rows,... /*variadic function for the functions*/) {

    functions = (_Struct_functions*)malloc(struct_size * sizeof(_Struct_functions*));

    if (functions == NULL) {
        printf("%s\n", "error loading functions");
        exit(EXIT_FAILURE);
    }

    va_list ptr;
    va_start(ptr, struct_size);


    for (int i = 0; i < struct_size; i++)
    {
        functions[i] = va_arg(ptr, _Struct_functions);
    }

    va_end(ptr);

    if (GDM.length == 0) {
        GDM.dataset = (Dataset*)malloc(sizeof(Dataset));
        GDM.length++;

    }
    else {
        GDM.dataset = (Dataset*)realloc(GDM.dataset, GDM.length * sizeof(Dataset));
        if(GDM.dataset == NULL){
            printf("problems with memory allocation");
            exit(EXIT_FAILURE);
        }
    }

    if (GDM.dataset + (GDM.length - 1) != NULL) {
        (GDM.dataset + (GDM.length - 1))->_Struct_size = struct_size;
        (GDM.dataset + (GDM.length - 1))->last_inserted = 0;
        (GDM.dataset + (GDM.length - 1))->expected_rows = expected_rows;
        (GDM.dataset + (GDM.length - 1))->type = T_dataset;
        (GDM.dataset + (GDM.length - 1))->size = 0;
        (GDM.dataset + (GDM.length - 1))->struct_type = (Type*)malloc(struct_size * sizeof(Type));
        return GDM.dataset + (GDM.length - 1);
    }else{
        printf("problems with memory allocation");
        exit(EXIT_FAILURE);
    }

}

void laod_from_file(FILE* fp, Dataset* dataset) {
    char* line = NULL;
    size_t len = 0;
    line = (char*)malloc(len * sizeof(char));
    int read;

    if (fp == NULL) {
        printf("%s\n", "error loading file");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        int left = 0, right = 0;
        int columns_counter = 0;


        GDM.new_record_allocation_function(dataset);

        for (int i = 0; i < read; i++)
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

    //Reallocate correct ammount of memory
    (*dataset).rows = (Struct*)realloc((*dataset).rows, dataset->last_inserted * sizeof(Struct*));
    dataset->size = dataset->last_inserted;
}

size_t getline_(char** lineptr, size_t* n, FILE* stream) {
    char* bufptr = NULL;
    char* p = bufptr;
    size_t size;
    int c;

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
        (*dataset).rows = (Struct*)malloc((*dataset).expected_rows * sizeof(Struct*));
        dataset->size = dataset->expected_rows;
    }


    if (dataset->last_inserted == dataset->size-1) {
        (*dataset).rows = (Struct*)realloc((*dataset).rows, (dataset->size * 2) * sizeof(Struct*));
        if((*dataset).rows == NULL){
            printf("problems with memory allocation");
            exit(EXIT_FAILURE);
        }
        dataset->size *= 2;
    }

    if ((*dataset).rows != NULL) {
        (*dataset).rows[(*dataset).last_inserted].fields = (Var*)malloc((*dataset)._Struct_size * sizeof(Var));
        (*dataset).last_inserted++;
    }
}

void load_element_as_int(char** lineptr, int i, int j, int column, Dataset* dataset) {

    int placeholder = 0;

    for (int index = i; index <= j; index++)
    {
        placeholder *= 10;
        placeholder += (int)(*lineptr)[index] - '0';
    }

    dataset->struct_type[column] = T_int;
    (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.n = placeholder;

#if log == 1
    printf("%d\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.n);
#endif

}

void load_element_as_char_array(char** lineptr, int i, int j, int column, Dataset* dataset) {
    char* placeholder = (char*)malloc(((j - i) + 1 + 1) + sizeof(char));
    if (placeholder == NULL) {
        printf("%s\n", "error loading char from file");
        exit(EXIT_FAILURE);
    }
    else {
        for (int index = i; index <= j; index++)
        {
            ((char*)placeholder)[index - i] = (char)(*lineptr)[index];
        }

        ((char*)placeholder)[j - i + 1] = '\0';
    }
    dataset->struct_type[column] = T_string;
    (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.s = placeholder;

#if log == 1
    printf("%s\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.s);
#endif
}

void load_element_as_double(char** lineptr, int i, int j, int column, Dataset* dataset) {
    char* placeholder = (char*)malloc(((j - i) + 1) + sizeof(char));
    double d_placeholder = 0;
    if (placeholder == NULL) {
        printf("%s\n", "error loading double from file");
        exit(EXIT_FAILURE);
    }
    else {
        for (int index = i; index <= j; index++)
        {
            ((char*)placeholder)[index - i] = (char)(*lineptr)[index];
        }
    }

    if (placeholder == NULL) {
        printf("%s\n", "error loading double from file");
        exit(EXIT_FAILURE);
    }
    d_placeholder = strtod(placeholder, NULL);

    dataset->struct_type[column] = T_double;
    (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d = d_placeholder;

#if log == 1
    printf("%f\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d);
#endif
}

void load_element_as_float(char** lineptr, int i, int j, int column, Dataset* dataset) {
    char* placeholder = (char*)malloc(((j - i) + 1) * sizeof(char));
    float d_placeholder = 0;
    if (placeholder == NULL) {
        printf("%s\n", "error loading float from file");
        exit(EXIT_FAILURE);
    }
    else {
        for (int index = i; index <= j; index++)
        {
            ((char*)placeholder)[index - i] = (char)(*lineptr)[index];
        }
    }

    if (placeholder == NULL) {
        printf("%s\n", "error loading float from file");
        exit(EXIT_FAILURE);
    }
    d_placeholder = strtof(placeholder, NULL);

    dataset->struct_type[column] = T_double;
    (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.f = d_placeholder;

#if log == 1
    printf("%f\n", (*dataset).rows[(*dataset).last_inserted - 1].fields[column].data.d);
#endif
}


void load_element_as_boolean(char** lineptr, int i, int j, int column, Dataset* dataset){
}

void load_element_as_struct(char** lineptr, int i, int j, int column, Dataset* dataset){}

int comparator(Var first, Var second, int num_comparation, ...) {

    va_list ptr;
    va_start(ptr, num_comparation);
    int result = 0;

    for (int i = 0; i < num_comparation; i++)
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

int default_int_sort_function(const void* a,const void* b) {
    if (*(int*)a < *(int*)b)return -1;
    if (*(int*)a == *(int*)b)return 0;
    if (*(int*)a > *(int*)b)return 1;
}

int default_float_sort_function(const void* a,const void* b) {
    if (*(float*)a < *(float*)b)return -1;
    if (*(float*)a == *(float*)b)return 0;
    if (*(float*)a > *(float*)b)return 1;
}

int default_double_sort_function(const void* a,const void* b) {
    if (*(double*)a < *(double*)b)return -1;
    if (*(double*)a == *(double*)b)return 0;
    if (*(double*)a > *(double*)b)return 1;
}

int default_string_sort_function(const void* a,const void* b) {
    int res = strcmp((*(char**)a),(*(char**)b));
    if(res == 0) return 0;
    if(res > 0) return 1;
    if(res < 0)return -1;
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo){
    Dataset* dataset = GDM.new_Dataset(4, 20000000, &load_element_as_int, &load_element_as_char_array, &load_element_as_int, &load_element_as_double);
    void* sorting_function;
    switch (field) {
        case 0:
            sorting_function = GDM.default_int_sort_function;
            break;
        case 1:
            sorting_function = GDM.default_string_sort_function;
            break;
        case 2:
            sorting_function = GDM.default_int_sort_function;
            break;
        case 3:
            sorting_function = GDM.default_double_sort_function;
            break;
        default:
            printf("you must provide an existing field");
            break;

    }
    double time_spent;
    clock_t begin = clock();
    GDM.load_from_file(infile, dataset);
    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("records loaded in: %f seconds \n",time_spent);
    GDM.sorting_fields = field;
    begin = clock();
    switch (algo)
    {
        case 1:
            GDM.mergeSort(dataset, dataset->last_inserted, dataset->_Struct_size, sorting_function);
            break;
        case 2:
            GDM.quickSort(dataset, dataset->last_inserted, dataset->_Struct_size, sorting_function);
        default:
            break;
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("records sorted in: %f seconds \n",time_spent);

    begin = clock();
    for (int i = 0; i < dataset->size; i++) {
        for (int j = 0; j < dataset->_Struct_size; j++)
        {
            switch (dataset->struct_type[j])
            {
                case T_int:
                    fprintf(outfile, "%d", dataset->rows[i].fields[j].data.n);
                    break;
                case T_string:
                    fprintf(outfile, "%s", dataset->rows[i].fields[j].data.s);
                    break;
                case T_double:
                    fprintf(outfile, "%f", dataset->rows[i].fields[j].data.d);
                    break;
                default:
                    break;
            }
            if (j < dataset->_Struct_size - 1) {
                fprintf(outfile, "%s", ",");
            }
        }
        fprintf(outfile, "\n", "\0");
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("records writed in: %f seconds \n",time_spent);

}

void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)){
    if(((Dataset*)base)->type == T_dataset){
        tmp = (Struct*)malloc(nitems * sizeof(Struct*));
        merge_sort_Dataset((Dataset*)base, 0, nitems-1, compar);
        free(tmp);
    }else{
        merge_sort_void(base, 0, nitems - 1, size, compar);
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

    for (int k = i; k <= j; k++)
    {
        dataset->rows[k] = tmp[k - i];
    }
}

void merge_sort_void(void* base, int i, int j, size_t size, int (*compar)(const void*, const void*)) {
    int middle = (i + j) / 2;
    if (i < j) {
        merge_sort_void(base, i, middle,size,compar);
        merge_sort_void(base, middle + 1, j,size,compar);
    }
    int placeholder = 0;
    int left = i; //i
    int right = middle + 1; //j

    if ((j - i) == 0) {
        tmp_void_sort = (void*)malloc(sizeof(void*));
    }
    else {
        tmp_void_sort = (void*)malloc((j - i) * sizeof(void*));
    }

    if (tmp_void_sort == NULL) {
        exit(EXIT_FAILURE);
    }

    while (left <= middle && right <= j)
    {
        if(compar((char*)base + (size * left) , (char*)base + (size * right)) == -1){
            memcpy((char*)tmp_void_sort + (size * placeholder), (char*)base + (size * left), size);
            left++;
        }
        else {
            memcpy((char*)tmp_void_sort + (size * placeholder), (char*)base + (size * right), size);
            right++;
        }
        placeholder++;
    }

    while (left <= middle)
    {
        memcpy((char*)tmp_void_sort + (size * placeholder), (char*)base + (size * left), size);
        left++;
        placeholder++;
    }

    while (right <= j)
    {
        memcpy((char*)tmp_void_sort + (size * placeholder), (char*)base + (size * right), size);
        right++;
        placeholder++;
    }


    for (int k = i; k <= j; k++)
    {
        memcpy((char*)base + (size * k), (char*)tmp_void_sort + (size * (k - i)), size);
    }

    free(tmp);
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)){
    if (((Dataset*)base)->type == T_dataset) {
        tmp = (Struct*)malloc(sizeof(Struct*));
        quick_sort_Dataset((Dataset*)base, 0, nitems - 1, compar);
        free(tmp);
    }
    else {
        quick_sort_void(base, 0, nitems - 1, size, compar);
    }
}

void quick_sort_Dataset(Dataset* dataset, int i, int j, int (*compar)(const void*, const void*)) {
    if (i >= j || i < 0) {
        return;
    }

    Var pivot = dataset->rows[j].fields[GDM.sorting_fields];
    int index = i - 1;

    for (int k = i; k <= j - 1; k++) {
        if (comparator(dataset->rows[k].fields[GDM.sorting_fields], pivot, 1, compar) == -1) {
            index++;
            *tmp = dataset->rows[index];
            dataset->rows[index] = dataset->rows[k];
            dataset->rows[k] = *tmp;
        }
    }

    index++;
    *tmp = dataset->rows[index];
    dataset->rows[index] = dataset->rows[j];
    dataset->rows[j] = *tmp;

    quick_sort_Dataset(dataset, i, index - 1,compar);
    quick_sort_Dataset(dataset, index + 1, j,compar);
}

void quick_sort_void(void* base, int i, int j, size_t size, int (*compar)(const void*, const void*)) {
    if (i >= j || i < 0) {
        return;
    }

    void* pivot = (char*)base + (j * size);
    int index = i - 1;
    void* tmp_ = (void*)malloc(sizeof(void*));

    for (int k = i; k <= j - 1; k++) {
        if (compar((char*)base + (size * k), pivot) == -1) {
            index++;
            memcpy((char*)tmp_, (char*)base + (size * index),size);
            memcpy((char*)base + (size * index), (char*)base + (size * k), size);
            memcpy((char*)base + (size * k), (char*)tmp_, size);
        }
    }

    index++;
    memcpy((char*)tmp_, (char*)base + (size * index), size);
    memcpy((char*)base + (size * index), (char*)base + (size * j), size);
    memcpy((char*)base + (size * j), (char*)tmp_, size);

    quick_sort_void(base, i, index - 1,size, compar);
    quick_sort_void(base, index + 1, j,size, compar);

    free(tmp_);
}