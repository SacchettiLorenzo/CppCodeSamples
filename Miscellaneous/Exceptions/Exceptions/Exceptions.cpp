#include <iostream>
#include <stdexcept>

using namespace std;

int divide(int a, int b) {
    if (b == 0) {
        throw runtime_error("Divide by 0");
    }
    return a / b;
}

void foo() noexcept   // noexcept 
{
    throw 42; // the exception is not handled so the program terminate
}

void bar() {
    throw runtime_error("42");
}

int main()
{
    int num1 = 10, num2 = 1;

    try {
        int result = divide(num1, num2);
        cout << "Result: " << result << endl;
    }catch(const exception& e) { //catch every exemption
        cerr << "Error: " << e.what() << endl;
    }


    try {

    int arr[5] = { 1, 2, 3, 4, 5 };
    int index = 5;
    if (index >= (sizeof(arr) / sizeof(int))) {
        throw out_of_range("out of bound");
    }
    int y = arr[index];
    }
    catch(const exception& e){
        cout << e.what() << endl;
    }
    
    foo(); // call the function with noexcept so the exception in not handled

    try
    {
        foo(); // the exception is handled only outside the function so the program stop anyway
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    try
    {
        bar(); //the exception is thrown and handled outside
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    

   
}

//exceptions
/*
* exceptions library provide ad interface to handle errors through the throw exception expression
* by default only some errors of the functions or classes throw an exception
* every possible exception should be handled manualy via if statement and throw exception expression
* 
* exception mainly divide in 2 types: logic_error and runtime_error
* to see the complete list visit the c++ reference 
* 
* one of the most popular error is the access violation that occur when trying to access an array out of bound, dereferencing null or invalid pointer, reading or writing freed memory
*
* noexcept specifies a function that doesen's throw exception or terminate the program if an exception is thrown within his scope
*/

/* exit codes:
*  0 is standard exit code for successful execution
*  non-0 indicate error or exeptions
*  to see the complete list visit the c++ reference 
*/

