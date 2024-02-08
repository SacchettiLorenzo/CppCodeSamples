#include <iostream>

int values = 1000;


int main()
{
    int x = 1;
    __assume(x != 1);
    if (x == 1) {
        printf("live code\n");
    }
    else {
        printf("dead code\n"); //optimizing this part of the branch
    }

    
 
}

/*  __declspec is used to make some optimizations during compile time
*   The restrict declspec can only be applied to function declarations that return a pointer 
*   for example void *malloc(size_t size);
*   The restrict declspec gives the compiler more information for performing compiler optimizations
* 
*   The noalias declspec is also applied only to functions, and indicates that the function is a semi-pure function. 
*   A semi-pure function is one that references or modifies only locals, arguments, and first-level indirections of arguments.
* 
*   Those declspec are promises to the compiler. The compiler won't perform any venification on that
*   //more __declspec modifier on the documentation
*
*   __restrict and __declspec(restrict) are two different things.
* 
*   __assume tell the compiler that a variable should assume a certain value
*   so some optimization can be done
* 
*   A pointer that is modified with __restrict is referred to as a __restrict pointer. 
*   A __restrict pointer is a pointer that can only be accessed through the __restrict pointer. 
*   In other words, another pointer cannot be used to access the data pointed to by the __restrict pointer.
* 
*   All of those optimization keyword are for the MSVC compiler
* 
*  //example for __declpec and rectrict to be added
*/


