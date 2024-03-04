#include <iostream>
#include <map>

using namespace std;

typedef uint32_t key;



struct User {

	User(const string first_name, const string& last_name) : first_name{add(first_name)}, last_name{add(last_name)}{}
	
protected:
	key first_name, last_name;
	static map<key, string> names;
	static key seed;
	static key add(const string& s) {
		//could be improved with boost bimap
		//implementation of a simple get-or-add mechanic
		std::pair<key, string> res;
		for (auto& it : names) {
			if (it.second == s) {
				res = it;
			}
		}
		auto resIt = names.find(res.first);
		if (resIt == names.end()) {
			//no result in the map --> adding
			names.insert({ ++seed,s });
			return seed;
		}
		return res.first; //return the already inserted key value
	}

	const string& get_first_name() const {
		return names.find(first_name)->second;
	}

	const string& get_last_name() const {
		return names.find(last_name)->second;
	}

	friend ostream& operator << (ostream& os, const User& obj) {
		return os
			<< "first name: " << obj.get_first_name()
			<< " last name: " << obj.get_last_name();
	}
};

//initializing static members
key User::seed = 0;
map<key, string> User::names;
int main() {
	User user("Lorenzo", "Sacchetti");
	cout << user << endl;
}

/*	flyweight is a design patter that let you use again the data that are already present in the collection
*	this design depend on the get-or-add logic to re-use data 
*/