#include <iostream>

using namespace std;

//& lvalue reference declerator
//&& rvalue reference declerator

int main() {
	int var = 10;

	int& ref = var;

	cout << var << endl;
	cout << ref << endl;

	//changing ref but printing var
	ref = 20;
	cout << var << endl;

	//passing reference of the variable avoid the needence of a return value
	int x = 10;
	int y = 5;
	cout << "Before Swap: x = " << x << " y = " << y << endl; // Outputs 5 10
	swap(x, y);
	cout << "After Swap: x = " << x << " y = " << y << endl;  // Outputs 10 5
}

void swap(int& a, int& b) { //reference as parameters
	int temp = a;
	a = b;
	b = temp;
}

// reference
/*
* it is possible to use the reference just like the original variable; When the value of the reference change, the value of the original variable change too;
* it acts as an alias of the original variable
*/