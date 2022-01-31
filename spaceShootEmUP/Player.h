#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
class Player : public Entity
{
	int  status,firingCD;

public:
	Player();
	
	void setStatus(int stat);
	int getStatus();
	void fire();

	void setFiringCD(int firing);
	int getFiringCD();
	~Player();
};

