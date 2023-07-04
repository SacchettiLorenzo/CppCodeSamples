#include <iostream>

int main()
{
    int array[5] = { 1, 2, 3, 4, 5 };
    size_t size = sizeof(array);

    printf("The size of the array is: %lu byte\n", size);
    printf("Every int is rapresented with 32 bit (4 byte) \n");

    return 0;
}

/* size_t
* It?s a type which is used to represent the size of objects in bytes and
    is therefore used as the return type by the sizeof operator.
    It is guaranteed to be big enough to contain the size of the biggest object the host system can handle.
     if the compiler is 32 bit then it is simply a typedef(i.e., alias) for unsigned int but
     if the compiler is 64 bit then it would be a typedef for unsigned long long.

     size_t is never negative so it is often used as variable for cycles.
     size_t is used to rapresent objects sizes so when it appear in the code it is probably referred to an object
*/

