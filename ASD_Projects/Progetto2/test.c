#include "edit_distance.h"
#include "UnitTest.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage:\n1: recursive correction\n2: dynamic correction\n3: dynamic structured correction\n");
        return 1;
    }
    double time_spent;
    int selection = atoi(argv[1]);

    WLN* head = (WLN*)malloc(sizeof (struct word_length_node));
    FILE* to_be_corrected_file_ptr = NULL;
    FILE* dictionary_file_ptr = NULL;
    char* to_be_corrected_text;
    char** unstructured_dictionary;

    /*
	const char* s1 = "orizonte";
	const char* s2 = "oriente";
    const char* s3 = "quanto";

    int res;
	 res = edit_distance(s1, s2);
	printf("%d\n", res);

    res = edit_distance_dyn(s1, s2);
    printf("%d\n", res);
    */

    to_be_corrected_file_ptr = fopen("correctme.txt", "r");
    dictionary_file_ptr = fopen("dictionary.txt", "r");
    read_files(to_be_corrected_file_ptr, dictionary_file_ptr,&to_be_corrected_text,&unstructured_dictionary,head);

    switch (selection) {
        case 1:
            word_analized = 0;
            clock_t begin = clock();
            correct(to_be_corrected_text, unstructured_dictionary);
            clock_t end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("time spent in non dynamic correct function: %f\n",time_spent);
            break;
        case 2:
            word_analized = 0;
            clock_t begin_ = clock();
            correct_dyn(to_be_corrected_text, unstructured_dictionary);
            clock_t end_ = clock();
            time_spent = (double)(end_ - begin_) / CLOCKS_PER_SEC;
            printf("time spent in dynamic correct function: %f\n",time_spent);
            break;
        case 3:
            word_analized = 0;
            clock_t begin__ = clock();
            correct_structured(to_be_corrected_text,head);
            clock_t end__ = clock();
            time_spent = (double)(end__- begin__) / CLOCKS_PER_SEC;
            printf("time spent in dynamic structured correct function: %f\n",time_spent);
            break;
        default:return 1;
    }


    /*
	//fclose(to_be_corrected_file_ptr);
	//fclose(dictionary_file_ptr);
    */
}