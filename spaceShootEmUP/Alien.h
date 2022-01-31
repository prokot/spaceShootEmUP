#pragma once
#include "Entity.h"
#include <time.h>
class Alien : public Entity
{
	time_t time1;
	int dir;
public:
	Alien();
	void update();
	void changePos();
	~Alien();
};

