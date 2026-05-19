#include <iostream>
#include <thread>

using namespace std;

void functionToCall();

class thread_guard {
    thread& t;
public:
    explicit thread_guard(thread & t_):t(t_) {

    }

    ~thread_guard() {
        if (t.joinable())t.join();
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete; //deleted operator "=" cannot assing thread_guerd instance to another thread_guard instance
};

struct func {
    int& i;
    func(int& i_) :i(i_) {}
    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            //dosomethin();
        }
    }
};

int main() {
    int some_local_state = 0;
    func my_func(some_local_state);
    thread t(my_func);
    thread_guard g(t);
    
} 

void functionToCall() {
    std::cout << "Called the function from thread " << std::this_thread::get_id() << std::endl;
}

/*
* it is usefull to use a class to manage threads in order to join the thread when the instance of the thread management class is destroied
* // the constructor is explicit so it cannot be used for implicit conversion and copy-initialization
* // copy constructor and copy assignement operator ar deleted
*/