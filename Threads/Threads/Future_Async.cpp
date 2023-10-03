#include <iostream>
#include <future>

using namespace std;

int function1();
int function2();
int function3(int param);
int function4();

int main() {

	// standard use of future - async
	future<int> the_answer1 = std::async(function1);
	function2();
	cout << the_answer1.get();

	// future - async with launch deferred and parameters
	future<int> the_answer2 = std::async(launch::deferred,function3, 10);
	function2();
	cout << the_answer2.get(); //function 3 is launched after this call

	// future - async with launch async and parameters
	future<int> the_answer3 = std::async(launch::async, function3, 10);//function 3 is launched after this call
	function2();
	cout << the_answer3.get();

	// future - async with both launch option
	future<int> the_answer3 = std::async(launch::async | launch::deferred, function4);
	function2();
	cout << the_answer3.get();

	
}

/* Future
*	if a thread needs to wait for a specific event, it can use a 'future' to rapresenting this event.
*	a 'future' act as a place where you can store your return value of a async function (can be void).
*   2 types of 'future':
*   unique futures (std::future<>) work with unique pointer
*   shared futures (std::shared_futures<>) work with shared pointers
*	the future itself do not provide synchronized acces to object that should be protected with mutex or other mechanism
*	the most basic event could be the result of a calculation running in background
* 
* Async
*	async is used to start an asynchronous task for which the result is not needed right away.
*   std::async return a std::future object which eventually hold the return value.
*   when you need the value the get() function is called and on the std::future object and the thread blocks until the 'future' is ready to return the value.
*	additional argument can be passed in the same way that std:.thread does
*   all the rvalue are copied
*	it is possible to specify if async will runnof a different thread or syncronously in the current one using std::launch::---
*	std::launch::deferred : the function won't run until wait() or get() is called (it may never actualy run)
*	std::launch::async : the function will run on its own thread
*   std::launch::async | std::launch::async : the implementation may choose the best option depending on the load on system (this is the default one)
*/