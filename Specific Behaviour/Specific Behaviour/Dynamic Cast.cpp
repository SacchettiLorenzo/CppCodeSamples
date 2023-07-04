#include <iostream>
#include <string>

class Entity {
public:
    virtual void Printname(){}
};

class Player : public Entity {

};

class Enemy : public Entity {

};


int main()
{
    Player* player = new Player();    // the type player has 3 types: "Entity" and "Player"
    Entity* player = new Player(); //implicit cast

    Entity* e1 = new Enemy();

    Player* p = (Player*)e1;//accepted but is dangerous because "Enemy" could have different functions than "Player" causing crash

    Player* p1 = dynamic_cast<Player*>(e1); // accepted and safe "Entity" neew to be a polimorphic class (virtual function)
}

//dynamic cast is evalueted at runtime making extra checks for code safaty
// it is mainly used for inheritance casting (upcast and downcast)
// if the cast is valid (Entity -> Player) the cast will perform normally
// if the cast in not valid (Enemy -> Player) the cast will perform with perform with a null value (we can perform control if the value is null after the cast)



// This is possible thank to RTTI (Run Time Type Information) that keep infromation about types and class

//dynamic cast take more time to perform than an implicit cast because it check if the types are compatible
//if types are not compattible the programm will not crash