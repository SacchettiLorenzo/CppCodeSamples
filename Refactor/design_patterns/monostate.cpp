#include <iostream>
#include <string>

using namespace std;

class Printer {
	static int id;
public:
	int get_id() const {
		return id;
	}

	void set_id(int value) {
		id = value;
	}
};

int main() {
	Printer P;
}

/* Monostate is a variation on the Singleton pattern
*	The class work only with static data, 
*	the biggest advantage is that you can modify an existing class to work with static data. doing so 
*	you achieve the nonplurality of object instances
*	the disadvantages is that static members always takes up space even if not needed.
*/