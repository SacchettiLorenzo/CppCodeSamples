#include <iostream>

using namespace std;

void HelloWord() {
    cout << "Hello word!" << endl;
}

void HelloWord2(int a) {
    cout << "Hello word!" << a << endl;
}

int main()
{
    auto function = &HelloWord;

    void(*function2)(/*parameters*/) = &HelloWord;

    typedef void(*Function3)();
    Function3 function3 = HelloWord;

    typedef void(*Function4)(int);
    Function4 function4 = HelloWord2;

    function();
    function2();
    function3();
    function4(42);
}

/*
* function pointer allow to assign a function to a variable
*
* the compiler will assign a void pointer type to the variable if the auto keyword is used
*
* it is possible to define a type to assign a function to, in this way the reference assignement is not needed
*/

