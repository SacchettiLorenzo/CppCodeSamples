#include <iostream>
#include <thread>

void functionToCall();


int main()
{
    //-----------------------------------------------------------------------------------------------------------------
    std::cout << "number of thread available " << std::thread::hardware_concurrency() << std::endl; // it can be wrong depending on the system
    // the main run in his own thread so it is possible to get the main thread id
    std::thread::id main_thread_id = std::this_thread::get_id();
    std::cout << main_thread_id << std::endl;

    std::thread t1(functionToCall); //calling the funtion in the t1 thread

    //check if t1 is joinable. thread are joinable if join or detach hasn't been called
    std::cout << "is t1 joinable? ";
    t1.joinable() ? std::cout << "yes" << std::endl : std::cout << "no" << std::endl;
    t1.join(); //wait for the t1 to return; the thread that call t1.join() is blocked in the meantime 
    //t1.detach(); t1 execute independently, the thread that called the t1 execution is not waiting. when t1 has finished all the resources are released
    std::cout << "is t1 joinable? ";
    t1.joinable() ? std::cout << "yes" << std::endl : std::cout << "no" << std::endl;

    functionToCall(); // calling the function in the main thread
    //-----------------------------------------------------------------------------------------------------------------
    
}

void functionToCall() {
    std::cout << "Called the function from thread " << std::this_thread::get_id() << std::endl;
}



