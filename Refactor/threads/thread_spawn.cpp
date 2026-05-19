#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

using namespace std;

void do_work(unsigned int k) {

}

int main() {
	vector<thread> threads;
	for (size_t i = 0; i < 20; i++)
	{
		threads.push_back(thread(do_work, i));
	}

	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

}

//mem_fn return a function object (any object for which the function call operator is defined)
//whose call invoke the pointed member function (in this case thread::join)