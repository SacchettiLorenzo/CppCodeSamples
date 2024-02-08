

#include <iostream>

int main()
{
    struct S {

    };

    std::cout << sizeof(S) << std::endl;

    //S_1 look like the following:
    //iiiicc**
    struct S_1 {
        int b; //4 bytes
        char a; //1 byte
        char c; //1 byte
    };

    std::cout << sizeof(S_1) << std::endl;

    //S_1 look like the following:
    //c***iiiic***
    struct S_2 {
        char a;
        int b;
        char c;
    };

    std::cout << sizeof(S_2) << std::endl;
}

//Assuming the usage of multiple data type inside one single structure
//the memory is alligned at the 8th byte for each data type
//the compiler will add a padding after the type changed to allign with the 8th byte
//the empty struct occupies 1 byte

