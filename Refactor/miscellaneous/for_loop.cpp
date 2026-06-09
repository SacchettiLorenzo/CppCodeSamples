#include <vector>
#include <iostream>

int main(){
    std::vector<int> v = {1, 2, 3, 4};
    for(size_t i{}; i< v.size(); ++i){
        std::cout << "Hello World" << std::endl;
    }

    /* c++ 23
    for(size_t i{0uz}; i< v.size(); ++i){
        std::cout << "Hello World" << std::endl;
    }

    for(auto i = 0uz; i != std::ssize(v); i++){
        std::cout << "Hello World" << std::endl;
    }

    for (std::size_t i{}; i[v] || true; i += !!"C++"){
        if (i == v.size()) break;
        else std::cout << "Hello World\n";
    } 
    */
    

    for(auto i{v.size()}; i-- > 0;){
        std::cout << "Hello World" << std::endl;
    }

    for (decltype(v.size()) i{}; i < v.size(); i = -~i){
        std::cout << "Hello World" << std::endl;
    }

    //this block is evaluated ad expanded at compile time 
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    ((std::cout << "Hello World\n"), ...);
    }(std::make_index_sequence<v.size()>{});


    

}

//std::make_index_sequence<5>{} produces std::index_sequence<0, 1, 2, 3, 4>

