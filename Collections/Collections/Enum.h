#pragma once
#include <iostream>
enum Example1{A,B,C};
enum Example2{D = 10, E = 20, F = 30};
enum Example3 : unsigned char { G, H, I };
enum Example4 : unsigned int{ J, K, L };
enum Example5 : char { M, N, O };

void PrintEnum();