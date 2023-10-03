#include <iostream>
#include <string>

using namespace std;

struct Database {
private:
	string DBname;
protected:
	Database() {
		DBname = "Super Database";
		//doing various things
	}
public:
	static Database& get() {
		static Database database;
		return database;
	}

	// heap allocation of the pointer, in this way only the pointer is static
	/*static Database& get() {
		static Database* database = new Database();
		return *database;
	}*/

	void printName() {
		cout << DBname << endl;
	}

	Database(Database const&) = delete;
	Database(Database&&) = delete;
	Database& operator= (Database const&) = delete;
	Database& operator= (Database&&) = delete;
};

int main() {
	Database::get().printName();

	
}

/* Singleton
*	Sometimes in the program there is the necessity to instanciate only one time a class (for example for a connection to a database)
*	To prevent the call of a con tructor more than one time the class shold be designed as a singleton
*	In the class there in only the static member that rapresent the instance of the class and the only methon is a get() method that return a 
*   reference to that static instance
*	All the various contructor are deleted to prevent any stealthy call
*	The only way to access database instance is to call the static class method get() that return the 
	instance and then access the others members through the returned static instance 
	
*	Subclasses of singleton are strictly dependand from it so if we need to change the data source for testing porpuses
*	we have to work around it building a subclass that override the function that provide the real data.
*	
* 
*	in the example a possible connection to a database is treated as a singleton
*	'Database::get()' return the static instance. 'Database::get().otherFunction()' to access to the primate functions of the class (instance)
*/