#include <iostream>
#include <typeinfo>
#include <string>

#define VERSION 17


#if VERSION == 17
#include <any>
#include <variant>
#endif
#include <vector>

using namespace std;

class Base {virtual void dummy(){} };
class Derived : public Base {};

int main()
{
     //ALL DATA TYPES ------------------------------------
    int num = 42;
    float pi = 3.14f;
    double pi_high_precision = 3.1415926535;
    char letter = 'A';
    bool is_cpp_great = true;

    //Structures are used to group variables of different data types together under a single name.
    //usually structs use padding to allign data at the 8th byte. padding is added at runtime
    struct Person {
        string name;    //40
        int age;        //4
        float height;   //4
    };

    cout << "Person size: " << sizeof(Person) << endl;
    cout << "Person allignment: " << alignof(Person) << endl;

    //it is possible to define a custom allignement (power of 2)
    struct alignas(32) PersonCustomAllignment {
        string name;    //40
        int age;        //4
        float height;   //4
    };

    cout << "PersonCustomAllignment size: " << sizeof(PersonCustomAllignment) << endl;
    cout << "PersonCustomAllignment allignment: " << alignof(PersonCustomAllignment) << endl;

    Person p1 = { "John Doe", 30, 5.9 };
    
    //Unions are used to store different data types in the same memory location. Only one member can contain a value at any given time.
    union Data { 
        int num;
        char letter;
        float decimal;
    };


    Data myData;
    myData.num = 42;
    myData.decimal = 13.2f;
    cout << "Union: " << myData.num << endl; //print a value without any meaning because myData.num has been partially overwritten



    // size_t --------------------------------------------------
    int array[5] = { 1, 2, 3, 4, 5 };
    size_t size = sizeof(array);
    printf("The size of the array is: %lu byte\n", size);
    printf("Every int is rapresented with 32 bit (4 byte) \n");

    //void*---------------------------------------------
    int x = 42;
    float y = 3.14f;
    std::string z = "Hello, world!";

    void* void_ptr;

    void_ptr = &x;

    cout << "int value: " << *(static_cast<int*>(void_ptr)) << endl;

    cout << *(int*)void_ptr << endl; //same thing but implicit

    void_ptr = &y;

    cout << "float value: " << *(static_cast<float*>(void_ptr)) << endl;
    
    void_ptr = &z;

    cout << "string value: " << *(static_cast<string*>(void_ptr)) << endl;


#if VERSION == 17
    //any --------------------------------------
    
    any any_value;

    any_value = 42;
    cout << "int value: " << any_cast<int>(any_value) << endl;

    any_value = 3.14;
    std::cout << "double value: " << std::any_cast<double>(any_value) << std::endl;

    any_value = std::string("Hello, world!");
    std::cout << "string value: " << std::any_cast<std::string>(any_value) << std::endl;

    //variant --------------------------------------
    variant<int, string> data;
    data = 2;
    data = "Lollo";
    string s = get<string>(data);
   // string s2 = any_cast<string>(data);
#endif

    //typeid -------------------------------
    Base* base_ptr = new Derived;
    
    cout << "type: " << typeid(*base_ptr).name() << endl;
    cout << "type: " << typeid(any_value).name() << endl;
    //cout << "type: " << typeid(*void_ptr).name() << endl; do not work
    cout << "type: " << typeid(x).name() << endl;
    cout << "type: " << typeid(Base).name() << endl;
    if (typeid(*base_ptr).name() == typeid(Derived).name()) {
        cout << "Found!!!" << endl;
    }

    //auto --------------------------------------
    auto myint = 5;

    vector<int> myvector = { 1,2,3,4,5 };
    
    //standard use of iterator
    for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
        cout << *it << endl;
    }

    //with auto
    for (auto it = myvector.begin(); it != myvector.end(); ++it) {
        cout << *it << endl;
    }
    /*
    auto test() {
        return 3.14f;
    }
      */

    return 0;
}

/* size_t
* It's a type which is used to represent the size of objects in bytes and
    is therefore used as the return type by the sizeof operator.
    It is guaranteed to be big enough to contain the size of the biggest object the host system can handle.
     if the compiler is 32 bit then it is simply a typedef(i.e., alias) for unsigned int but
     if the compiler is 64 bit then it would be a typedef for unsigned long long.

     size_t is never negative so it is often used as variable for cycles.
     size_t is used to rapresent objects sizes so when it appear in the code it is probably referred to an object
*/

//whyle using dynamic type RTTI(Run-Time Type Indetification) allow to obtain data about objects during program execution
// RTTI allow dynamic cast and typeid

/* void*
* 
* A void* pointer is a generic pointer that can point to objects of any data type.
* it does need to be casted to be rapresented with the correct data type
*/

/* <any> only working with c++ 17 or higher
* generalized type safe container for single values of any type
*/

/* typeid
* using RTTI can get informations about the type of an object or even from a class
* it is possible to fetch the id,the name ...  (see type_info)
*/

/* automatic type Deduction
* it deduces the type of the variable from the type of it's initializer expression at compile time
* if there is no initializer expression, a compilation error with accur
* it works with return type decleration in functions
* it is usefull if the type is complex of hard to predict for exampole when using typecasting 
* 
*/

