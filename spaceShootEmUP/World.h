#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <time.h>
#include "Alien.h"
#include "Player.h"
#include "Bullet.h"
#include "SuperAlien.h"

#define WIDTH 660
#define HEIGHT 380

using namespace std;

class World
{
	vector <Alien*> enemies;
	Player *player;
	Bullet* bullet;
	int score;
	int time1;
	sf::RenderWindow *window;
public:
	World();
	void spawnEnemies();

	void detectCollision();

	void updateEnemies();

	void renderEnemies();

	void fire();

	void handleKeys();

	void game();


	~World();
};

