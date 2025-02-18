#include <iostream>
#include "pch.h" //precompiled header file that inlcude a lot of code

int main()
{
    std::cout << "Hello World!\n";
}

/*
precompiled header are used to keep most of the unmodified code already compiled in order to
decrease the compilation time. this in particularly usefull with big header file.
it make sense to make a precompiled header if the header file won't be touched again in the future.
in this way it is possible to compile only the newer code

all the code that is containd in STL or in windows.h will harldly be modified so it make senso to precompile it.
the precompiled header should be used when the code contained in the header are broadly used

follow the instruction in pch.cpp to create a precompiled header 
*/