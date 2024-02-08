#include <iostream>

using namespace std;

class Entity {
private:
    int x, y;

    int* pointer;

    mutable int value;
public:
    int getX() const {
        value = 10;
        //x = 10; cant do
        return x;
    }

    const int* const getPointer() const {
        return pointer;
    }

};

void printEntity(const Entity& e) {
    //passing a reference to avoid copying of the object
    //the reference is const so the method used must be const
    cout << e.getX() << endl;
}

int main()
{
    int value = 10;
    const int max_age = 99;

    const int* a = new int;
    int const* b = new int;
    int* const c = new int;
    //a* = 10; //can't do
    a = &max_age;

    //c = &value; can't do (watch syntax)

}

/*
* The constant keyword can be attached to any functions and variable and prevents it to be modified
*
* in const pointer it is not possible to modify the content of the pointer but it is possible to change the variable pointed at;
* depending on the syntax there are different behaviour:
* - const int* a = int const* a; normal constant pointer
* - int* const; cannot reassign the pointed variable but can change the content
*
* const behaviour is different if the keyword is before the asterisk or after the asterisk
*
* in classes a method can me defined const if the method should never modify other class members
*
* the const keyword used 3 times in method declareation means:
* - the method will return a pointer that cannot be modified
* - the content of the pointer cannot be modified
* - the method promise not to modify any class member
*
* if the class can be istantiated as const the method used should be const or at least have a const version
*
* the keyword mutable allow the const method to modify a class member variable. it should be used for debugging purposes or if most of the
* member should me const and only few need to update
*/