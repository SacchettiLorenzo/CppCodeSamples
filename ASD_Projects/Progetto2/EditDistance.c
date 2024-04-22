#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647 
#define bufferSpan 16
#define expected_dictionary_length 661562
#define printValueMatrix 0
#define printArrowsMatrix 0

//todo: migliorare la parte del valore di ritorno della funzione correct_structured_word, rimuovere il trasferimento del risultato da correction_actual e correction_buffer

typedef enum directions { null, up, left, cross } Dir;
Dir* directions;
int* values;
int res;
char* to_be_corrected_text;
int text_length = 0;
char** unstructured_dictionary;
char* corrected_text;
int dictionary_length = 0;
char correction_buffer[40];
char correction_actual[40];
FILE* to_be_corrected_file_ptr = NULL;
FILE* dictionary_file_ptr = NULL;

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
    char word[50];
    int edit_distance;
};




int edit_distance(const char* s1, const char* s2);
int edit_distance_dyn(const char* s1, const char* s2);
void edit_distance_dyn_rec(const char* s1, const char* s2, int i, int j);
void read_files(FILE* to_be_corrected_file_ptr, FILE* dictionary_file_ptr, char** to_be_corrected_text, char*** unstructured_dictionary, WLN* head);
void correct(char* to_be_corrected_text, char** unstructured_dictionary);
void correct_structured(char* to_be_corrected_text,WLN* head);
struct result_set correct_structured_word(char* word,WLN* head);
size_t getline_(char** lineptr, size_t* n, FILE* stream);
void new_word(char* word, WLN* head);
void add_new_length_node(WLN* prev, WLN* next, int value);
void add_new_alphabetic_node(AN* prev, AN* next, char value);
int main()
{

    WLN* head = (WLN*)malloc(sizeof (struct word_length_node));
    /*
	const char* s1 = "altro";
	const char* s2 = "quando";
    const char* s3 = "quanto";

    new_word(s1,head);
    new_word(s2,head);
    new_word(s3,head);
	 int res = edit_distance(s1, s2);
	printf("%d\n", res);

    res = edit_distance_dyn(s1, s2);
    printf("%d\n", res);
    */
    to_be_corrected_file_ptr = fopen("correctme.txt", "r");
    dictionary_file_ptr = fopen("dictionary.txt", "r");
    read_files(to_be_corrected_file_ptr, dictionary_file_ptr,&to_be_corrected_text,&unstructured_dictionary,head);
	//correct(to_be_corrected_text, unstructured_dictionary);
    correct_structured(to_be_corrected_text,head);
	//fclose(to_be_corrected_file_ptr);
	//fclose(dictionary_file_ptr);

}


int edit_distance(const char* s1, const char* s2) {

	if (strlen(s1) == 0) {
		return strlen(s2);
	}
	if (strlen(s2) == 0) {
		return strlen(s1);
	}

	int d_no_op = 0;
	if (s1[0] == s2[0]) {
		d_no_op = edit_distance((s1 + 1), (s2 + 1));
	}
	else {
		d_no_op = INT_MAX;
	}

	int d_canc = 1 + edit_distance(s1, (s2 + 1));

	int d_ins = 1 + edit_distance((s1 + 1), s2);

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


	if (values != NULL && directions != NULL) {
		for (int i = 0; i < ((strlen(s1) + 1) * (strlen(s2) + 1)); i++)
		{
			values[i] = 0;
			if (i < strlen(s2)+1 && i > 0) {
				directions[i] = left;
			}
			else {
				if (i % (strlen(s2) +1 ) == 0 && i > 0) {
					directions[i] = up;
				}
				else {
					directions[i] = null;
				}

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
	int Icursor = strlen(s1) + 1;
	int Jcursor = strlen(s2) + 1;

	while (Icursor != 0 && Jcursor != 0)//check conditions ( might be Icursor != 1 || Jcursor != 1)
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

	/*{
		printf("   ");
		for (int i = 0; i < (strlen(s2)); i++) {
			printf(" %c", s2[i]);
		}


		for (int i = 0; i < ((strlen(s1) + 1) * (strlen(s2) + 1)); i++)
		{
			if (i % (strlen(s2) + 1) == 0) {

				printf("\n");
				if (i != 0) {
					printf("%c ", s1[(i / strlen(s2)) - 1]);
				}
				else {
					printf("  ");
				}

			}
			printf("%d ", values[i]);
		}
		printf("\n");
	}*/



	if (i < (strlen(s1) + 1) && j < (strlen(s2) + 1)) {
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



	if (j < strlen(s2))
		edit_distance_dyn_rec(s1, s2, i, j + 1);
	else {
		if (i < strlen(s1))
			edit_distance_dyn_rec(s1, s2, i + 1, 0);
	}

}

void read_files(FILE* to_be_corrected_file_ptr, FILE* dictionary_file_ptr, char** to_be_corrected_text, char*** unstructured_dictionary,WLN* head) { //check pointers
	char* line = NULL;
	size_t len = 0;
	line = (char*)malloc(len * sizeof(char));
	int read = 0;
	int index = 0;
	
	*unstructured_dictionary = (char**)malloc(expected_dictionary_length * sizeof(char*));
	if (*unstructured_dictionary == NULL) {
		printf("%s\n", "problems allocating memory");
		exit(EXIT_FAILURE);
	}

	if (to_be_corrected_file_ptr == NULL || dictionary_file_ptr == NULL) {
		printf("%s\n", "error loading file");
		exit(EXIT_FAILURE);
	}
	
	read = getline_(&line, &len, to_be_corrected_file_ptr);
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

	while ((read = getline_(&line, &len, dictionary_file_ptr)) != -1) {
		line[read-1] = '\0';
		(*unstructured_dictionary)[index] = (char*)malloc(read * sizeof(char));//todo: fix the +4 problem (with less than 4 char everything break)
		if ((*unstructured_dictionary)[index] == NULL) {
			printf("%s\n", "problems allocating memory");
			exit(EXIT_FAILURE);
		}
		memcpy((*unstructured_dictionary)[index], line, read);
		index++;

        if(head != null){
            new_word(line,head );
        }

}

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
	char separator;
	//to lowerCasefunction?
	while (right < text_length) {
		while (to_be_corrected_text[right] != ' ' 
			&& to_be_corrected_text[right] != ',' && to_be_corrected_text[right] != '.' 
			&& to_be_corrected_text[right] != ';' && to_be_corrected_text[right] != ':' 
			&& to_be_corrected_text[right] != '?' && to_be_corrected_text[right] != '\n' 
			&& to_be_corrected_text[right]!= '\0') {
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
		for (size_t i = 0; i < dictionary_length && edit_distance != 0; i++)
		{
			int k = edit_distance_dyn(tmp, unstructured_dictionary[i]);
			if (k < edit_distance) {
				edit_distance = k;
				correct_index = i;
			}
		}
		printf("%s corrected with %s with edit distance %d\n",tmp, unstructured_dictionary[correct_index], edit_distance);
		
		for (int i = left; i < right; i++) { //todo: this could be wrong
			corrected_text[i] = tmp[i];
		}

		while (to_be_corrected_text[right] == ' '
			|| to_be_corrected_text[right] == ',' || to_be_corrected_text[right] == '.'
			|| to_be_corrected_text[right] == ';' || to_be_corrected_text[right] == ':'
			|| to_be_corrected_text[right] == '?' || to_be_corrected_text[right] == '\n'
			|| to_be_corrected_text[right] == '\0') {
			corrected_text[right] = to_be_corrected_text[right];
			right++;
		}
		left = right;
		
	}

}

void correct_structured(char* to_be_corrected_text,WLN* head){
    int left = 0;
    int right = 0;
    char separator;
    //to lowerCasefunction?
    while (right < text_length) {
        while (to_be_corrected_text[right] != ' '
               && to_be_corrected_text[right] != ',' && to_be_corrected_text[right] != '.'
               && to_be_corrected_text[right] != ';' && to_be_corrected_text[right] != ':'
               && to_be_corrected_text[right] != '?' && to_be_corrected_text[right] != '\n'
               && to_be_corrected_text[right]!= '\0') {
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
        while (strlen(tmp) > head_->value){
            head_ = head_->next;
        }
        struct result_set res;
        if(strlen(tmp) == head_->value){
            //search center
            res = correct_structured_word(tmp,head_);
            if (res.edit_distance < edit_distance) {
                strcpy(correction_actual,correction_buffer);
                edit_distance = res.edit_distance;
            }
        }

        if(edit_distance != 0){
            WLN* head_left;
            WLN* head_right;
            if(head_->prev != NULL){
                head_left = head_->prev;
            }

            if(head_->next != NULL){
                head_right = head->next;
            }

            while (edit_distance != 0 && (head_left->prev != NULL || head_right->next != NULL)){
                res = correct_structured_word(tmp,head_left);
                if (res.edit_distance < edit_distance) {
                    strcpy(correction_actual,correction_buffer);
                    edit_distance = res.edit_distance;
                }
                if(edit_distance == 0)break;

                res = correct_structured_word(tmp,head_left);
                if (res.edit_distance < edit_distance) {
                    strcpy(correction_actual,correction_buffer);
                    edit_distance = res.edit_distance;
                }
                if(edit_distance == 0)break;

                if(head_left->prev != NULL){
                    head_left = head_left->prev;
                }

                if(head_right->next != NULL){
                    head_right = head_right->next;
                }
            }
        }

        printf("%s corrected with %s with edit distance %d\n",tmp, correction_actual, edit_distance);

        for (int i = left; i < right; i++) {//todo: this could be wrong
            corrected_text[i] = tmp[i];
        }

        while (to_be_corrected_text[right] == ' '
               || to_be_corrected_text[right] == ',' || to_be_corrected_text[right] == '.'
               || to_be_corrected_text[right] == ';' || to_be_corrected_text[right] == ':'
               || to_be_corrected_text[right] == '?' || to_be_corrected_text[right] == '\n'
               || to_be_corrected_text[right] == '\0') {
            corrected_text[right] = to_be_corrected_text[right];
            right++;
        }
        left = right;

    }
}

struct result_set correct_structured_word(char* word,WLN* head){
    struct result_set res;
    res.edit_distance = INT_MAX;

    if(head->value == 0 || head->alpphabet_order_dictionary_head == 0){
        return res;
    }
    AN* dictionary_ = head->alpphabet_order_dictionary_head->next;
    while ((int)word[0] > (int)dictionary_->value && dictionary_->next != NULL){
        dictionary_ = dictionary_->next;
    }
    if(word[0] == dictionary_->value){
        for (int i = 0; i < dictionary_->num_words && edit_distance != 0; ++i) {
            int k = edit_distance_dyn(word, dictionary_->dictionary[i]);
            if (k < res.edit_distance) {
                res.edit_distance = k;
                if(dictionary_->dictionary[i] != NULL)
                strcpy(correction_buffer,dictionary_->dictionary[i]);
            }
        }
    }
    if(edit_distance != 0){
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
            for (int i = 0; i < dictionary_left->num_words && edit_distance != 0; ++i) {
                int k = edit_distance_dyn(word, dictionary_left->dictionary[i]);
                if (k < res.edit_distance) {
                    res.edit_distance = k;
                    if(dictionary_->dictionary[i] != NULL)
                    strcpy(correction_buffer,dictionary_->dictionary[i]);  }
            }
            if(edit_distance == 0)break;

            for (int i = 0; i < dictionary_right->num_words && edit_distance != 0; ++i) {
                int k = edit_distance_dyn(word, dictionary_right->dictionary[i]);
                if (k < res.edit_distance) {
                    res.edit_distance = k;
                    if(dictionary_->dictionary[i] != NULL)
                    strcpy(correction_buffer,dictionary_->dictionary[i]);
                }
            }
            if(edit_distance == 0)break;

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
    WLN* original_WLN_head = head;
    if(head->alpphabet_order_dictionary_head == NULL){
        head->alpphabet_order_dictionary_head = (AN*)malloc(sizeof (struct alphabetic_node));
        head->alpphabet_order_dictionary_head->value = 0;
    }


    int length = strlen(word);
    while( length > head->value){ //il while si ferma all'elemeto successivo rispetto a quello che deve essere inserito, devo riformulare l'aggiunta dei nodi
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
