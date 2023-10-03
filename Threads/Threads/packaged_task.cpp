#include <iostream>
#include <future>

using namespace std;

void printTwoNumbers(int a,int b);
int multiply(float a, int b);

int main() {
	
	//binding a function in a packaged task
	std::packaged_task<void()> task(std::bind(printTwoNumbers,5,10));
	std::future<void> result = task.get_future();
	task();

	std::packaged_task<int()> task2(std::bind(multiply,5,10));
	std::future<int> result2 = task2.get_future();
	task2();

	std::cout << "task_bind:\t" << result2.get() << '\n';

	//lambda in packaged task
	std::packaged_task<int(int, int)> task3([](int a, int b) {
		return multiply(a,b);
		});
	std::future<int> result3 = task3.get_future();

	task3(2, 9);

	std::cout << "task_lambda:\t" << result3.get() << '\n';

	//thread in packaged task
	std::packaged_task<int(int, int)> task4(multiply);
	std::future<int> result4 = task4.get_future();

	std::thread task_td(std::move(task4), 2, 10);
	task_td.join();

	std::cout << "task_thread:\t" << result4.get() << '\n';

	
}

void printTwoNumbers(int a, int b) {
	cout << a << " and " << b << endl;
}

int multiply(float a, int b) {
	return a * b;
}

/* packaged task
*  this class template is used to wrap any callable object so that in can be invoked asynchronously
*  it can be used as a building block for a thread pool
*  the parameters of the template are the function parameters type and the return type <return(param1,param2,paramx)> <int(int,int)>
*  the syntax of the parameters can depend on waht callable is used
*  the packaged task return a 'future' from the get_future() member function
*  std::packaged_task<void()> wrap a function with no return value, if the callable has a return value it is discarded
*/