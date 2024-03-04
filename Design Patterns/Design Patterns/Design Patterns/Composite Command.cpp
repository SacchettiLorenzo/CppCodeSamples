#include <iostream>
#include <vector>

using namespace std;

struct BankAccount {
	int balance = 0;
	int overdraft_limit = -500;

	void deposit(int amount) {
		balance += amount;
		cout << "deposited " << amount << ", balance is now:" << balance << endl;
	}

	bool withdraw(int amount) {
		if (balance - amount >= overdraft_limit) {
			balance -= amount;
			cout << "withdrew " << amount << ", balance is now:" << balance << endl;
			return true;
		}
		return false;
	}
};

struct Command {
	bool succeded;
	virtual void call() = 0;
	virtual void undo() = 0;
};

struct BankAccountCommand : Command {
	BankAccount& account;
	enum Action { deposit, withdraw } action;
	int amount;
	bool withdrawal_succeded;

	BankAccountCommand(BankAccount& account, const Action action, const int amount) : account(account), action(action), amount(amount), withdrawal_succeded{ false } {}

	void call() override {
		switch (action)
		{
		case BankAccountCommand::deposit:
			account.deposit(amount);
			break;
		case BankAccountCommand::withdraw:
			withdrawal_succeded = account.withdraw(amount);
			break;
		default:
			break;
		}
	}

	void undo() override {
		switch (action)
		{
		case BankAccountCommand::deposit:
			withdrawal_succeded = account.withdraw(amount);
			break;
		case BankAccountCommand::withdraw:
			if (withdrawal_succeded) {
				account.deposit(amount);
			}
			break;
		default:
			break;
		}
	}
};

struct ComositeBankAccountCommand : vector<BankAccountCommand>, Command {
	ComositeBankAccountCommand(const initializer_list<value_type>& items) : vector<BankAccountCommand>(items){}

	void call() override {
		bool ok = true;
		for (auto& cmd : *this) {
			if (ok) {
				cmd.call();
				ok = cmd.succeded;
			}
			else {
				cmd.succeded = false;
			}
		}
	}

	void undo() override {
		for (auto it = rbegin(); it != rend(); ++it)
		{
			it->undo();
		}
	}
};

struct MoneyTransferCommand : ComositeBankAccountCommand {
	MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount) : ComositeBankAccountCommand{
		BankAccountCommand(from,BankAccountCommand::withdraw,amount),
		BankAccountCommand(to,BankAccountCommand::deposit,amount)
	}{}
};

int main() {

}
/*	instead of creating and calling these multiple command it is possible to merge Composite design and 
*	command design to a composite command design
* 
*	in the example it is developed a simulation of a money transfer
*	each command will be called only if the previous one succeded
* 
*	a possible improvement could be adding a boolean "succeded" flag for the whole composite command
*/