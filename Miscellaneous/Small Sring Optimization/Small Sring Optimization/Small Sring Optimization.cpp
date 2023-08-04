#include <iostream>
#include <string>

using namespace std;


int main()
{
    string name = "LolloLolloLolloLollo"; // allocating memory
    string nameShort = "Lollo"; // not allocating memory beacuse fit the criteria of a small string
    const char* name2 = "Lollo"; // not allocating memory
}

/*
* string use to slow down a program beacuse tend to allocate memory on the heap
* small string optimization use a buffer for string longer 15 char or less
* at the start of the programm a small amount of stack space is reserved for small string
* (mind that debug mode work different and could allocate anyway)
*/
