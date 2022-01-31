#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#define WIDTH 660
#define HEIGHT 380

Player::Player() {
	setLives(3);
	setY(HEIGHT / 3);
	setX(0);
	setMoveSpeed(0.1);
	status = 0;
	firingCD = 0;
	//creating new texture and sprite for the entity
	sf::Texture *playert = new sf::Texture();
	sf::Sprite *player = new sf::Sprite();
	playert->loadFromFile("Graphics/player.png");
	//scaling the texture
	player->scale(sf::Vector2f(0.05f, 0.05f));
	player->setPosition(sf::Vector2f(getX(), getY())); // absolute position

	player->setTexture(*playert);
	setEntity(player);
}


void Player::setStatus(int stat) {
	status = stat;
}

int Player::getStatus() {
	return status;
}

void Player::setFiringCD(int firing) {
	firingCD = firing;
}

int Player::getFiringCD() {
	return firingCD;
}

Player::~Player() {
	delete(getEntity().getTexture());
}