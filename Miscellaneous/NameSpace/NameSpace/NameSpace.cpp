#include <iostream>

namespace space {
    void function() {
        std::cout << "i'm using a function in a namespace" << std::endl;
    }
}

int main()
{
    //function(); function is not part of the scope
    space::function();

    using namespace space;//use the entire namespace
}

/*
* namespace are names for scopes
* a class is also a namespace
*/


