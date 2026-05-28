#include <iostream>

using namespace std;

struct Accumulator
{
    Accumulator(int x) : counter(x) {} //constructor of the object
    int counter = 0;
    //overload the '()' operator
    int operator()(int i) { return counter += i; }
};



int main()
{
    Accumulator acc(5);
    cout << acc(10) << endl; //add "10"
    cout << acc(20) << endl; //add "20"
    cout << acc.counter << endl;
}


//
/*functor -> function object
* Functor:  A functor acts just like a function, but it has the advantages that it is stateful, meaning it can keep data reflecting its state between calls.
* functor are the most similar method to simulate a global function
* in the example the operator '()' known as "fuction call operator" is overloaded so when acc(n) in called the sum is performed on the value stored in acc.counter
* more in general it is possible to perform actions that are always needed when using callable, in this case using () will add i to counter
* https://www.youtube.com/watch?v=qcuYSqHxqLk
*/
