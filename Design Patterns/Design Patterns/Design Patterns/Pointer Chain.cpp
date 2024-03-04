#include <iostream>

using namespace std;

struct Creature {
	string name;
	int attack;
	int defense;

	// add constructor and << here
	friend ostream& operator << (ostream& os, const Creature & creature) {
		return os << creature.name << "has Attack: " << creature.attack
			<< " and Defense: " << creature.defense;
	}
};

class CreatureModifier {
	//next modifier chained to this one
	CreatureModifier* next{ nullptr };
protected:
	//the class store a reference to the object it plans to modify
	Creature& creature;
public:
	explicit CreatureModifier(Creature& creature) : creature{creature}{}

	//chan the next modifier
	void add(CreatureModifier* cm) {
		if (next) {
			next->add(cm);
		}
		else {
			next = cm;
		}
	}

	//handle the next item in the chain
	virtual void handle() {
		if (next) {
			next->handle();
		}
	}
};

class DoubleAttackModifier : public CreatureModifier {
public:
	explicit DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {
	
	}
	void handle() override {
		creature.attack *= 2; //real modification
		CreatureModifier::handle(); //call the handle of the base class to compute the next modifier in the chain
	}
};

class IncreaseDefenseModifier : public CreatureModifier {
public:
	explicit IncreaseDefenseModifier(Creature& creature) : CreatureModifier(creature) {

	}
	void handle() override {
		if (creature.attack <= 2) {
			creature.defense += 1; //real modification
		}
		CreatureModifier::handle(); //call the handle of the base class to compute the next modifier in the chain
	}
};


int main() {
	Creature goblin{ "Goblin" ,1 ,1 };
	CreatureModifier root{ goblin };
	DoubleAttackModifier r1{ goblin };
	DoubleAttackModifier r1_2{ goblin };
	IncreaseDefenseModifier r2{ goblin };

	root.add(&r1);
	root.add(&r1_2);
	root.add(&r2);

	root.handle();

	cout << goblin << endl;
}
/*	The Pointer Chain Design Pattern implement the concept of chain of responsability
*	it is possible to stack a list of operation to be executed
* 
*	in the example it is dveloped a system for applying modifiers to a creature in a videogame 
*/