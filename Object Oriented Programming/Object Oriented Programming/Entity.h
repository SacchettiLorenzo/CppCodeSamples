#pragma once
#include <string>
using namespace std;

class Entity
{
public:
	int x, y;
	string name;
	static int lastId;


	//function overloading
	Entity();
	Entity(string name);

	//destructor
	~Entity();

	//copy constructor
	Entity(const Entity& obj);

	
	//disable copy
	//Entity(const Entity& obj) = delete;

	//copy assignement operator
	Entity& operator= (const Entity& other);

	//Move Constructor
	Entity(Entity&& other);

	Entity& operator=(Entity&& other);

	virtual void WhoAmI(); //function declered virtual to allow override

	void Move(int newx, int newy);

	void setId(int id);

	int getId();

	friend void friendFunction(Entity& obj);
	
	
private:
	int id;
	int private_variable;
	int* data;
	
};

//constructor: initialise the class with some specific values
//destructor: delete or free the memory occupied by the class; it must contain code to free dynamically allocated memery to avoid memory leaks
//copy constructor: member function that initialize an object using another object of the same class (creating a copy)
//copy assignement operator: overload "=" operator (create a copy)

//move constructor: member function that set the current instance to point to another instance. the other member of the instance are set to null pointer 
//move assignement operator: overload "=" operator that set the current instance to point to the other one



