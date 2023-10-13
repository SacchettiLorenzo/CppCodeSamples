

#include <stdio.h> 
#include <iostream>
#define get_variable_name_name(var)  #var 

int main()
{
    int myVar = 10;
    printf("%s = %d \n", get_variable_name_name(myVar),myVar);

    return 0;
}