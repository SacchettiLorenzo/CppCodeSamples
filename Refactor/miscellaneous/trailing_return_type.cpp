#include <iostream>

int main() {

	auto func_name(int x, int y) -> int;

    // same as
    // int func_name(int x, int y);

    //the return type of a lambda function is expressed using the trailing return type syntax
    //even if the compiler can actually deduce (in most case) the return type from the returned expression
    auto lambda = []() -> int {
        return 42;
    }

}

