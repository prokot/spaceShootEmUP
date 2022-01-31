#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Bullet::Bullet() {
	setLives(1);
	setMoveSpeed(0.25);
	setX(WIDTH / 2);
	setY(HEIGHT / 2);
	//creating new texture and sprite for the entity
	sf::Texture* tempt = new sf::Texture();
	sf::Sprite* bullet = new sf::Sprite();
	tempt->loadFromFile("Graphics/bullet.png");
	//scaling texture
	bullet->scale(sf::Vector2f(0.01f, 0.01f));
	bullet->setPosition(sf::Vector2f(getX(), getY())); // absolute position

	bullet->setTexture(*tempt);
	setEntity(bullet);
}


//trying to save memory
Bullet::~Bullet(){
	delete(getEntity().getTexture());
}