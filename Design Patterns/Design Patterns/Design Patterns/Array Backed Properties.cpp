#include <iostream>
#include <string>
#include <array>

using namespace std;

class Creature {
	enum Abilities { str, agl, ints, count };
	array<int, count> abilities;
public:
	int get_strength() const {
		return abilities[str];
	}

	int set_strength(int value) {
		abilities[str] = value;
	}

	int sum() const {
		int sum = 0;
		for (int x : abilities)sum += x;
		return sum;
	}

	double avarage() const {
		return sum() / (double)count;
	}
};

int main() {

}

/* Array backed properties
*	this pattern allow a simpler maintainance of a class providing a way to add property without having to refactor 
*	every part of the class
*	the properties name are stored in an enum and the actual values in a type compatible data structure
* 
*	all the functions are generated in such a way that no refactoring is needed
* 
*	The only thing to pay attention to is that is not convenient to change the order of the properties because functions like 
*	getters and setters works on a data that have a specific place in memory identified by a specific index
*/