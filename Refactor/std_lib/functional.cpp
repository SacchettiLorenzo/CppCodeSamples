#include <iostream>
#include <functional>
#include <string_view>

double my_divide(double x, double y) { return x / y; }

bool is_same(int a, int b){return a == b;}

int main()
{

    std::function<double(double,double)> f = my_divide;
    std::cout << f(10,2) << std::endl;

    auto fn_five = std::bind(my_divide, 10, 2);
    std::cout << fn_five() << std::endl;

    auto fn_half = std::bind(my_divide, std::placeholders::_1, 2);
    std::cout << fn_half(10) << std::endl;

    auto fn_divide = std::bind(my_divide, std::placeholders::_1, std::placeholders::_2);
    std::cout << fn_divide(100,7) << std::endl;

    auto is_differ = std::not_fn(is_same);
    auto k = is_differ(1,2);

    constexpr std::string_view in =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
        "do eiusmod tempor incididunt ut labore et dolore magna aliqua";

        const std::string_view needle{"pisci"};

    auto it = std::search(in.begin(), in.end(),std::default_searcher(needle.begin(), needle.end()));

}

//std::function can store, copy and invoke any copyconstructible callable target function via pointers

//std::plus, std::minus, std::multiplies, std::divides, std::modulus, std::negate
//implements function objects for the arithmetic operations (in this way it is possible to pass them as callable objects)

//std::equal_to, std::not_equal_to, std::greater, std::less, std::greater_equal, std::less_equal
//implements function objects for the comparison operator (in this way it is possible to pass them as callable objects)

//std::logical_and, std::logical_or, std::logical_not
//implements function objects for the logical operations (in this way it is possible to pass them as callable objects)

//std::bit_and, std::bit_or, std::bit_xor, std::bit_not
//implements function objects for the bitwise operations (in this way it is possible to pass them as callable objects)

//std::not_fn create a function object that return the complement of the result of the function object it holds

//std::default_searcher return a pair of iterators pointing to the first and the one past last of the sequence to search, it is used to inject arbitrary search strategy to a generic search functionality
// it can be changed with std::boyer_moore_searcher or std::boyer_moore_horspool_searcher for enhnaced performance on substrig searcing

//std::bind return a function object that can be called afterwards
//std::bind supports the use of std::placeholder in order to let the callable object add parameters

