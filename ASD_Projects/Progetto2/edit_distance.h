#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define INT_MAX 2147483647 
#define bufferSpan 16
#define expected_dictionary_length 661562
#define printValueMatrix 0
#define printArrowsMatrix 0
#define log 1

//todo: add toLOwerCase function

typedef enum directions { null, up, left, cross } Dir;
static Dir* directions;
static int* values;

static int text_length = 0;
static int word_analized = 0;
static char* corrected_text;
static int dictionary_length = 0;

typedef struct alphabetic_node{
    char value;
    struct alphabetic_node* prev;
    struct alphabetic_node* next;
    int num_words;
    int allocated;
    char** dictionary;
}AN;

typedef struct word_length_node{
    int value;
    struct word_length_node* prev;
    struct word_length_node* next;
    struct alphabetic_node* alpphabet_order_dictionary_head;
}WLN;

struct result_set{
    char* word;
    int edit_distance;
};

/**
 * @brief Calculate edit distance between two words using recursion over word pieces
 * 
 * @param s1 string 1
 * @param s2 string 2
 * @addtogroup edit_distance_functions
 * @return int
 */
int edit_distance_rec(const char* s1, const char* s2);

/**
 * @brief Calculate edit distance between two words using dynamic programming
 * 
 * @param s1 string 1
 * @param s2 string 2
 * @addtogroup edit_distance_functions
 * @return int 
 */
int edit_distance_dyn(const char* s1, const char* s2);

/**
 * @brief Actual dynamic programming recursive edit distance calculation
 * 
 * @param s1 string 1
 * @param s2 string 2
 * @param i index i
 * @param j index j
 * @addtogroup edit_distance_functions
 */
void edit_distance_dyn_rec(const char* s1, const char* s2, int i, int j);

/**
 * @brief read the files and load the text into the right data structure
 * 
 * @param to_be_corrected_file_ptr pointer to a file containing the text to correct
 * @param dictionary_file_ptr pointer to a file containing the dictionary
 * @param to_be_corrected_text pointer to a char array used to save the text to correct
 * @param unstructured_dictionary pointer to a char* array used to store the dictionary
 * @param head pointer to a word_length_node used to store the dictionary in a structured manner
 */
void read_files(FILE* to_be_corrected_file_ptr, FILE* dictionary_file_ptr, char** to_be_corrected_text, char*** unstructured_dictionary, WLN* head);

/**
 * @brief correct the words using the edit_distance function (non dynamic)
 *
 * @param to_be_corrected_text pointer to a char array containing the words to be corrected
 * @param unstructured_dictionary pointer to a char* containing the dictionary
 * @addtogroup correction_functions
 */
void correct(char* to_be_corrected_text, char** unstructured_dictionary);

/**
 * @brief correct the words using the edit_distance function (dynamic)
 * 
 * @param to_be_corrected_text pointer to a char array containing the words to be corrected
 * @param unstructured_dictionary pointer to a char* containing the dictionary
 * @addtogroup correction_functions
 */
void correct_dyn(char* to_be_corrected_text, char** unstructured_dictionary);

/**
 * @brief corect the words using the edit_distance_dyn function (dynamic)
 * 
 * @param to_be_corrected_text pointer to a char array containing the words to be corrected
 * @param head pointer to a word_length_node used to store the dictionary in a structured manner
 * @addtogroup correction_functions
 */
void correct_structured(char* to_be_corrected_text,WLN* head);

/**
 * @brief correct one word
 * 
 * @param word pointe to a char array with the work to look for
 * @param head pointer to a word_length_node used to store the dictionary in a structured manner
 * @return struct result_set 
 * @addtogroup correction_functions
 */
struct result_set correct_structured_word(char* word,WLN* head);

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
 * @brief add a word to a structured dictionary
 * 
 * @param word pointer to the word that should be added
 * @param head pointer to a word_length_node used to store the dictionary in a structured manner
 */
void new_word(char* word, WLN* head);

/**
 * @brief add a new node for word with specific length
 * 
 * @param prev node before this one
 * @param next node next this one
 * @param value word length
 */
void add_new_length_node(WLN* prev, WLN* next, int value);

/**
 * @brief add a new node for word with specific first letter
 * 
 * @param prev node before this one
 * @param next node next this one
 * @param value first letter of the word
 */
void add_new_alphabetic_node(AN* prev, AN* next, char value);