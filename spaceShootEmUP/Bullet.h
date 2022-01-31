#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <SFML/Window.hpp>

#define WIDTH 660
#define HEIGHT 380
class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();
};
