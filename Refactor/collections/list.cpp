#include "List.h"
#include <list>

void ListAccess() {

    list<int> gqlist1;

    for (int i = 0; i < 10; ++i) {
        gqlist1.push_back(i * 2);
    }

    list<int>::iterator it;

    for (it = gqlist1.begin(); it != gqlist1.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

void ListModifier() {
    list<int> mylist{ 1, 2, 2, 2, 5, 6, 7 };
    list<int> mylist2{ 8, 9, 10 };
    mylist.remove(2);           // remove all the matching elements

    for (auto it = mylist.begin(); it != mylist.end(); ++it)
        cout << ' ' << *it;

    mylist.reverse();   // reverse all the elements of the list
    mylist.sort();      // sort the list in increasing order
    mylist.unique();    // remove duplicates;
    mylist.splice(mylist.begin(), mylist2);     // transfer elements to one list to another

    for (auto it = mylist.begin(); it != mylist.end(); ++it)
        cout << ' ' << *it;

    mylist.merge(mylist2);  // merge two sorted list into one.


    for (auto it = mylist.begin(); it != mylist.end(); ++it)
        cout << ' ' << *it;

}

