

#include <iostream>

int main()
{
    bool b = true;
    std::cout << std::boolalpha << b << std::endl;
    std::cout << std::noboolalpha << b << std::endl;

    std::cout << std::endl;

    std::cout << std::boolalpha << (bool)1 << std::endl;
    std::cout << std::boolalpha << (bool)0 << std::endl;

    std::cout << std::endl;

    std::cout << std::noboolalpha << (bool)1 << std::endl;
    std::cout << std::noboolalpha << (bool)0 << std::endl;

    std::cout << std::endl;

    std::cout << std::boolalpha << 0 << std::endl;
    std::cout << std::boolalpha << 1 << std::endl;
}

/*  boolalpha let you change the rapresentation of booleans
*   you can rapresent them in textual or integral form
*   boolalpha will change all the occurencies in the stream but only the bollean ones
*   non boolean values will remain untouched
*/

