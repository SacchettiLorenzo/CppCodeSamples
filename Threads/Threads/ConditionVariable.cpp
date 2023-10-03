#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>

using namespace std;

struct data_chunk {
	int a;
	int b;
};

mutex mut;
queue<data_chunk> data_queue;
condition_variable data_cond;

void data_preparation_thread() {

	for (size_t i = 0; i < 10; i++)
	{
		data_chunk const data = {i,i};
		lock_guard<mutex> lk(mut);
		data_queue.push(data);
		data_cond.notify_one();
	}
}

void data_processing_thread() {
	while (true)
	{
		if (data_queue.empty())break;
		unique_lock<mutex> lk(mut);
		data_cond.wait(lk, [] {return !data_queue.empty(); });
		data_chunk data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		cout << "A: " << data.a << ", B: " << data.b << endl;
	}
}

int main() {

	thread t1(data_preparation_thread);

	thread t2(data_processing_thread);

	
	t1.join();
	t2.join();

}

/* CONDITION VARIABLE
*  a condition variable is associated with some event or other condition, and one or more threads can wait for
*  that condition to be satisfied.
*  when some thread has determinated that the condition is satisfied it can notify other thread that are waiting for that condition.
*  condition variable are available with std::condition_variable or with std::condition_variable_any (more general)
* 
*  in data_preparation_thread a mutex lock the data inside the scope, at the end of the function a notification to waiting threads is sent
* 
*  in data_processing_thread a mutex lock the data inside the scope, the conditional variable is checked inside the wait function. if the condition is 
*  not satisfied the thread is paused and mutex unlocked.
* 
* data_processing_thread to perform operation on data must have:
*  - notification from data_preparation_thread
*  - conditional variable satisfied
*  - mutex unlocked to access data safaly
*/