#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

	

	vector<int> v{ 2, 3, 7, 14, 23 };
	for_each(v.begin(), v.end(), [](int x) {cout << x << endl; }); //function fron algorithm library / for each element execute lambda function
	//[](int x) {cout << x << endl; } //lambda function that print 


	//longer lambda function
	vector<int> v1{ 1, 2, 3, 4, 5 };
	for_each(v1.begin(), v1.end(), [](int x) {
		if (x % 2 == 0) {
			cout << x << " is even number" << endl;
		}
		else {
			cout << x << " is odd number" << endl;
		}
		}); //function fron algorithm library / for each element execute lambda function
	//[](int x) {cout << x << endl; } //lambda function that print 


	//if there is the needence to use more variable in the lambda expression
	int d = 3;
	vector<int> v2{ 1, 2, 3, 4, 5 };
	for_each(v2.begin(), v2.end(), [d](int x) {
		if (x % d == 0) {
			cout << x << " is divisible by " << d << endl;
		}
		else {
			cout << x << " is not divisible by " << d << endl;
		}

		});
	//inside the lambda expression is not possible to change values passend by value but only by reference(passing the pointer to the varaible)



	for_each(v2.begin(), v2.end(), [&](int x) {cout << d << endl; }); // "&" in capture clause means that all the variable are passed by reference (so the value can chage inside the lambda expression)
	for_each(v2.begin(), v2.end(), [=](int x) {cout << d << endl; }); // "=" in capture clause means that all the variables are passed by value (so the value can not change inside the lambda expression)


}


//lambda, is an anonymous(unnamed) function that is defined in place
// it is not ment to be reused like regular functions
//in this way it is possible to avoid the use of a function that need to be declered in a header file just to be used one time
/*
* [] capture clause for variables that comes from outside the calling function
* [&] variable are aquired by reference
* [=] variable are aquired by value
* it is possible to define capture clause for each variable [&a, =b]
* () parameters for varaibles that comes from inside the calling function
* {} function definition

*/