#include <iostream>

using namespace std;

template<typename T> struct Property {
	T value;
	Property(const T initial_value) {
		*this = initial_value;
	}

	//getter
	operator T() {
		return value;
	}

	//setter
	T operator =(T new_value) {
		return value = new_value;
	}
};

struct Creature {
	Property<int> strength{ 10 };
	Property<int>agility{ 5 };
};

int main() {
	Creature creature;
	creature.agility = 20;
	auto x = creature.strength;
}

/*	Property Proxy design pattern is used to make more general the concept on object property in c++
*	if a class provide some property it is possible to create a template for the managment of get and set of those properties
*/