#include <iostream>

using namespace std;

//base class
struct Pingable {
	virtual string ping(const string& massage) = 0;
};

// no message storage, response is immediate
struct Pong : Pingable {
	string ping(const string& message) override {
		return message + " pong";
	}
};

void tryit(Pingable& pp) {
	cout << pp.ping("ping") << endl;
}

int main() {
	Pong pp;
	for (size_t i = 0; i < 3; i++)
	{
		tryit(pp);
	}
}
/*	Communications Proxy build an design similar a request-response design
*	it is usefull to expand some functionality without using any kind of storage but working only on the provided data
* 
*	in the example we try to simulate a ping-pong
*/