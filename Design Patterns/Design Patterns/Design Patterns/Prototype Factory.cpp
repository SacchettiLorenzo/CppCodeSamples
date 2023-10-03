#include <iostream>
#include <string>

using namespace std;

struct Address {
	string street;
	string city;
	int suite;

};

struct Contact {
	string name;
	Address* address = nullptr;
};


Contact second{ "", new Address{"123B East Dr","london",0} }; //contact of the employee in the second office
Contact first{ "", new Address{"123 East Dr","london",0} }; //contact of emplyee in the first office

struct EmployeeFactory {
	

	static unique_ptr<Contact> NewMainOfficeEmplyee(string name, int suite) {
		return NewEmployee(name, suite, first);
	}

	static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite) {
		return NewEmployee(name, suite, second);
	}

private: 
	static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto) {
		auto result = make_unique<Contact>(proto);
		result->name = name;
		result->address->suite = suite;
		return result;
	}

};

int main() {
	
		auto john = EmployeeFactory::NewMainOfficeEmplyee("John Doe", 123);
		auto jane = EmployeeFactory::NewAuxOfficeEmployee("jane Doe", 125);

		unique_ptr<Contact> ciao = EmployeeFactory::NewMainOfficeEmplyee("John Doe", 123);
	

}

/*	Prototype factory template
*	Prototype factory template is used when most of an object should have predefined data.
*	The object is partially constructed at the beginning then copied for the actual requested instance and 
*	modified just as mush as needed
*/