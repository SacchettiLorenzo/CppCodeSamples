#include <iostream>
#include <cstdarg>

using namespace std;

void simple_print(const char* fmt...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0')
    {
        if (*fmt == 'd') {
            int i = va_arg(args, int);
            cout << i << endl;
        }
        else if (*fmt == 'c') {
            int c = va_arg(args, int);
            cout << static_cast<char>(c) << endl; //static cast used for checking cast safety at compile time (casting used only for the example)
        }
        else if (*fmt == 'f') {
            double d = va_arg(args, double);
            cout << d << endl;
        }
        ++fmt;
    }

    va_end(args);
}

void generic_print() {

}

template <typename T, typename... Types>
void generic_print(T current, Types... others) {
    cout << current << endl;
    generic_print(others...);
    //passing a variadic set of arguments means that others[0] is managed by T and others[1] and subsequent are managed by Types
}

int main()
{
    simple_print("dcff", 3, 'a', 1.999, 42.5);
    generic_print(1, 2, 3.14,
        "Pass me any "
        "number of arguments",
        "I will print\n");
}

/* VARIADIC FUNCTIONS
*  are functions which take a variable number of arguments
*  the support for this dunctionality is provided by <cstdarg>
*
*   va_start: enable access to variadic function arguments
*   va_arg: accesses the next argument
*   va_copy: makes a copy of the variadic function arguments
*   va_end: ends traversal of varaidic function arguments
*   va_list: holds the information needed by start,arg,end
*
*   simple_print() work by providing the letter for the correct type in the first argument
*   generic_print() overload an empty function with template parameter and variadic template parameters.
        it call itself recursively passing the next set of parameters as argument for the function
        the ampty function in this case is needed to handle the base case (recursive function)
*/