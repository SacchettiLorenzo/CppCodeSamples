#include "Entity.h"
#include <iostream>

using namespace std;

int Entity::lastId = 0;

Entity::Entity() {
	Entity::x = 0;
	Entity::y = 0;
	data = new int[10];
	id = lastId;
	lastId++;
}

Entity::Entity(string name)
{
	Entity::x = 0;
	Entity::y = 0;
	data = new int[10];
	id = lastId;
	lastId++;
	Entity::name = name;
}

Entity::~Entity() {
	delete[] data;
}

Entity::Entity(const Entity& other): data(new int[10]) {
	Entity::x = other.x;
	Entity::y = other.y;
	Entity::name = other.name;
	Entity::id = other.id;
	copy(other.data, other.data + 10, Entity::data);
	
}


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



