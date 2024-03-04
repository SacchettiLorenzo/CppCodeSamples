#include <iostream>

using namespace std;

class Creature {
	int strength, agility;
public:
	Creature(int strength, int agility) : strength{strength}, agility{agility}{}

	int process_query(const CreatureQuery& q) const;
	void process_command(const CreatureCommand& cc);

	/*if we want is possible to implement getter and setter anyway*/
	void set_strength(int value);
	int get_strength();
};

enum class CreatureAbility{strength, agility};

struct CreatureCommand {
	enum Action {set, increaseBy, decreaseBy} action;
	CreatureAbility ability;
	int amount;
};

struct CreatureQuery {
	CreatureAbility ability;
};

void Creature::process_command(const CreatureCommand& cc) {
	int* ability;
	switch (cc.ability) {
	case CreatureAbility::strength:
		ability = &strength;
		break;

	case CreatureAbility::agility:
		ability = &agility;
		break;
	}

	switch (cc.action) {
	case CreatureCommand::set:
		*ability = cc.amount;
		break;
	case CreatureCommand::increaseBy:
		*ability += cc.amount;
		break;
	case CreatureCommand::decreaseBy:
		*ability -= cc.amount;
		break;
	}
}

int Creature::process_query(const CreatureQuery& q) const {
	switch (q.ability) {
	case CreatureAbility::strength: return strength;
	case CreatureAbility::agility: return agility;
	}
	return 0;
}

void Creature::set_strength(int value) {
	process_command(CreatureCommand{
		CreatureCommand::set, CreatureAbility::strength, value
		});
}

int Creature::get_strength() {
	return process_query(CreatureQuery{ CreatureAbility::strength });
}

int main() {
	Creature monster(10,20);
	monster.process_command(CreatureCommand{ CreatureCommand::increaseBy, CreatureAbility::agility, 30 });
	monster.get_strength();

}

/*	the idea of this design pattern is to divide the operations in 2 major groups:
*	Commands: action to perform that might change values of some variable
*	Query: data request
* 
*	A class will expose only two call, one for command and one for queries
*/