#include "Alien.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <time.h>

#define WIDTH 660
#define HEIGHT 380

Alien::Alien() {
	setLives(1);
	setY(HEIGHT / 2);
	setX(WIDTH);
	time1 = 0;
	dir = 0;
	setMoveSpeed(0.01);
	//creating new texture and sprite for the entity
	sf::Texture* alient = new sf::Texture();
	sf::Sprite* alien = new sf::Sprite();
	alient->loadFromFile("Graphics/alien.png");
	//scaling texture
	alien->scale(sf::Vector2f(0.2f, 0.2f));
	alien->setPosition(sf::Vector2f(getX(), getY())); // absolute position

	alien->setTexture(*alient);
	setEntity(alien);
}

//change sprite position to current x and y, basically an update
void Alien::changePos() {
	
	sf::Sprite temp = getEntity();
	temp.setPosition(sf::Vector2f(getX(), getY())); // absolute position
	setEntity(&temp);
}


//random movement method
void Alien::update() {
	//setting seed
	srand(time(NULL));

	time_t rollTime;
	double seconds;
	rollTime = time(NULL);
	//if first time, set variable to current time
	if (time1 == 0) {
		time1 = rollTime;
	}
	else {
		//calculate difference to check if passed
		seconds = difftime(rollTime, time1);
		// 3 seconds until changing he direction
			if (seconds > 3) {
				//randomizing direction and resetting timer
				dir = rand() % 4;
				time1 = rollTime;
			}
			else {
				//basic switch case indicating what random direction the alien moves
				switch (dir) {
				case 0:
					moveLeft();
					break;
				case 1:
					moveRight();
					break;
				case 2:
					moveUp();
					break;
				case 3:
					moveDown();
					break;
				default:
					break;
				}
			}
	}
}

Alien::~Alien() {
	delete(getEntity().getTexture());
}