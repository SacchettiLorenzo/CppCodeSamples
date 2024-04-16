#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647 
#define bufferSpan 16
#define expected_dictionary_length 661562
#define printValueMatrix 0
#define printArrowsMatrix 0

typedef enum directions { null, up, left, cross } Dir;
Dir* directions;
int* values;
int res;
char* to_be_corrected_text;
int text_length = 0;
char** unstructured_dictionary;
char* corrected_text;
int dictionary_length = 0;
FILE* to_be_corrected_file_ptr = NULL;
FILE* dictionary_file_ptr = NULL;
errno_t error;

int edit_distance(const char* s1, const char* s2);
int edit_distance_dyn(const char* s1, const char* s2);
void edit_distance_dyn_rec(const char* s1, const char* s2, int i, int j);
void read_files(FILE* to_be_corrected_file_ptr, FILE* dictionary_file_ptr, char* to_be_corrected_text, char** unstructured_dictionary);
void correct(char* to_be_corrected_text, char** unstructured_dictionary);
size_t getline(char** lineptr, size_t* n, FILE* stream);

int main()
{


	const char* s1 = "do";
	const char* s2 = "quando";

	/*int res = edit_distance(s1, s2);
	printf("%d\n", res);*/

	/*res = edit_distance_dyn(s1, s2);
	printf("%d\n", res);*/

	error = fopen_s(&to_be_corrected_file_ptr, "C:\\Users\\Lorenzo\\Desktop\\correctme.txt", "r");
	error = fopen_s(&dictionary_file_ptr, "C:\\Users\\Lorenzo\\Desktop\\dictionary.txt", "r");
	read_files(to_be_corrected_file_ptr, dictionary_file_ptr,&to_be_corrected_text,&unstructured_dictionary);
	fclose(to_be_corrected_file_ptr);
	fclose(dictionary_file_ptr);
	correct(to_be_corrected_text, unstructured_dictionary);

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

#if printArrowsMatrix true
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
#if printValueMatrix true
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

void read_files(FILE* to_be_corrected_file_ptr, FILE* dictionary_file_ptr, char** to_be_corrected_text, char*** unstructured_dictionary) { //check pointers
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
	
	read = getline(&line, &len, to_be_corrected_file_ptr);
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

	while ((read = getline(&line, &len, dictionary_file_ptr)) != -1) {
		line[read-1] = '\0';
		(*unstructured_dictionary)[index] = (char*)malloc((read + 4) * sizeof(char));//todo: fix the +4 problem (with less than 4 char everything break)
		if ((*unstructured_dictionary)[index] == NULL) {
			printf("%s\n", "problems allocating memory");
			exit(EXIT_FAILURE);
		}
		memcpy((*unstructured_dictionary)[index], line, read);
		index++;
	}
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
		
		for (int i = left; i < right; i++) {
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