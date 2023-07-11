#include <iostream>
#include <memory> //smart pointers

using namespace std;

class Entity {
public:
	Entity() {
		cout << "Created Entity" << endl;
	}
	~Entity() {
		cout << "Destroyed Entity" << endl;
	}

	void print() {

	}
};
	


int main() {
	//unique_ptr-----------------------------------
	//scope for unique pointer
	{
		//unique_ptr<Entity> entity(new Entity());
		unique_ptr<Entity> entity = make_unique<Entity>();// better exeption handling
		//unique_ptr<Entity> e2 = entity; can not copy

		//the unique pointer is destroyed at the end if the scope
		entity->print();
	}

	//shared pointer-----------------------------------
	{
		shared_ptr<Entity> e0;
		{
		shared_ptr<Entity> shared = make_shared<Entity>();
		e0 = shared;
		//in this scope the reference to e0 is alive
		}
		//in this scope the reference to e0 is alive

	}
	//the pointer lost the referece so it gets destroied

	//weak pointer------------------------------
	{
		weak_ptr<Entity> e2;
		{
			shared_ptr<Entity> shared = make_shared<Entity>();
			e2 = shared;
			//in this scope the reference to e0 is alive
			
		}
		
		//in this scope the pointer is destroyed because it is out of his scope and the reference count is 0 (is always 0 with)

	}



}

//smart pointers
/*
* smart pointers automaticly free the memory when an object is not needed anymore
* unique_ptr
* shared_ptr
* weak_ptr
* 
* unique_ptr (scope pointers)
* free the memory when the pointer is out of scope 
* it's called unique pointer because it cannot be copied 
* 
* shared_ptr
* work with reference counting. it keep the count of how there many references are to the pointe
* when the ammount of references reaches 0, the pointer gets deleted 
* 
* weak_ptr
* work the same as a shared pointer but it doesn't encrease teh count of the references
* 
* smart pointer provide functions to get information about pointers
*/