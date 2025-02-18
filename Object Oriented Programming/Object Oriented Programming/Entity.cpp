#include "Entity.h"
#include <iostream>

using namespace std;

int Entity::lastId = 0;

//Constructor
Entity::Entity() {
	Entity::x = 0;
	Entity::y = 0;
	data = new int[10];
	id = lastId;
	lastId++;
}

//Constructor ovedrloaded
Entity::Entity(string name)
{
	Entity::x = 0;
	Entity::y = 0;
	data = new int[10];
	id = lastId;
	lastId++;
	Entity::name = name;
}

//Destructor
Entity::~Entity() {
	delete[] data;
}


//Copy constructor
Entity::Entity(const Entity& other): data(new int[10]) {
	Entity::x = other.x;
	Entity::y = other.y;
	Entity::name = other.name;
	Entity::id = other.id;
	copy(other.data, other.data + 10, Entity::data);
	
}

//Copy assignment operator
Entity& Entity::operator=(const Entity& other)
{
	cout << "calling copy assignement operator" << endl;
	this->x = other.x;
	this->y = other.y;
	this->id = other.id;
	this->name = other.name;
	copy(other.data, other.data + 10, data);
	return *this;
}

//Move Constructor
Entity::Entity(Entity&& other): data(other.data) {
	cout << "calling move constructor" << endl;
	other.data = nullptr;
}

//Move assignment operator
Entity& Entity::operator=(Entity&& other) {
	cout << "calling move assignment operator" << endl;
	if (this != &other) {
		delete data;
		data = other.data;
		other.data = nullptr;
	}
}

void Entity::WhoAmI() {
	cout << "I'm an Entity" << endl;
}

void Entity::Move(int newx, int newy) {
	Entity::x = newx;
	Entity::y = newy;
}

void Entity::setId(int id) {
	Entity::id = id;
}

int Entity::getId() { return Entity::id; }

