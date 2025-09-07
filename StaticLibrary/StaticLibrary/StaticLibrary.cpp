
#include <iostream>
#include "MathLibrary.h"


int main()
{
    std::cout << MathLibrary::Arithmetic::Add(5 , 5)<<std::endl;
    std::cout << MathLibrary::Arithmetic::Subtract(5, 5)<<std::endl;
    std::cout << MathLibrary::Arithmetic::Multiply(5, 5)<<std::endl;
    std::cout << MathLibrary::Arithmetic::Divide(5, 5)<<std::endl;
}
