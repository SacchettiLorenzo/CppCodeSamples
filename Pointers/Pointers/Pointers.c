#include <stdio.h>

//c++ = 0
//c   = 1
#define language 1

typedef struct {
    int x;
    int y;
}point;

void addone(int* n);
void move(point* p);

#if language == 0
void addtwo(int& n);
#endif

int main()
{
    int a = 1;

    int* pointer_to_a = &a; //&a generate a pointer to a; the type int* can hold the pointer;
    printf("The value a is %d\n", a);
    printf("The value of a is also %d\n", *pointer_to_a); // *pointer_to_a is used to acces the variable a

    a += 1;
    *pointer_to_a += 1; // same operation

    printf("The value of a is now %d\n", a);

    //with pointer is possible to access memory-adress outside the function scope
    // in this case if we had used a function without a pointer we should have used a return statement
    int n = 0;
    printf("Before: %d\n", n);
    addone(&n);
    printf("After: %d\n", n);


    point p; //struct with new type definition
    move(&p); // the function has access to p struct

#if language == 0
    //alias of a variable (only work in c++)
    int& alias = a; // alias in a
    addtwo(a);
    printf("%d\n", a);
#endif
}

void addone(int* n) {
    // n is a pointer here which point to a memory-adress outside the function scope
    (*n)++; // this will effectively increment the value of n
}

#if language == 0
void addtwo(int& n) {
    n = n + 2; //alias of a, no need to use pointer
}
#endif

void move(point* p) {
    (*p).x++;
    (*p).y++;
}