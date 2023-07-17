#include <iostream>
#include <thread>

using namespace std;

void functionToCall2(int i, std::string const& s);
void functionToCall3(int& num);

#define scenario 4


int main() {
#if scenario == 0
    //PASSING ARGUMENT TO THREAD FUNCTION -----------------------------------------------------------------------------
    //char word[4] = "ciao"; 
    //std::thread t2(functionToCall2, 42, word); //could break
    thread t2(functionToCall2, 42, "CIAO");
    t2.join();
    //-----------------------------------------------------------------------------------------------------------------
#endif

#if scenario == 1
    //the main function could end before the buffer has been converted to string due to the implicit conversion that happen insiede the function
    char buffer[1024] = "ciao";
    thread t(functionToCall2, 3, buffer);
    t.detach();
#endif

#if scenario == 2
    //the buffer is converted before the function even start so it is safe to tell that the data insiede the thread has been copied correctly
    char buffer[1024] = "ciao";
    thread t(functionToCall2, 3, string(buffer));
    t.detach();
#endif

#if scenario == 3
    //this example do not compile because the variable num is passes as reference at the thread in the standard way
    int num = 0;
    thread t(functionToCall3, num);
    t.join();
    //functionToCall3(num);
    cout << num << endl;
#endif

#if scenario == 4
    //this example use std::ref to pas the reference. it work just fine
    int num = 0;
    thread t(functionToCall3, ref(num));
    t.join();
    //functionToCall3(num);
    cout << num << endl;
#endif
}

void functionToCall2(int i, std::string const& s) {
    cout << s << std::endl;
}

void functionToCall3(int & num) {
    num = num + 1;
}

/*
* passing argument to a thread function is essentialy passing the argument to a thread constructor
* when using thread all the argument of the function are copied so we have to keep in mind that passing references to a thread could not be a good idea
* a good idea is convert the actual reference in a non references type:
* char buffer[1024];
* thread t(function, buffer) could break
* thread t(function, std::string(buffer)) wont break;
* the reverse scenario can happen, the thread will update the inner copied data so it wont update the data pointed by the references passed by arguments
* reference to data != reference as copy of data
*/