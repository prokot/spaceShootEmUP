#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
	int lives;
	float x, y,time1,movespeed;
	sf::Texture entityt;
	sf::Sprite* entity;

public:
	Entity();
	void update();
	sf::Sprite getEntity();
	void setEntity(sf::Sprite* entityy);


	float getX();
	float getY();

	void setX(float xx);
	void setY(float yy);

	int getLives();
	void setLives(int livess);

	float getMoveSpeed();
	void setMoveSpeed(float speed);

	void moveRight();
	void moveDown();
	void moveUp();
	void moveLeft();
};

