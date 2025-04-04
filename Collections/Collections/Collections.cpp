

#include <iostream>
//#include "Array.h"
//#include "Vector.h"
//#include "List.h"
//#include "Map.h"
//#include "Enum.h"
#include "Queue.h"

using namespace std;

int main()
{
    //ARRAY
    /*
    MonodimensionalArray();
    BidimensionalArray();
    MultidimensionalArray();
    DynamicAllocation();
    ArraySize();
    */

    // VECTOR
    /*
    VectorAccess();
    VectorAccessByIterator();
    VectorAccess();
    VectorModifier();
    */

    // LIST

    /*
    ListAccess();
    ListModifier();
    */

    //ENUM
    //PrintEnum();

    //Map();
   //Unordered_Map();

    //QueueOperations();
    
    

}


/*  NOTE------------------------------------------------------
*   -ARRAY
        -Array are not dynamic so they allow only a fixed number of element which is decided at the time of decleration.
         There is not any control of the bound of the array so if we try to access more elements then the size of the array we get errors at runtime.
        - Dynamic allocation do not define array during runtime but allocate memory for a number of element.
         In c++ the 'new' operator return the address of the first element of the newly allocated memory for the array, so we can use the address as
         starting point of the array. Using dynamic allocation it is possible to define arrays with a variable value as size.
    -VECTOR
        - Vector are the same as dynamic array with the ability to resize itself automatically. Element are inserted in contiguous storage.
        The access to a vector is granted by an iterator.
        If we use vector we must remember that it resize automatically so a function will be called to do that.
        various operations takes tifferent time depending on complexity
        Random acces - constant O(1)
        Insertion and removal at the end - constant O(1) because there is no cycle through
        Insertion and removal - lineat in the distance to the end of the vector O(n)
        Knowing the size - O(1)
        Resizing the vector - O(n)
    -LIST
        Liste are sequential containsers that allow non-contiguous memory allocation. List are slower in traversal but fast as vector or array for insertion
        and deletion.
        List need a proper defined iterator to work with.
        Some statement are similar to vectors.
    -QUEUE
        Que are a type of container that works with (FIFO) first in first out. The element are inserted at the back and deleted from the front of the dataset
    -DEQUE
        Double-ended que are que capable of expansion and contraction on both end. Like Vector it's possible to push and pop element at the back fo the dataset
        with the addition of push and pop and the front of the datasete
    -PAIR
        It is used to combine toghether two values, even if the data type is different. It can be used to store key-value elements.
        it is not mandatory to declare the data type.
    -STACK
        Stack is a container adaptors with (LIFO) Last In First Out type of working. It's is possible to remove element only from one side of the container.
        Even the reading process is performed from the last element so the stack result in inverted order but it isn't.
    -SET
        Sets are a type of associative containers in which each element has to be unique because the value of the element identifies it. The values are stored in a specific order.
    -MAP
        A map associate a key with a value or a series of values, it can be ordered or unordered;
        In maps data are quicker to fetch because are organized in a way that make the searching process easier, you don't have to search through the all dataset to have a specific element(like vector)
        Map are self balancing binary search tree so the algorithm complexity is O(log n). Using a < (less then) operator is possible to search and store new value in correct place
        Unordered Map use hashtable to understand the position of the element (it can be faster).
        In map the use of [] operator (cityMap["Torino"]) create the element if not exist, the key element will have the assigned name but
        all the other non-provided date will be at default value; to avoid this instead of use [] use .at() .
        Mind that Vector are for the general use faster then maps but for larger set of data maps are better; for example for indexing big structure
        for general porpuse is better the unordered map because is faster unless we need an ordered structure
    -ENUM
        Enum consist of a group of variable of the same type.
        By default, if there aren't other value specified the value of the enum variable is in increasing order starting by the firt one at 0;(Example1)
        Otherwise the value can be specified;(Example2)
        In a grup where some variable has his own value and others not, the value immidiately next to the one which has the value increased by 1, like in a sequnce
        by default the enum is an integer so we can assign value that take equal or les memory like unsigned char or char (these types can be rapresented via integer)




*/