#pragma once
#include "Entity.h"
class Player : virtual public Entity
{
	public:
	//function Overriding through inheritance
	void WhoAmI() override;
};

//subclass of Entity

/* Virtual inheritalnce
* a virtual base class is a class that is shared by multiple classes.
* To avoid ambigiuty and to ensure that the class is inherited in the final derived class only one time
* the base class is virtual
* see diamond Inheritance
* 
*/


