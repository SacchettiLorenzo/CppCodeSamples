#include <stdio.h> 
#include <iostream>

//variable definition
#define VARIABLE 10

//variable undefinition
#undef VARIABLE

//function definition
#define SQUARE(x) x*x

//definig a function that return the name of the function
#define get_variable_name_name(var)  #var 

//if the function SQUARE is non define it is defined here
#ifndef SQUARE
#define SQUARE(x) x*x
#endif // !SQUARE

//if the function SQUARE is defined set SQAREISDEFINED true
#ifdef SQUARE
#define SQAREISDEFINED true
#endif // !SQUARE

// normale if else statement
#if VARIABLE == 10
#rdefine VARIABLE  20
#else
#undef VARIABLE
#define VARIABLE  30
#endif

//variadic macro 
#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }

//checking for operative system
#ifdef __linux__ // __ANDROID__ - __linux__ - __APPLE__ - _WIN32 - _WIN64 (and others)
//do something
#endif

//checking for compiler
#ifdef _MSC_VER // __GNUC__ - __clang__ - __MINGW32__ - __MINGW64__
//do something
#endif



int main()
{
    int myVar = 10;
    printf("%s = %d \n", get_variable_name_name(myVar), myVar);
    printf("%d \n\n", VARIABLE);

    printf("file name: %s \n", __FILE__);
    printf("at line: %d \n", __LINE__);
    printf("time: %s \n", __TIME__);
    printf("date: %s \n", __DATE__);
    printf("name fo this function: %s \n", __func__);

    CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");

    //other option are available depending on the c++ version and refere to some of the behaviour that the program could have
    //there are option available only for microsoft that provides informations about the compilation

    //Some microsoft only usefull macro

    // __COUNTER__ is incremented by 1 every time it is used in the whole programm,
    // it can be used to create simple unique id for automatically created object
    printf("count: %d \n", __COUNTER__);
    printf("count: %d \n", __COUNTER__);

    //_debug id defined as 1 if the programm is compiled for debugging
    printf("debug version: %d \n", _DEBUG);

    //current function name in different forms
    printf("Function name: %s\n", __FUNCTION__);
    printf("Decorated function name: %s\n", __FUNCDNAME__);
    printf("Function signature: %s\n", __FUNCSIG__);

    //max integer dimension in bit
    printf("max number of bit for integers: %d\n", _INTEGRAL_MAX_BITS);

    //compiler version
    printf("compiler version: %i\n", _MSC_VER);
    printf("complete compiler version: %i\n", _MSC_FULL_VER);

    //timestamp
    printf("timestamp: %s \n", __TIMESTAMP__);






    return 0;
}