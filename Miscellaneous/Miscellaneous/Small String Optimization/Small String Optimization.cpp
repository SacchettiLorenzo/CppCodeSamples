#include <iostream>
#include <string>

using namespace std;


int main()
{
    string name = "LolloLolloLolloLollo"; // allocating memory
    string nameShort = "Lollo"; // not allocating memory beacuse fit the criteria of a small string
    const char* name2 = "Lollo"; // not allocating memory

    const char* Literal = "This is a String literal";
    //*Literal = 'A'; do not work

    cout << Literal << endl;
    printf("%s\n", Literal);
    printf("%c\n", *(Literal + 3));

    char CharArray[] = "This is a Char array";
    CharArray[5] = 'q';

    char* ptr = CharArray;
    ptr = ptr + 3;
    *ptr = '1';

    cout << CharArray << endl;
    printf("%c\n", *(CharArray + 3));
}

/*
* string use to slow down a program beacuse tend to allocate memory on the heap
* small string optimization use a buffer for string long 15 char or less
* at the start of the programm a small amount of stack space is reserved for small string
* (mind that debug mode work different and could allocate anyway)
*
* String Literal vs array of char
*
* String Literal:
* sequence of read only character; dereferencing and reassignement will cause a memory access violation / segmentation fault
*
* Array of char:
* allocates memory and copy the assigned value so it can be modified
*
* both array and Literal are accessible by poiters and end with '\0' character but only array of char can be modified
* 
* The number of char suitable for small string optimization depend on the architecture of the machine.
* On a 64 bit architecture we could have 3 words string optimization or 24 byte. 
* The commiper usually add information that could use 1 or 2 bytes. The total size could be (24-something) buytes
*/
