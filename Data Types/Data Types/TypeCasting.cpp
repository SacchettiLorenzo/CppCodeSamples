#include <iostream>
#include <string>

// new class
class integer {
	int x;

public:
	// constructor
	integer(int x_in = 0)
		: x{ x_in }
	{
		std::cout << "Constructor Called" << std::endl;
	}

	// user defined conversion operator to string type

	operator std::string()
	{
		std::cout << "Conversion Operator Called" << std::endl;
		return std::to_string(x);
	}
};

class Base
{
};
class Derived : public Base
{
public:
	int onemorevariable;
};

int main() {

	//implicit conversion
	short a = 10;
	int b;
	b = a;

	// explicit conversion
	float f = 3.14f;
	auto af = (int)f;

	//CONVERTION OF POINTERS --------------------------------------------------
	int c = 10;
	char d = 'a';

	int* q = (int*)&d; //pass at compile time but may fail at run time; typecasting pointer can produce weird behaviour
	std::cout << *q << std::endl;
	//int* p = static_cast<int*>(&d); //not permitted at compile time
	int* p = static_cast<int*>(&c); //permitted at compile time
	std::cout << *p << std::endl;
	//-------------------------------------------------------------------------

	//STATIC CAST

	//USER DEFINED CONVERSION OPERATOR ----------------------------------------
	// Converting an Object using a User-Defined Conversion Operator
	//without the user defined conversion operator the conversion integet->strig does not exist.
	integer obj(3);
	std::string str = obj;
	obj = 20;

	// using static_cast for typecasting
	std::string str2 = static_cast<std::string>(obj); //the effect are the same as "std::string str = obj;" but static cast perform a tight type checking of the returned value;
	obj = static_cast<integer>(30);
	//-------------------------------------------------------------------------

	//UPCASTING ---------------------------------------------------------------
	Derived d1;

	// Implicit cast allowed
	Base* b1 = (Base*)(&d1);

	// upcasting using static_cast
	Base* b2 = static_cast<Base*>(&d1);
	//-------------------------------------------------------------------------

	//TO AND FROM VOID TYPE CONVERISON ----------------------------------------
	int i = 10;
	void* v = static_cast<void*>(&i);//void type accept every type
	int* ip = static_cast<int*>(v);//every type accept a void type value
	std::cout << *ip;
	//-------------------------------------------------------------------------

	//int to enum -------------------------------------------------------------
	enum Color {RED,GREEN,BLUE};
	int colorValue = 1;
	Color color = static_cast<Color>(colorValue);
	//-------------------------------------------------------------------------

}
// implicit and explicit type casting
/*
* implicit casting:
* conversion of data types without losing its original meaning
* the implicit type conversion always happen with compatible type and without any casting keyword
* short to int do not lose meaning
* char to int lose meaning
* 
* explicit casting:
* the type is specified in the brackets (typename)
* the cast is performed anyway even with data los
*/
 
/* static cast
* static type cast perform explicit type conversion
* static_cast<type> (object)
* The type parameter must be a data type to which object can converted via known method;
* This type of conversion perform a compile-time check and gives an error if there is no valid conversion possible between given types;
* it is generally safer than implicit or explicit cast but not always needed
* static_cast conversions are checked at compile time to prevent obvious incompatibilities. in this way static cast are safe at run time
* static_cast<> operator can be used for converting numeric data type such as enum to int or float or for
* converting a derived class pointer to a base class pointer (losing the derived class specific member)
* if the requested conversion in not known it must be defined in the newly created class
* 
*/ 
// const cast
// dynamic cast
// reinterpret cast

//arithmetic conversion hierarchy
// the compiler can promote a data type in this order
// int -> unsigned int -> long -> long logn -> unsigned long logn -> float -> double -> long double;
// trying the conversion in different order will cause lose of data
