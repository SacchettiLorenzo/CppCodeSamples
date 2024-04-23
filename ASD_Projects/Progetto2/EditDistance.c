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
Dir* directions;
int* values;

int text_length = 0;
int word_analized = 0;
char* corrected_text;
int dictionary_length = 0;

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

	const char* s1 = "orizonte";
	const char* s2 = "oriente";
    const char* s3 = "quanto";

    int res;
	// res = edit_distance(s1, s2);
	//printf("%d\n", res);

    //res = edit_distance_dyn(s1, s2);
    //printf("%d\n", res);


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


int edit_distance_rec(const char* s1, const char* s2) {

	if (strlen(s1) == 0) {
		return (int)strlen(s2);
	}
	if (strlen(s2) == 0) {
		return (int)strlen(s1);
	}

	int d_no_op = 0;
	if (s1[0] == s2[0]) {
		d_no_op = edit_distance_rec((s1 + 1), (s2 + 1));
	}
	else {
		d_no_op = INT_MAX;
	}

	int d_canc = 1 + edit_distance_rec(s1, (s2 + 1));

	int d_ins = 1 + edit_distance_rec((s1 + 1), s2);

	int min_value = d_no_op;
	if (d_canc < min_value) {
		min_value = d_canc;
	}

	if (d_ins < min_value) {
		min_value = d_ins;
	}

	return min_value;

}

int edit_distance_dyn(const char* s1, const char* s2) {
	directions = (Dir*)malloc((strlen(s1) + 1) * (strlen(s2) + 1) * sizeof(Dir));
	values = (int*)malloc((strlen(s1) + 1) * (strlen(s2) + 1) * sizeof(int));

    if (directions == NULL || values == NULL) {
        printf("%s\n", "problems allocating memory");
        exit(EXIT_FAILURE);
    }

	//directions and values matrices preparation
		for (int i = 0; i < (int)((strlen(s1) + 1) * (strlen(s2) + 1)); i++)
		{
			values[i] = 0;
			if (i < (int)strlen(s2)+1 && i > 0) {
				directions[i] = left;
			}
			else {
				if (i % (int)(strlen(s2) +1 ) == 0 && i > 0) {
					directions[i] = up;
				}
				else {
					directions[i] = null;
				}

			}
		}


	edit_distance_dyn_rec(s1, s2, 0, 0);

#if printArrowsMatrix == 1
	printf("   ");
	for (int i = 0; i < (strlen(s2)); i++) {
		printf(" %c", s2[i]);
	}

	for (int i = 0; i < ((strlen(s1) + 1) * (strlen(s2) + 1)); i++)
	{
		if (i % (strlen(s2) + 1) == 0) {

			printf("\n");
			if (i != 0) {
				printf("%c ", s1[(i / (strlen(s2) + 1)) - 1]);
			}
			else {
				printf("  ");
			}

		}

		if (directions[i] == up) {
			printf("%s ", "^");
		}
		if (directions[i] == left) {
			printf("%s ", "<");
		}
		if (directions[i] == cross) {
			printf("%s ", "\\");
		}
		if (directions[i] == null) {
			printf("%s ", "_");
		}
	}

	printf("\n");
	printf("\n");
#endif
#if printValueMatrix == 1
	printf("   ");
	for (int i = 0; i < (strlen(s2)); i++) {
		printf(" %c", s2[i]);
	}


	for (int i = 0; i < ((strlen(s1) + 1) * (strlen(s2) + 1)); i++)
	{
		if (i % (strlen(s2) + 1) == 0) {

			printf("\n");
			if (i != 0) {
				printf("%c ", s1[(i / (strlen(s2) + 1)) - 1]);
			}
			else {
				printf("  ");
			}

		}
		printf("%d ", values[i]);
	}
	printf("\n");
#endif
	int res = 0;
	int Icursor = (int)strlen(s1) + 1;
	int Jcursor = (int)strlen(s2) + 1;

	//calculate the result of the edit distance algorithm
	while (Icursor != 0 && Jcursor != 0)
	{
		if (directions[(Icursor - 1) * (strlen(s2) + 1) + (Jcursor)-1] == cross) {
			
			Icursor--;
			Jcursor--;
		}
		else {
			if (directions[(Icursor - 1) * (strlen(s2) + 1) + (Jcursor)-1] == up) {
				if (directions[(Icursor - 1) * (strlen(s2) + 1) + (Jcursor)-1] != null) {
					res++;
				}
				Icursor--;
			}
			else {
				if (directions[(Icursor - 1) * (strlen(s2) + 1) + (Jcursor)-1] != null) {
					res++;
				}
				Jcursor--;
			}
		}
	}

	free(directions);
	free(values);
	return res;
}

void edit_distance_dyn_rec(const char* s1, const char* s2, int i, int j) {

	//values and direction matrices have one column and one row more so
	//(j+1) adjust the offset for the right calculation
	//if j has no +1 it means that the original operation was (j+1)-1



	if (i < (int)(strlen(s1) + 1) && j < (int)(strlen(s2) + 1)) {
		if (s1[i - 1] == s2[j - 1]) {
			if (i != 0 && j != 0) {
				values[(i * (strlen(s2) + 1) + (j + 1)) - 1] = values[(((i - 1) * (strlen(s2) + 1)) + j) - 1] + 1; // may add +1
				directions[(i * (strlen(s2) + 1) + (j + 1)) - 1] = cross;
			}
		}
		else {
			if (values[((i - 1) * (strlen(s2) + 1) + (j + 1)) - 1] >= values[(i * (strlen(s2) + 1) + j) - 1]) {
				if (i != 0 && j != 0) {
					values[(i * (strlen(s2) + 1) + (j + 1)) - 1] = values[((i - 1) * (strlen(s2) + 1) + (j + 1)) - 1];
					directions[(i * (strlen(s2) + 1) + (j + 1)) - 1] = up;
				}
			}
			else {
				if (i != 0 && j != 0) {
					values[(i * (strlen(s2) + 1) + (j + 1)) - 1] = values[(i * (strlen(s2) + 1) + j) - 1];
					directions[(i * (strlen(s2) + 1) + (j + 1)) - 1] = left;
				}
			}
		}



	}



	if (j < (int)strlen(s2))
		edit_distance_dyn_rec(s1, s2, i, j + 1);
	else {
		if (i < (int)strlen(s1))
			edit_distance_dyn_rec(s1, s2, i + 1, 0);
	}

}

void read_files(FILE* to_be_corrected_file_ptr, FILE* dictionary_file_ptr, char** to_be_corrected_text, char*** unstructured_dictionary,WLN* head) { //check pointers
	//todo: check if pointers are not null

    char* line = NULL;
	size_t len = 0;
	line = (char*)malloc(len * sizeof(char));
	int read = 0;
	int index = 0;
	
	//todo: add dynamic memory allocation
	*unstructured_dictionary = (char**)malloc(expected_dictionary_length * sizeof(char*));
	if (*unstructured_dictionary == NULL) {
		printf("%s\n", "problems allocating memory");
		exit(EXIT_FAILURE);
	}

	if (to_be_corrected_file_ptr == NULL || dictionary_file_ptr == NULL) {
		printf("%s\n", "error loading file");
		exit(EXIT_FAILURE);
	}
	
	read = (int)getline_(&line, &len, to_be_corrected_file_ptr);
	*to_be_corrected_text = (char*)malloc(read * sizeof(char));
	if (*to_be_corrected_text == NULL) {
		printf("%s\n", "text is null");
		exit(EXIT_FAILURE);
	}
	memcpy(*to_be_corrected_text, line, read);
	text_length = read;
	corrected_text = (char*)malloc(text_length * sizeof(char));
	if (corrected_text == NULL) {
		printf("%s\n", "problems allocating memory");
		exit(EXIT_FAILURE);
	}

	while ((read = (int)getline_(&line, &len, dictionary_file_ptr)) != -1) {
		line[read-1] = '\0';
		(*unstructured_dictionary)[index] = (char*)malloc(read * sizeof(char));
		if ((*unstructured_dictionary)[index] == NULL) {
			printf("%s\n", "problems allocating memory");
			exit(EXIT_FAILURE);
		}
		memcpy((*unstructured_dictionary)[index], line, read);
		index++;

		//if head exist add a new word to the data structure
        if(head != null){
            new_word(line,head );
        }
	}

	//keep the head at the beginning of the list
    WLN* tmp = head;

    while (head->next != NULL){
        while (head->alpphabet_order_dictionary_head->prev != NULL){
            head->alpphabet_order_dictionary_head = head->alpphabet_order_dictionary_head->prev;
        }
        head = head->next;
    }
    head = tmp;

	dictionary_length = index;
}

void correct(char* to_be_corrected_text, char** unstructured_dictionary) {
	int left = 0;
	int right = 0;
	
	while (right < text_length) {
		while (to_be_corrected_text[right] != ' ' 
			&& to_be_corrected_text[right] != ',' && to_be_corrected_text[right] != '.' 
			&& to_be_corrected_text[right] != ';' && to_be_corrected_text[right] != ':' 
			&& to_be_corrected_text[right] != '?' && to_be_corrected_text[right] != '\''
            && to_be_corrected_text[right] != '\n'&& to_be_corrected_text[right]!= '\0') {
			right++;
		}
		
		char* tmp = (char*)malloc((right - left + 1) / sizeof(char));

		if (tmp == NULL) {
			printf("%s\n", "problems allocating memory");
			exit(EXIT_FAILURE);
		}

		memcpy(tmp, to_be_corrected_text + left, right - left);
		tmp[right - left] = '\0';

		int edit_distance = INT_MAX;
		int correct_index;
		for (int i = 0; i < dictionary_length && edit_distance != 0; i++)
		{
			int k = edit_distance_rec(tmp, unstructured_dictionary[i]);
            word_analized++;
			if (k < edit_distance) {
				edit_distance = k;
				correct_index = i;
			}
		}

#if log == 1
		printf("%s --> %s , edit distance %d\n",tmp, unstructured_dictionary[correct_index], edit_distance);
#endif

        strcat(corrected_text,unstructured_dictionary[correct_index]);
        char cToStr[2];
        cToStr[1] = '\0';
		while (to_be_corrected_text[right] == ' '
			|| to_be_corrected_text[right] == ',' || to_be_corrected_text[right] == '.'
			|| to_be_corrected_text[right] == ';' || to_be_corrected_text[right] == ':'
			|| to_be_corrected_text[right] == '?' || to_be_corrected_text[right] == '\''
            || to_be_corrected_text[right] == '\n'|| to_be_corrected_text[right] == '\0') {
            cToStr[0] = to_be_corrected_text[right];
            strcat(corrected_text,cToStr);
			right++;
		}
		left = right;
	}
    printf("%s\n", to_be_corrected_text);
    printf("%s\n", corrected_text);
    printf("word analyzed: %d\n", word_analized);
}

void correct_dyn(char* to_be_corrected_text, char** unstructured_dictionary) {
    int left = 0;
    int right = 0;

    while (right < text_length) {
        while (to_be_corrected_text[right] != ' '
               && to_be_corrected_text[right] != ',' && to_be_corrected_text[right] != '.'
               && to_be_corrected_text[right] != ';' && to_be_corrected_text[right] != ':'
               && to_be_corrected_text[right] != '?' && to_be_corrected_text[right] != '\''
               && to_be_corrected_text[right] != '\n'&& to_be_corrected_text[right]!= '\0') {
            right++;
        }

        char* tmp = (char*)malloc((right - left + 1) / sizeof(char));

        if (tmp == NULL) {
            printf("%s\n", "problems allocating memory");
            exit(EXIT_FAILURE);
        }

        memcpy(tmp, to_be_corrected_text + left, right - left);
        tmp[right - left] = '\0';

        int edit_distance = INT_MAX;
        int correct_index;
        for (int i = 0; i < dictionary_length && edit_distance != 0; i++)
        {
            int k = edit_distance_dyn(tmp, unstructured_dictionary[i]);
            word_analized++;
            if (k < edit_distance) {
                edit_distance = k;
                correct_index = i;
            }
        }

#if log == 1
        printf("%s --> %s , edit distance %d\n",tmp, unstructured_dictionary[correct_index], edit_distance);
#endif

        strcat(corrected_text,unstructured_dictionary[correct_index]);
        char cToStr[2];
        cToStr[1] = '\0';
        while (to_be_corrected_text[right] == ' '
               || to_be_corrected_text[right] == ',' || to_be_corrected_text[right] == '.'
               || to_be_corrected_text[right] == ';' || to_be_corrected_text[right] == ':'
               || to_be_corrected_text[right] == '?' || to_be_corrected_text[right] == '\''
               || to_be_corrected_text[right] == '\n'|| to_be_corrected_text[right] == '\0') {
            cToStr[0] = to_be_corrected_text[right];
            strcat(corrected_text,cToStr);
            right++;
        }
        left = right;
    }
    printf("%s\n", to_be_corrected_text);
    printf("%s\n", corrected_text);
    printf("word analyzed: %d\n", word_analized);
}

void correct_structured(char* to_be_corrected_text,WLN* head){
    int left = 0;
    int right = 0;

    //to lowerCasefunction?
    while (right < text_length) {
        while (to_be_corrected_text[right] != ' '
               && to_be_corrected_text[right] != ',' && to_be_corrected_text[right] != '.'
               && to_be_corrected_text[right] != ';' && to_be_corrected_text[right] != ':'
               && to_be_corrected_text[right] != '?' && to_be_corrected_text[right] != '\n'
               && to_be_corrected_text[right] != '\''&& to_be_corrected_text[right]!= '\0') {
            right++;
        }

        char* tmp = (char*)malloc((right - left + 1) / sizeof(char));

        if (tmp == NULL) {
            printf("%s\n", "problems allocating memory");
            exit(EXIT_FAILURE);
        }

        memcpy(tmp, to_be_corrected_text + left, right - left);
        tmp[right - left] = '\0';

        WLN* head_ = head;
        int edit_distance = INT_MAX;
        char* word_corrected = (char*)malloc((right - left + 1)*sizeof(char));

		//go to the nearest word length
        while ((int)strlen(tmp) > head_->value){
            head_ = head_->next;
        }
        struct result_set res;
        res.edit_distance = INT_MAX;
		//search middle
        if((int)strlen(tmp) == head_->value){
            res = correct_structured_word(tmp,head_);
            if (res.edit_distance < edit_distance) {
                strcpy(word_corrected,res.word);
                edit_distance = res.edit_distance;
            }
        }

		//search the nearest word in the lists one element further to left than right
        if(edit_distance != 0){
            WLN* head_left;
            WLN* head_right;
            if(head_->prev != NULL){
                head_left = head_->prev;
            }

            if(head_->next != NULL){
                head_right = head_->next; //todo: check if "head" should be "head_"
            }

            while (res.edit_distance != 0 && (head_left->prev != NULL || head_right->next != NULL)){
                res = correct_structured_word(tmp,head_left);
                if (res.edit_distance < edit_distance) {
                    strcpy(word_corrected,res.word);
                    edit_distance = res.edit_distance;
                }
                if(edit_distance == 0) {
                    break;
                }

                res = correct_structured_word(tmp,head_right);
                if (res.edit_distance < edit_distance) {
                    strcpy(word_corrected,res.word);
                    edit_distance = res.edit_distance;
                }
                if(edit_distance == 0) {
                    break;
                }

                if(head_left->prev != NULL){
                    head_left = head_left->prev;
                }

                if(head_right->next != NULL){
                    head_right = head_right->next;
                }
            }
        }
#if log == 1
        printf("%s --> %s , edit distance %d\n",tmp, word_corrected, edit_distance);
#endif
        strcat(corrected_text,word_corrected);
        char cToStr[2];
        cToStr[1] = '\0';
        while (to_be_corrected_text[right] == ' '
               || to_be_corrected_text[right] == ',' || to_be_corrected_text[right] == '.'
               || to_be_corrected_text[right] == ';' || to_be_corrected_text[right] == ':'
               || to_be_corrected_text[right] == '?' || to_be_corrected_text[right] == '\n'
               ||to_be_corrected_text[right] == '\'' || to_be_corrected_text[right] == '\0') {
            cToStr[0] = to_be_corrected_text[right];
            strcat(corrected_text,cToStr);
            right++;

        }
        left = right;

    }
    printf("%s\n", to_be_corrected_text);
    printf("%s\n", corrected_text);
    printf("word analyzed: %d\n", word_analized);
}

struct result_set correct_structured_word(char* word,WLN* head){

    struct result_set res;
    res.edit_distance = INT_MAX;

    if(head->value == 0 || head->alpphabet_order_dictionary_head == 0){
        return res;
    }
    res.word = (char*)malloc((head->value) * sizeof (char));

    AN* dictionary_;
    if(head->alpphabet_order_dictionary_head->value == 0){
        dictionary_ = head->alpphabet_order_dictionary_head->next;
    }else{
        dictionary_ = head->alpphabet_order_dictionary_head;
    }

	//go to the nearest word by the first letter
    while ((int)word[0] > (int)dictionary_->value && dictionary_ != NULL && dictionary_->next != NULL){
        dictionary_ = dictionary_->next;
    }
    if(word[0] == dictionary_->value){
        for (int i = 0; i < dictionary_->num_words && res.edit_distance != 0; ++i) {
            int k = edit_distance_dyn(word, dictionary_->dictionary[i]);
            word_analized++;
            if (k < res.edit_distance) {
                res.edit_distance = k;
                if(dictionary_->dictionary[i] != NULL)
                strcpy(res.word,dictionary_->dictionary[i]);
            }
        }
    }

	//search the nearest word in the lists one element further to left than right
    if(res.edit_distance != 0){
        AN* dictionary_left;
        AN* dictionary_right;
        if(dictionary_->prev != NULL){
            dictionary_left = dictionary_->prev;
        }

        if(dictionary_->next != NULL){
            dictionary_right = dictionary_->next;
        }

        while (dictionary_left->prev != NULL || dictionary_right->next != NULL){
            //search
            for (int i = 0; i < dictionary_left->num_words && res.edit_distance != 0; ++i) {
                int k = edit_distance_dyn(word, dictionary_left->dictionary[i]);
                word_analized++;
                if (k < res.edit_distance) {
                    res.edit_distance = k;
                    if(dictionary_left->dictionary[i] != NULL)
                    strcpy(res.word,dictionary_left->dictionary[i]);  }
            }
            if(res.edit_distance == 0) {
                break;
            }

            for (int i = 0; i < dictionary_right->num_words && res.edit_distance != 0; ++i) {
                int k = edit_distance_dyn(word, dictionary_right->dictionary[i]);
                word_analized++;
                if (k < res.edit_distance) {
                    res.edit_distance = k;
                    if(dictionary_right->dictionary[i] != NULL){
                        strcpy(res.word,dictionary_right->dictionary[i]);
                    }
                }
            }
            if(res.edit_distance == 0) {
                break;
            }

            if(dictionary_left->prev != NULL){
                dictionary_left = dictionary_left->prev;
            }
            if(dictionary_right->next != NULL){
                dictionary_right = dictionary_right->next;
            }
        }
    }
    return res;
}

size_t getline_(char** lineptr, size_t* n, FILE* stream) {
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

void new_word(char* word, WLN* head){
    if (head == NULL || word == NULL) {
        printf("%s\n", "one ore more NULL pointers");
        exit(EXIT_FAILURE);
    }
    WLN* original_WLN_head = head;
    if(head->alpphabet_order_dictionary_head == NULL){
        head->alpphabet_order_dictionary_head = (AN*)malloc(sizeof (struct alphabetic_node));
        head->alpphabet_order_dictionary_head->value = 0;
    }


    int length = (int)strlen(word);
    while( length > head->value){
        if(head->next == NULL){
            add_new_length_node(head, NULL, length);
        }
        head = head->next;
    }

    if(length < head->value){
        add_new_length_node(head->prev, head, length);
        head = head->prev;
    }

    AN* original_AN_head = head->alpphabet_order_dictionary_head;
    int first_char_value = (int)word[0];
    while(first_char_value > (int)head->alpphabet_order_dictionary_head->value){
        if(head->alpphabet_order_dictionary_head->next == NULL){
        add_new_alphabetic_node(head->alpphabet_order_dictionary_head,NULL,word[0]);
        }
        head->alpphabet_order_dictionary_head = head->alpphabet_order_dictionary_head->next;
    }
    if(first_char_value < (int)head->alpphabet_order_dictionary_head->value){
        add_new_alphabetic_node(head->alpphabet_order_dictionary_head->prev,head->alpphabet_order_dictionary_head,word[0]);
        head->alpphabet_order_dictionary_head = head->alpphabet_order_dictionary_head->prev;
    }

    if(head->alpphabet_order_dictionary_head->allocated-1 == head->alpphabet_order_dictionary_head->num_words){
        //todo: add realloc protection
        head->alpphabet_order_dictionary_head->dictionary = realloc(head->alpphabet_order_dictionary_head->dictionary,head->alpphabet_order_dictionary_head->allocated*2*sizeof (char*));
        if(head->alpphabet_order_dictionary_head->dictionary == NULL){
                printf("%s\n", "problems allocating memory");
                exit(EXIT_FAILURE);
        }else{
            head->alpphabet_order_dictionary_head->allocated *= 2;
        }
    }
    head->alpphabet_order_dictionary_head->dictionary[head->alpphabet_order_dictionary_head->num_words] = (char*)malloc(
            (strlen(word)+1) * sizeof(char));
    memcpy(head->alpphabet_order_dictionary_head->dictionary[head->alpphabet_order_dictionary_head->num_words],word,
           strlen(word));
    head->alpphabet_order_dictionary_head->dictionary[head->alpphabet_order_dictionary_head->num_words][strlen(word)] = 0;
    head->alpphabet_order_dictionary_head->num_words++;



}

void add_new_length_node(WLN* prev, WLN* next, int value){

    WLN* new_node = (WLN*)malloc(sizeof (struct word_length_node));
    if(new_node->alpphabet_order_dictionary_head == NULL){
        new_node->alpphabet_order_dictionary_head = (AN*)malloc(sizeof (struct alphabetic_node));
        new_node->alpphabet_order_dictionary_head->value = 0;
    }
    prev->next = new_node;
    new_node->prev = prev;
    new_node->next = next;
    if(next != NULL){
        next->prev = new_node;
    }
    new_node->value = value;
}

void add_new_alphabetic_node(AN* prev, AN* next, char value){
    //allocate dictionary
    AN* new_node = (AN*)malloc(sizeof(struct alphabetic_node));
    prev->next = new_node;
    new_node->prev = prev;
    new_node->next = next;
    if(next != NULL){
        next->prev = new_node;
    }
    new_node->value = value;
    new_node->num_words = 0;
    new_node->allocated = bufferSpan;
    new_node->dictionary = (char**)malloc(bufferSpan * sizeof (char*));
    if(new_node->dictionary == NULL){
        printf("%s\n", "problems allocating memory");
        exit(EXIT_FAILURE);
    }
}
