#include "Queue.h"



void showQueue(queue<int> q) {
	//show all the element while removing it from the front
	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
	}
}

void QueueOperations() {
	queue<int> q;
	q.push(101);
	q.push(202);
	q.push(303);

	showQueue(q);

	cout << " gquiz.size() : " << q.size() << endl;
	cout << " gquiz.front() : " << q.front() << endl;
	cout << " gquiz.back() : " << q.back() << endl;
}