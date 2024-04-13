#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647 

typedef enum directions { null, up, left, cross } Dir;
Dir* directions;
int* values;
int res;
int edit_distance(const char* s1, const char* s2);
int edit_distance_dyn(const char* s1, const char* s2);
void edit_distance_dyn_rec(const char* s1, const char* s2, int i, int j);

int main()
{
	const char* s1 = "vaiInFiga";
	const char* s2 = "PorcoDio";

	int res = edit_distance(s1, s2);
	printf("%d\n", res);

	res = edit_distance_dyn(s1, s2);
	printf("%d\n", res);
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
			if (i < strlen(s1) + 1 && i > 0) {
				directions[i] = left;
			}
			else {
				if (i % (strlen(s1) + 1 ) == 0 && i > 0) {
					directions[i] = up;
				}
				else {
					directions[i] = null;
				}

			}
		}
	}



	edit_distance_dyn_rec(s1, s2, 0, 0);

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

	int res = 0;
	int Icursor = strlen(s1) + 1;
	int Jcursor = strlen(s2) + 1;

	while (Icursor != 1 || Jcursor != 1)
	{
		if (directions[(Icursor - 1) * (strlen(s2) + 1) + (Jcursor)-1] == cross) {
			
			Icursor--;
			Jcursor--;
		}
		else {
			if (directions[(Icursor - 1) * (strlen(s2) + 1) + (Jcursor)-1] == up) {
				res++;
				Icursor--;
			}
			else {
				res++;
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