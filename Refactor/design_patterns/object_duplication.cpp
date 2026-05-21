#include <iostream>
#include <string>

using namespace std;

struct Address {
	string street;
	string city;
	int suite;

	Address(const string& street, const string& city, const int suite) : street{street}, city{city},suite{suite}{}
};

struct Contact {
	string name;
	Address* address = nullptr;

	Contact(string name, Address* address) : name{ name }, address{ address } {}
	//using the copy constructor of Address to create a new object
	Contact(const  Contact& other) : name{other.name}, address{new Address{*other.address}}{} 

	//overloading = operator to act as copy constructor
	Contact& operator=(const Contact& other) {
		if (this == &other)return *this;
		name = other.name;
		address = new Address{ *other.address };
		return *this;
	}
};


int main() {
	
	Contact worker = { "", new Address{"123B East Dr","london",0} };;
	Contact john{ worker };
	john.name = "John";
	john.address->suite = 10;

	Contact jane = worker;
	john.name = "Jane";
	john.address->suite = 45;
	cout << worker.address->city << endl;
	cout << john.address->city << endl;
	cout << jane.address->city << endl;
	


}

/*	Object duplication is usefull when we have to create an object that is similar to another one
*   we must take care of the duplication, we have to copy the actual data and not the pointer
*	to make the code the most generic possible we have to define copy constructor of every struct or class that could be involved in the copy 
*	
*/