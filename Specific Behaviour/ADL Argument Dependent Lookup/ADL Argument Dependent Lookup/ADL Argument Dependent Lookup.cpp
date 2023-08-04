#include <iostream>

namespace mynamaspace {
    class myclass {
    public:
        int value;
    };

    std::ostream& operator <<(std::ostream& os, const myclass& obj) {
        os << "myclass: " << obj.value;
        return os;
    }
}

int main()
{
    mynamaspace::myclass obj;
    obj.value = 42;
    using std::cout; // Required to use 'cout' without fully qualifying it.
    cout << obj << std::endl; // ADL is used to find the correct overloaded 'operator<<'.
}

//ADL argument dependent lookup
/*
* allow the compiler to search for the appropriate function to call based on the types of argument provided
* allow the compiler to find a function in the same namespace as the arguments even if the function is not declered at the point of use or
* within the namespace provided
* 
* the << operator is inside the namespace mynamespace so ADL is used to find the correct function defined for myclass
*/