
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //standard vector from STL

    vector<int> values = { 1,2,3,4,5 };

    //standard for loop
    for (int i = 0; i < values.size(); i++) {
        cout << values[i] << endl;
    }

    //range based for loop
    for (int value : values) {
        cout << value << endl;
    }

    //using iterator
    for (vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        cout << *it << endl;
    }

    //USE OF INPUT ITERATOR TO ACCESS ELEMENTS
    for (vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        cout << *it << endl;
    }

    //USE OF OUTPUT ITERATOR TO ASSIGN ELEMENTS
    for (vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        *it = 1;
    }

    //USE OF FOREWARD ITERATOR TO ACCESS AND ASSIGN ELEMENTS
    for (vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        cout << *it << endl;
        *it = 1;
    }

    //USE OF BIDIRECTIONAL ITERATOR TO ACCESS AND ASSING ELEMENTS IN REVERSE
    for (vector<int>::iterator it = values.end(); it != values.begin(); --it) {
        if (it != values.end()) {
            cout << *it << endl;
            *it = 1;
        }
    }
    //USE BIDIRECTIONAL OPERATOR TO COPARE ELEMENTS
    vector<int>::iterator i1;

    vector<int>::iterator i2;

    i1 = values.begin();

    i2 = values.end();

    if (i1 < i2) {
        cout << "Yes" << endl;
    }

    int count = i2 - i1;

    cout << "count = " << count;



}

/* ITERATOR
* An iterator is an object that point to an element inside a container.
* It is used to move through the contents of the container.
* The most simple iterator is a ponter that point element inside an array and can iterate through them using the incrememnt operator (++).
* Depending upon the functionality and the data structure used there are 5 categories.
* From the most powerfull:
* - Random-Access
* - Bidirectional
* - Foreward
* - Input / Output
*
*  Foreward, Bidirectional, Random Iterator are also valid Oputput iterators
*
* Different containers of the STL support different iterator level:
* Vector : Random - Access
* List : Bidirectional
* Deque : Random - Access
* Map : Bidirectional
* Multimap : Bidirectional
* Set : Bidirectional
* Multiset : Bidirectional
* Stack : No iterator Supported
* Queue : No iterator Supported
* Priority - Queue : No iterator Supported
*

*/

/* INPUT ITERATOR
*  it can be used only with single pass algorithms in which we can got to all the locations in the range at most once
*  An input iterator can be compared for equality with another iterator, two iterators will be equal only when they point to the same position
*  an input iterator can be dereferenced (* or ->) to obtain the value stored at the position being pointed by the iterator
*  it can be incremented so that it refer to the next element in the sequence using ++ operator but not -- operator
*  input iterator are used only for accessing elements and not for performing copy or assignement
*  Permitted operations: std::find
*/

/* OUTPUT ITERATOR
*  it can be used only with with single pass algorithms in which we can got to all the locations in the range at most once
*  output iterators cannot be compared for equality with another iterator.
*  an output iterator can be dereferenced (* or ->) to obtain the value stored at the position beaing pointed by the iterator
*  it can be incremented so that it refer to the next element in the sequence using ++ operator but not -- operator
*  output iterators are used only when we want to assign elements and not when we have to access elements.
*  Permitted operations: std::move
*/

/* FOREWARD ITERATOR
*  it can be used in multi pass algorithm
*  can be compared for equality with another iterator, two iterators will be equal only when they point to the same position
*  the foreward iterator can be dereferenced as an rvalue as well as an lvalue so it can be used for both accessing and assigning operation
*  it can be incremented so that it refer to the next element in the sequence using ++ operator but not -- operator
*  The value pointed to by these iterators can be exchanged or swapped.
*  Foreward = Input + Output
*  Permitted operations: std::replace
*/

/* BIDIRECTIONAL ITERATORS
*  it can be used in multi pass algorithm
*  can be compared for equality with another iterator, two iterators will be equal only when they point to the same position
*  can be dereferenced as an rvalue as well as an lvalue so it can be used for both accessing and assigning operation
*  it can be incremented so that it refer to the next element in the sequence using ++ operator
*  it can be decremented so that it refer to the previous element in the sequence using -- operator
*  it cannot be used with relational operator (== , <=)
*  Permitted operations: std::reverse_copy
*/

/* RANDOM ACCESS ITERATOR
*  it can be used in multi pass algorithm
*  can be compared for equality with another iterator, two iterators will be equal only when they point to the same position
*  can be dereferenced as an rvalue as well as an lvalue so it can be used for both accessing and assigning operation
*  it can be incremented so that it refer to the next element in the sequence using ++ operator
*  it can be decremented so that it refer to the previous element in the sequence using -- operator
*  support relational and arithmetical operator so it can move in both direction and that too randomly
*  support offeset dereference operator []
*  The value pointed to by these iterators can be exchanged or swapped.
*  Permitted operations: std::random_shuffle
*/
