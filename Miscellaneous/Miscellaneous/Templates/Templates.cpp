#include <iostream>

using namespace std;

template<typename T>
void print(T value) {
    cout << value << endl;
}

template<typename T, int N>
class Array {
private:
    T m_array[N]; //array of type T (generic) with N size
public: int getSize() const { return N; }
};

int main()
{
    print(5);
    print("ciao");
    print(3.14f);
    print<int>(10);//calling the template with a specific typename

    Array<int, 5> array;
    Array<std::string, 5> array2;
    cout << array.getSize() << endl;
    cout << array2.getSize() << endl;
}

//templates allow to create generic functions or classes
// the actual code for the specific type is generated at compile time. The compiler understand that the generic function is called with a specific type, so it create the specific function
// it avoid the massive function overloading for each type that could be managed by a specific function
// it is possible to specify a specific while calling the function
// if the template does not get called even once the template does not evet exist after compile time

//template work at compile time so it is possible to dynamically generate array(or simil structures) on the stack and not on the heap 

//in the angled brackets <> is possible to insert any type:
// - typename for generic
// - int for integer
// - clas for classes
// - ...
