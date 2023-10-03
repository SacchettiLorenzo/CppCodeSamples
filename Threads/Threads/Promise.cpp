#include <iostream>
#include <future>

using namespace std;

void printInt(future<int>& fut) {
	int a = fut.get(); // 
	cout << a << endl;
}

int main() {
	promise<int> prom;

	future<int> fut = prom.get_future();

	thread t1(printInt, ref(fut));

	prom.set_value(10);

	//the value is set at 10 so the promise return a future with the value
	//the future can provide the value so it execute the thread t1 that is not blocked anymore

	t1.join();
}



/* Promise
*	a promise execute the designed code when the value of the promise is set.
*	it return a std::future that store the data returned by the function executed by the promise
*	it offer a synconization point.
*	in the same way it is possible to manage an exception passing one with set_exception
* 
*/