#include "Vector.h"
#include <vector>

void VectorAccessByIterator() {
    vector<int> g1;

    for (int i = 1; i <= 5; i++)
        g1.push_back(i);            // fill the vector from the back

    
    for (auto i = g1.begin(); i != g1.end(); ++i) // 'begin' e 'end' first and last elemet of the vector
         cout << &i << " ";          //return the address of the element of the vector

    cout << endl;

    for (auto i = g1.begin(); i != g1.end(); ++i)
        cout << *i << " ";          //return the value of the element of the vector

    cout << endl;

    cout << "\nOutput of cbegin and cend: ";
    for (auto i = g1.cbegin(); i != g1.cend(); ++i)     // return a constant iterator so the element can't be modified
        cout << *i << " ";

    cout << "\nOutput of rbegin and rend: ";
    for (auto ir = g1.rbegin(); ir != g1.rend(); ++ir)  // return a reverse iterator, 'rbegin' is the last element.  
        cout << *ir << " ";

    cout << "\nOutput of crbegin and crend : ";
    for (auto ir = g1.crbegin(); ir != g1.crend(); ++ir)    // constant reverse iterator
        cout << *ir << " ";
}

void VectorCapacity() {
    vector<int> g1;

    for (int i = 1; i <= 5; i++)
        g1.push_back(i);

    cout << "Size : " << g1.size(); //return the number of elements in a vector

    cout << endl;

    cout << "Capacity : " << g1.capacity(); //the size of storage space allocated to the vector as number of elements

    cout << endl;

    cout << "Max_Size : " << g1.max_size(); // the max number of elements that the vector can hold

    g1.resize(4);   // resize the vector so that contains 'n' elements

    if (g1.empty() == false) // return true if vector is empty
        cout << "\nVector is not empty";
    else
        cout << "\nVector is empty";

    g1.shrink_to_fit(); // remove the unused capacity. Reduce 'capacity()' to 'size()'

    g1.reserve(10);     //request that the vector capacity be at list enough to contain n elements 

}

void VectorAccess() {
    vector<int> g1;

    for (int i = 1; i <= 5; i++)
        g1.push_back(i);

        cout<<g1[1];      // accessing vector by index, no  bound are checked before trying to access, the element mustn't be empty

        cout << endl;

        cout<<g1.at(1);   // chek if the element exist, if not throw an out_of_range error  

        cout<<endl;

        cout<<g1.front(); //return the first element in the vector; the value not the pointer

        cout<<endl;

        cout<<g1.back();  //return the last element in the vector; the value not the pointer

        cout<<endl;

        cout<<g1.data();  //return a pointer to the first vector element used internally by the vector to store its owned elements.     

        cout<<endl;   


}

void VectorModifier() {
    vector<int> g1;
    vector<int> g2;

    for (int i = 1; i <= 5; i++)
        g1.push_back(i);

    for (int i = 10; i <= 18; i++)
        g2.push_back(i);

    g1.assign(5, 10);   // fill the array with 10 five times, It can also modify the size of the vector if necessary
    g1.push_back(1);    // push an element from the back of the vector
    g1.pop_back();    // remove last element
    g1.insert(g1.begin(),30);   //insert a new element before the element in the specified position (in this case before the first element)
    g1.erase(g1.begin());       //remove the element in the specified position (in this case the first element)
    g1.swap(g2);    //swap all the element of one vector with another vector of the same type, size of the vector can be different and will be swapped too
    g1.clear();     //remove all the element and resize the vector to 0;
    g1.emplace(g1.begin(), 5);  //like insert but it is possible to create an object inside the parameter
    g1.emplace_back(20);    //like push_back and emplace
    
    



}