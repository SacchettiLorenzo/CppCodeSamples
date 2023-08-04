#include <iostream>
#include <list>
#include <mutex>

using namespace std;

class thread_guard {
    thread& t;
public:
    explicit thread_guard(thread& t_) :t(t_) {

    }

    ~thread_guard() {
        if (t.joinable())t.join();
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete; 
};

void add_to_list(int newvalue);
bool list_contains(int value_to_find);

mutex some_mutex;
list<int> some_list;

int main() {
    thread k(list_contains, 10);
    thread_guard l(k);

    thread t(add_to_list,10);
    thread_guard g(t);

    thread s(add_to_list, 20);
    thread_guard f(s);

    

}

void add_to_list(int new_value) {
    lock_guard<mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    lock_guard<mutex> guard(some_mutex);
    int found = find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
    cout << found;
    return found;
}

// mutex provide protection to shared data 
// in this way multiple thread can work on a single dataset
// thread works in parallel so it is not possible to determine which thread act first, mutex only provide protection when there is the possibility
// of multiple access simultaneously

//lock guard provide the template that lock on construction and unlock on destruction
//it coult be done in an axplicit way using lock() and unlock() the same as the thread_guard

// all the data that should be protected by mutex should be grouped in class or struct. global variables are never a good idea

// when using user defined containers the mutex must protect all the data structure and not the single element (like single node in a node structure)
// the mutex should be implemented inside the data structure, in this way each thread can access only one member function at any given time