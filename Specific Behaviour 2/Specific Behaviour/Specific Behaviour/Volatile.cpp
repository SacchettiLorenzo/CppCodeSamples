#include <iostream>

int main() {

	// considering the code 

	int some_int = 100;

	while (some_int == 100)
	{
		//your code
	}

	// if in the whole program the variable some_int never change the compiler will optimize the program to avoid to check some_int == 100 every time with the following:

	while (true)
	{
		//your code
	}

	// if something else that the compiler is not aware of will change the value of some_int the optimization could be undesirable so it may be defined as follow

	volatile int some_other_int = 100;

	while (some_other_int == 100)
	{
		//your code
	}

	// in this way the program will always perform the comparision

}

// volatile avoi aggressive optimization involving object because the value of the object might be changed by others undetectable programs