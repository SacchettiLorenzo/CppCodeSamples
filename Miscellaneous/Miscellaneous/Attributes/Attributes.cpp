#include <iostream>
#include <time.h>
#include <memory>
#include <chrono>

using namespace std;



[[deprecated("reason for deprecation")]]
void Foo(int num);

[[noreturn]] void f() {

}

void g()
{
	std::cout << "Code is intended to reach here";
}

int main()
{
	//Foo(42); //compilation errore  [[deprecated]]

	int unused = 10;
	[[maybe_unused]] int unusedvar = 10;

	int data = 1;
	switch (data)
	{
	case 1:
		[[fallthrough]];
	[[likely]] case 2: cout << data << endl;
	[[unlikely]] case 3: cout << data << endl;
	default:
		break;
	}

	int x = 10;
	if (x == 10) {
		[[likely]];
		//do something
	}

	//f();
	//g();


}

/*
* consist in additional informations for the compiler.
* the compiler will add special logic when compiling attribute code providing optimization
* most of the attributes come with c++ 20
* it is possible to write costom attribute that will be skipped by the compiler
*
* [[deprecated]]: will cause a compilation error due to use of deprecated functions. (function not intended for use or it might not exist in future version)
* [[likely]]: hint for the compiler that the code path for the attributed lebel is more likely one then others
* [[unlikely]]: hint for the compiler that the code path for the attributed lebel is more unlikely one then others
* [[fallthrough]]: if in a switch case there are cases without break, the execution jump to the next case; the compiler may rise a warning.
	the attribute disable the warning assuming the intentional behaviour. In normal situation fallthrough is not ok for the programm logic flow
* [[maybe_unused]]: tell the compiler that the element could be not used avoiding the generation of warning;
* [[noreturn]]: the code does not return the control to the caller. At the end it retunr without a value; a function noes not return if it enter a ifinite loop for example
*
* //other attributes on the c++ documentation
*/

void Foo(int num) {
	cout << num << endl;
}


