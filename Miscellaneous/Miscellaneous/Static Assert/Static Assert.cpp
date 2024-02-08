#include <iostream>

using namespace std;

class testClass {
public:
    static const int version = 2;
};

int main()
{
    //static_assert(sizeof(void*) == 4, "64-bit code generation is not supported.");
    
    static_assert(testClass::version > 2, "Old version of test class, cannot proceed");

}

/* 
*   check an expression at compile time
*   if the expression return false the error message is raised and the programm won't compile
* 
*   it is usefull when we have to check that the sysytem we are compiling on has some characteristics
*   for example if the system use  64 or 32 bit pointers 
*   or if the classes wse are working on are up to date
*/