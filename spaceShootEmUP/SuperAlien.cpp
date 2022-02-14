#include "SuperAlien.h"

#define WIDTH 660
#define HEIGHT 380
SuperAlien::SuperAlien() {
	setLives(2);
	setY(HEIGHT / 2);
	setX(WIDTH);
	setMoveSpeed(0.02);
	//creating new texture and sprite for the entity
	sf::Texture* alient = new sf::Texture();
	sf::Sprite* alien = new sf::Sprite();
	alient->loadFromFile("Graphics/superalien.png");
	//scaling texture
	alien->scale(sf::Vector2f(0.2f, 0.2f));
	alien->setPosition(sf::Vector2f(getX(), getY())); // absolute position

	alien->setTexture(*alient);
	setEntity(alien);
}

SuperAlien::~SuperAlien() {
	delete(getEntity().getTexture());
}