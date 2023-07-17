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



int main()
{
    float f = 3.5;

    int a = f;  //implicit cast
    std::cout << "the value of a: " << a << std::endl;

    int b = static_cast<int>(f);
    std::cout << "the value of b: " << b << std::endl;

    //CONVERTION OF POINTERS -------------------------------------------
    int c = 10;
    char d = 'a';

    int* q = (int*)&d; //pass at compile time but may fail at run time; typecasting pointer can produce weird behaviour
    std::cout << *q << std::endl;
    //int* p = static_cast<int*>(&d); //not permitted at compile time
    int* p = static_cast<int*>(&c); //permitted at compile time
    std::cout << *p << std::endl;
    //-------------------------------------------

    //USER DEFINED CONVERSION OPERATOR-------------------------------------------
    // Converting an Object using a User-Defined Conversion Operator
    //without the user defined conversion operator the conversion integet->strig does not exist.
    integer obj(3);
    std::string str = obj;
    obj = 20;

    // using static_cast for typecasting
    std::string str2 = static_cast<std::string>(obj); //the affect are the same as "std::string str = obj;" but static cast perform a tight type checking of the returned value;
    obj = static_cast<integer>(30);
    //-------------------------------------------

    //UPCASTING -------------------------------------------
    Derived d1;

    // Implicit cast allowed
    Base* b1 = (Base*)(&d1);

    // upcasting using static_cast
    Base* b2 = static_cast<Base*>(&d1);
    //-------------------------------------------

    //TO AND FROM VOID TYPE CONVERISON-------------------------------------------
    int i = 10;
    void* v = static_cast<void*>(&i);//void type accept every type
    int* ip = static_cast<int*>(v);//every type accept a void type value
    std::cout << *ip;
    //-------------------------------------------
}

/*
* static type cast perform explicit type conversion.
* static_cast<type> (object);
* The type parameter must be a data type to which object can be converted via known method.
*
* static_cast<> operator can be used for converting numeric data type such as enum to int or float or for
* converting a derived class pointer to a base class pointer (losing the derived class specific member)
*
* if the requested conversion in not known it must be defined in the newly created class
*
* static_cast conversions are checked at compile time to prevent obvious incompatibilities. in this way static cast are safe at run time
*/

