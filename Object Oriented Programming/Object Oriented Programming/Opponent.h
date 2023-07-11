#pragma once
#include "Enemy.h"
#include "Player.h"
class Opponent : public Enemy, public Player
{
	public:
	//function Overriding through inheritance
	void WhoAmI() override;
};

