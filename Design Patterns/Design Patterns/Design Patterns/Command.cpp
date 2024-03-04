#include <iostream>

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
	virtual void call() = 0;
	virtual void undo() = 0;
};

struct BankAccountCommand : Command {
	BankAccount& account;
	enum Action{deposit,withdraw} action;
	int amount;
	bool withdrawal_succeded;
	
	BankAccountCommand(BankAccount& account, const Action action, const int amount) : account(account), action(action), amount(amount), withdrawal_succeded{false} {}

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
		//performin opposite operation but only if withdraw succeded
		switch (action)
		{
		case BankAccountCommand::deposit:
			account.withdraw(amount);
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

int main() {
	BankAccount ba;
	BankAccountCommand cmd{ ba, BankAccountCommand::deposit, 100 };
	cmd.call();
	cmd.undo();
}
/*	a Command design pattern proposes that, instead of working with objects directly, we send them commands.
*	this is cool because in this way we are able to roll back to previous values or perform history based debugging
* 
*	in the example it is implemented a bank accound with deposit and withdraw operations
*/