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
    */
    

    for(auto i{v.size()}; i-- > 0;){
        std::cout << "Hello World" << std::endl;
    }   
}

