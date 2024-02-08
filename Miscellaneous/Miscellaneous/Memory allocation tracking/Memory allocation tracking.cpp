#include <iostream>
#include <memory>
using namespace std;

int globalMemoryUsage = 0;


void* operator new (size_t size)
{
    cout << "Allocating: " << size << " bytes" << endl;
    globalMemoryUsage += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    cout << "Freeing: " << size << " bytes" << endl;
    globalMemoryUsage -= size;
    free(memory);
}

struct Object {
    int x, y, z;

};

int main()
{
    {
        Object* obj = new Object;
    }

        cout << endl;

    {
        unique_ptr<Object> o = make_unique<Object>();
    }


}

/*
* every time the programm need to allocate memory on the heap it needs to use the new operator
* overloading the new operator to track how much memory has been allocated
*
* oveloading the delete operator to track how much memory has been freed(this work with data structures that use delete operator)
*/

