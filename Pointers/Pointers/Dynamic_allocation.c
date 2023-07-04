#include <stdio.h>
#include <stdlib.h>

void someFunction(int arg)
{
	printf("This is someFunction being called and arg is: %d\n", arg);
	printf("Whoops leaving the function now!\n");
}

int main() {
	typedef struct {
		char* name;
		int age;
	} person;

	person* myperson = (person*)malloc(sizeof(person)); //This tells the compiler that we want to dynamically allocate just enough to hold a person struct in memory and then return a pointer of type person to the newly allocated data.
	// malloc return void so (person*) is a typecast top a type holding person pointer

	myperson->name = "John";
	myperson->age = 27;

	printf("The age a is %d\n", (*myperson).age);
	printf("The age a is %d\n", myperson->age); // same way to access data
	free(myperson);

	char vowels[] = { 'A', 'E', 'I', 'O', 'U' };
	char* pvowels = vowels;
	int i;

	// Print the addresses
	for (i = 0; i < 5; i++) {
		printf("&vowels[%d]: %p, pvowels + %d: %p, vowels + %d: %p\n", i, &vowels[i], i, pvowels + i, i, vowels + i);
	}

	// Print the values
	for (i = 0; i < 5; i++) {
		printf("vowels[%d]: %c, *(pvowels + %d): %c, *(vowels + %d): %c\n", i, vowels[i], i, *(pvowels + i), i, *(vowels + i));
	}

	//&vowels[i] and pvowels + i are equivalent so 
	//char* pvowels = vowels; the pointer to array actually point to the first element of the array
	printf(" %d\n", pvowels + 1);
	printf(" %d\n", &vowels[1]);

	//we can dynamically allocate (contiguous) memory using blocks pointers. in this way is possible to allocate new memory at runtime
	int n = 5;
	char* pvowelsb = (char*)malloc(n * sizeof(char));
	pvowelsb[0] = 'A';
	pvowelsb[1] = 'E';
	*(pvowelsb + 2) = 'I';
	pvowelsb[3] = 'O';
	*(pvowelsb + 4) = 'U';

	//pointer to function
	void (*pf)(int);
	pf = &someFunction;
	(pf)(5);
}