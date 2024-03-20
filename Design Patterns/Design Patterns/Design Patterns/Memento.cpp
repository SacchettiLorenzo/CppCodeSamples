#include <iostream>
#include <vector>
using namespace std;

class BankAccount {
	int balance = 0;
public:
	explicit BankAccount(const int balance) : balance(balance) {};

	Memento deposit(int amount) {
		balance += amount;
		return{ balance };
	}

	void restore(const Memento& m) {
		balance = m.balance;
	}

};
class Memento {
	int balance;
public:
	Memento(int balance) : balance(balance) {};
	friend class BankAccount;
	friend class BankAccount2;
};

class BankAccount2 {
	int balance = 0;
	vector<shared_ptr<Memento>> changes;
	int current;
public:
	explicit BankAccount2(const int balance) : balance(balance) {
		changes.emplace_back(make_shared<Memento>(balance)); //create a pointer of a memento with a specific balance.
		current = 0;
	};

	int getBalance() {
		return balance;
	}

	shared_ptr<Memento> deposit(int amount) {
		balance += amount;
		auto m = make_shared<Memento>(balance);
		changes.push_back(m);
		++current;
		return m;
	}

	void restore(const shared_ptr<Memento>& m) {
		if (m) { //check if initiated
			balance = m->balance;
			changes.push_back(m);
			current = changes.size() - 1;
		}// else{return default value}
	}

	shared_ptr<Memento> undo() {
		if (current > 0) {
			--current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}
		return {};
	}

	shared_ptr<Memento> redo() {
		if (current + 1 < changes.size()) {
			++current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}
		return{};
	}
};

int main() {
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50); // m1 have balance 150
	auto m2 = ba.deposit(25); // m2 have balance 175

	ba.restore(m1); //balance 150

	ba.restore(m2);// balance 175

	BankAccount2 ba2{ 100 };
	ba2.deposit(50);
	ba2.deposit(25);

	ba2.undo();
	cout << ba2.getBalance() << endl;
	ba2.undo();
	cout << ba2.getBalance() << endl;
	ba2.redo();
	cout << ba2.getBalance() << endl;
	ba2.undo();
}


/*
* The memento pattern store the state of the system and return it as a dedicated, read-only object with no behaviour of its own.
* it is possible to roll back the system to a particular thate if needed
* 
* Using the Undo and Redo design it is possible to keep track of every operation performed and rollback at any of them
* 
* In the example a some operation are performed on a Bank account
*/