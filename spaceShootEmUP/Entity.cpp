#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#define WIDTH 660
#define HEIGHT 380

Entity::Entity() {
	lives = 1;
	y = HEIGHT / 2;
	x = WIDTH;
	movespeed = 0.1;

}


float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

sf::Sprite Entity::getEntity()
{
	return *entity;
}

void Entity::setEntity(sf::Sprite *entityy)
{
	entity = entityy;
}


void Entity::setX(float xx) {
	x = xx;
}
void Entity::setY(float yy) {
	y = yy;
}

int Entity::getLives() {
	return lives;
}
void Entity::setLives(int livess) {
	lives = livess;
}


float Entity::getMoveSpeed() {
	return movespeed;
}
void Entity::setMoveSpeed(float speed) {
	movespeed = speed;
}

void Entity::update() {
	entity->setPosition(sf::Vector2f(x, y)); // absolute position

}



void Entity::moveRight() {
	if(x< WIDTH - (entity->getTexture()->getSize().x * entity->getScale().x)){
	x = x + movespeed;
	update();
	}
}
void Entity::moveDown() {
	if (y < HEIGHT - (entity->getTexture()->getSize().y * entity->getScale().y)) {
	y = y + movespeed;
	update();
	}
}
void Entity::moveUp() {
	if (y > 0) {
	y = y - movespeed;
	update();
	}
}
void Entity::moveLeft() {
	if (x > 0) {
	x = x - movespeed;
	update();
	}
}