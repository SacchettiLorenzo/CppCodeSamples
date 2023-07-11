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

        
      
        __debugbreak();

        
       

        


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
