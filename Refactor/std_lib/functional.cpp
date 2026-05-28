#include <iostream>
#include <functional>

double my_divide(double x, double y) { return x / y; }

int main()
{
    auto fn_five = std::bind(my_divide, 10, 2);
    std::cout << fn_five() << std::endl;

    auto fn_half = std::bind(my_divide, std::placeholders::_1, 2);
    std::cout << fn_half(10) << std::endl;

    auto fn_divide = std::bind(my_divide, std::placeholders::_1, std::placeholders::_2);
    std::cout << fn_divide(100,7) << std::endl;

}

//std::bind return a function object that can be called afterwards
//std::bind supports the use of std::placeholder in order to let the callable object add parameters

