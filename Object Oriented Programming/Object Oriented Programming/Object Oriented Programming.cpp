#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Opponent.h"
#include <memory>

using namespace std;

int main()
{
    
        Entity e;
        e.x = 10;
        e.y = 15;

        
        //copy constructor
        Entity f(e);
      
        
        Entity k;
        //copy assignement operator
        k = e;

       //f,k,e have same value 

        Entity genericEntity;
        Player genericPlayer;
        Enemy genericEnemy;
        Opponent genericOpponent;

        genericEntity.WhoAmI();
        genericPlayer.WhoAmI();
        genericEnemy.WhoAmI();
        genericOpponent.WhoAmI();

        friendFunction(genericEntity);


      
        __debugbreak();



}

void friendFunction(Entity& obj) {
    cout << "printed private variable from outside the class using friend function: " << obj.id << endl;
}


//rule of zero five three
/*
* ZERO
* if a class does not manage resorces shod not have special member functions like:
* - destructor
* - copy constructor
* - copy assignement operator
* - move constructor
* - move assignement operator
* the compiler will generate those functions accordingly to what the class handles in term of mwmory
*
* THREE
* a class that manage resorces should define the following functions:
* - Destructor
* - Copy cnonstructor
* - Copy assignement operator
* 
* FIVE
* like rule of three with additional special member function:
* - Move constructor
* - Move assignement operator
*/

/* TODO: add move constructor and move assignement operator
*  
*/

/* DIAMONDO INHERITANCE
* class A in the Base class
* classes B and C are Subclasses of A
* class D is Subclass of B and C
* B and C must be declered as virtual to avoid abiguous parent decision
*/

/* VIRTUAL FUNCTIONS
* Allow subclass to override the functions of the base class
* in a diamond inheritance the D class is overriding the A class functions (if exist)
*/

/* ACCESS MODIFIERS
* 
* Public:
* All the public class members are available to everyone
* All the public members are available from anywhere in the program with member access operator "instance.member"
* 
* Private:
* All the member declered as private can be accessed only by the member functions inside the class or from friend class
* 
* Protected:
* All the member declered as protected can be accessed only by the member functions insided class or from subclasses
* 
*/

/* FRIEND function
* friend functions are functions declered as friednd inside the class but defined outside.
* friend functions can access private members of the class by an instance passed by reference
*/
