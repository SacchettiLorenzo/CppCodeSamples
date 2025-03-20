#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>

//it is possible to avoid the use of use namespace std by calling only what we are actually using
//using namespace std;
using std::cout, std::endl;

void know_your_algorithm();
void use_std_array();
template<std::size_t size>
void better_f(std::array<int, size>& arr) {}
void loop_map_items();
constexpr int compute_ahead(const int n);

int main()
{
    //using std::endl also flush the buffer and it takes extra time
    cout << "Hello World!" << endl;
    //using /n might be more convenient (in a loop for example)
    cout << "Hello World!\n";

    know_your_algorithm();
    loop_map_items();
}

//use algorithm that alrteady exist 
void know_your_algorithm() {
    const std::vector<int> data = { -1,-3,-5,8,16,-1 };

    //lambda function that return positive integer
    const auto is_positive = [](const auto& x) {return x > 0; };

    auto first_post_it = std::find_if(data.cbegin(), data.cend(), is_positive);

    cout << *first_post_it << endl;
}

//use std::array instead of c style array
void use_std_array() {
    const int n = 256;
    std::array<int, n> arr{};
    better_f(arr);
}

//use structure binding to avoid the use of first and second and be more clear
//structure binding work even for accepting a struct as return value
void loop_map_items() {
    std::unordered_map<std::string, std::string> colors = {
        {"RED", "#FF0000"},
        {"GREEN", "#00FF00"},
        {"BLUE", "#0000FF"}
    };

    for (const auto& [name, hex] : colors) {
        cout << "name: " << name << ", hex: " << hex << "\n";
    }
}

//if the value of n is knows ahead of time it might be evalueted at runtime
//add constexpr to tell the compiler to evalutate the function at compile time
constexpr int compute_ahead(const int n) {
    return n * (n + 1) / 2;
}

void default_vs_value_initialization() {
    //these variables are default initialied and therefore are filled with garbage
    //consider that id exist a default constructor it will be called (for std::string for example)
    int x;
    int* x2 = new int;

    //these variable are value initialized and therefore contain the value 0
    int y{};
    int* y2 = new int{};
    int* y3 = new int();
}

void smart_pointers() {
    struct Record {
        int id;
        std::string name;
    };

    auto customer = std::unique_ptr<Record>
}



