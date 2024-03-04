#include <iostream>


using namespace std;

//mediator
struct Game {
	signal<void(Query&)> queries;
};

struct Query {
	string creature_name;
	enum Argument{attack, defense} argument;
	int result;
};

class Creature {
	Game& game;
	int attack;
	int defense;
public:
	string name;

	Creature(Game& game, string name, int attack, int defense) : game{ game }, name{name}, attack { attack }, defense{ defense } {}

	friend ostream& operator <<(ostream& os, Creature& creature) {
		return os << "Name: " << creature.name << " Attack: " << creature.attack << " Defense: " << creature.defense;
	}
};

class CreatureModifier {
	Game& game;
	Creature& creature;
public:
	CreatureModifier(Game& game, Creature& creature): game(game), creature(creature){}
};

class DoubleAttackModifier : public CreatureModifier {
	connection conn;
public:
	DoubleAttackModifier(Game& game, Creature& creature) : CreatureModifier(game, creature) {
		conn = game.quesries.connect([&](Query& q)) {
			if (q.creature_name == creature.name && q.argument == Query::Argumet::attacl) {
				q.result *= 2;
			}
		}
	}

	~DoubleAttackModifier() { conn.disconnect(); }
};

int main() {
	Game game;
	Creature goblin{ game, "Strong Goblin",2,2 };
	cout << goblin << endl;
	{
		DoubleAttackModifier dam{ game, goblin };
		cout << goblin << endl;
	}
	cout << goblin << endl;
}

/*	The Broker Chain Design pattern is developed around the idea og adding an event broker to the programm.
*	Since it is connected to every partecipating component it is used as a mediator since it responds to queries
*	through events
* 
*	this example should use a boost library that inplement an event system
*/