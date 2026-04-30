#include <iostream>
#include <string>

using namespace std;

// new class
class integer {
	int x;

public:
	// constructor
	integer(int x_in = 0)
		: x{ x_in }
	{
		cout << "Constructor Called" << std::endl;
	}


	// user defined conversion operator to string type
	operator std::string()
	{
		cout << "Conversion Operator Called" << std::endl;
		return std::to_string(x);
	}
};

class Base
{
public:
	virtual void display() {
		std::cout << "BaseClass" << std::endl;
	}
};
class Derived : public Base
{
public:
	void display() {
		std::cout << "DerivedClass" << std::endl;
	}
	int onemorevariable;
};

class Entity {
public:
	virtual void Printname() {}
};

class Player : public Entity {

};

class Enemy : public Entity {
	
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
	cout << *q << std::endl;
	//int* p = static_cast<int*>(&d); //not permitted at compile time
	int* p = static_cast<int*>(&c); //permitted at compile time
	cout << *p << std::endl;
	//-------------------------------------------------------------------------

	//STATIC CAST -----------------------------------------------------------------------------------------------------

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
	cout << *ip <<endl;
	//-------------------------------------------------------------------------

	//int to enum -------------------------------------------------------------
	enum Color {RED,GREEN,BLUE};
	int colorValue = 1;
	Color color = static_cast<Color>(colorValue);
	//-------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------
	//CONST CAST ------------------------------------------------------------------------------------------------------
	const int original_value = 10;
	int* non_const_value_ptr = const_cast<int*>(&original_value);
	cout << "Original value: " << original_value <<endl;
	*non_const_value_ptr = 42;
	cout << "Modified value: " << *non_const_value_ptr << endl;
	//int* ciao = &original_value; non possible operation
	//-----------------------------------------------------------------------------------------------------------------
	//DYNAMIC CAST ----------------------------------------------------------------------------------------------------
	Base* basePtr = new Derived(); //upcasting

	Derived* derivedPtr;
	derivedPtr = dynamic_cast<Derived*>(basePtr); //downcasting

	if (derivedPtr) {
		derivedPtr->display();
	}
	else {
		cout << "invalid type conversion" << endl;
	}

	delete basePtr;

	//-----------------------------------------------------------------------------------------------------------------
	//REINTERPRET CAST ------------------------------------------------------------------------------------------------
	int num = 42;
	int* num_ptr = &num;

	// Disguise the integer pointer as a char pointer
	char* char_ptr = reinterpret_cast<char*>(num_ptr);

	for (size_t i = 0; i < sizeof(int); ++i) {
		// Print the individual bytes of the integer as characters
		std::cout << "Byte " << i << ": " << char_ptr[i] << std::endl;
	}


	//-----------------------------------------------------------------------------------------------------------------

	

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
/* const cast
* this cast allow to remove or add constness to a variable
* allow to modify or change the pointer or reference to a const object or type
* this feature can lead to undefined behavior so it is best to use only when absolutely necessary
* without const_cast is impossible to assign a constant pointer to a non constant variable
*/

/* dynamic cast
* it is used specifically for polymorphism.
* it safely converts and references of a base class to its derived class and checks the validity of the conversion during runtime
* if the conversion is not valid it return a null pointer instead of un undefined behaviour
* it is mainly used for inheritance casting (updasting and downcasting)
* This is possible thank to RTTI (Run Time Type Information) that keep infromation about types and class
* dynamic cast take more time to perform than an implicit cast because it check if the types are compatible
* if types are not compattible the programm will not crash
*/

/* reinterpret cast
* change the type of a pointer or an interger without altering the rapresentation of the data
* it is generally used when conversion is too low-level or  non suported by other cast method
* can lead to undefined behavior.
* can lead to problem such accessing memory regions that are not intended to be accessed.
*/

//arithmetic conversion hierarchy
// the compiler can promote a data type in this order
// int -> unsigned int -> long -> long logn -> unsigned long logn -> float -> double -> long double;
// trying the conversion in different order will cause lose of data
