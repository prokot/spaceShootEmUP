#include "World.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace sf;

World::World() {
    //game time
    time1 = time(NULL);
	score = 0;
    //player init
    Player *player1 = new Player();
    player = player1;
    //window init
    sf::RenderWindow *win = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Space Shoot'em Up!");
    window = win;

}


//spawn enemies
void World::spawnEnemies() {
        enemies.push_back(new Alien()); // polimorphism
        if (time1 % 10 == 0) {
            enemies.push_back(new SuperAlien());
        }
}

//function basically updating position and calling overridden function update in Alien class
void World::updateEnemies() {
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->update();
        if (enemies[i]->getLives() <= 0) {
            delete(enemies[i]);
            enemies.erase(enemies.begin() + i);
        }
    }
}

//function for rendering vector of enemies
void World::renderEnemies() {
    for (int i = 0; i < enemies.size(); i++) {
        window->draw(enemies[i]->getEntity());
    }
}

//method for detecting all collision
void World::detectCollision() {
    for (int i = 0; i < enemies.size(); i++) {
        //sfml types specyfing bounds
        FloatRect playerBounds = player->getEntity().getGlobalBounds();
        FloatRect enemyBounds = enemies[i]->getEntity().getGlobalBounds();
        
        //sfml provides a method for basic collision called intersects
        //here we check collision between player and enemy, substract life count if hit
        if (enemyBounds.intersects(playerBounds)&&player->getStatus() == 0) {
            player->setLives(player->getLives() - 1);
            player->setStatus(1);
        }

        //same thing with bullet and enemy collision, kill enemy, destroy bullet entity on hit and update score
        if (player->getFiringCD() == 1) {
            FloatRect bulletBounds = bullet->getEntity().getGlobalBounds();
        
        if (enemyBounds.intersects(bulletBounds)) {
            score++;
            delete(bullet);
            player->setFiringCD(0);
            enemies[i]->setLives(enemies[i]->getLives() - 1);
        }
        }
    }
}

//firing bullet
void World::fire() {
    // set cooldown
    player->setFiringCD(1);
    Bullet* blt = new Bullet();

    //spawn bullet at the right side of player
    blt->setX(player->getX() + player->getEntity().getTexture()->getSize().x * player->getEntity().getScale().x);
    blt->setY(player->getY() + (player->getEntity().getTexture()->getSize().y * player->getEntity().getScale().y)/2);
    bullet = blt;
}

void World::handleKeys() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // Right key is pressed: move our character
        player->moveRight();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // left key is pressed: move our character
        player->moveLeft();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // Up is pressed: move our character
        player->moveUp();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // Down is pressed: move our character
        player->moveDown();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&player->getFiringCD() == 0)
    {
        // Space is pressed: fire weapon
        fire();
    }
}


// main game code
void World::game() {

    time_t startTime = time(NULL);
    bool gameover = 0;

    //flags for timers logic operations
    bool spawnflag= 1,statusflag = 0,bulletflag=0;

    //frequency of enemy spawn time, and initation of timers
    int spawnTime = 3,statusTimer = 0,fireTimer = 0,tempTime = 0;

    //setting background img
    sf::Texture bkgrnd;
    bkgrnd.loadFromFile("Graphics/background.png");
    sf::Sprite spritebg;
    spritebg.setTexture(bkgrnd);

    //initializing text parameters
    sf::Font font;
    if (!font.loadFromFile("JMHTypewriter.ttf")) {
    printf("nie dziala");
    }
    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Underlined);

    //main game loop
    while (window->isOpen() && gameover == 0)
    {

        //getting events in the window
        sf::Event event;
        while (window->pollEvent(event))
        {
            //handling window closing
            if (event.type == sf::Event::Closed)
                window->close();
        }

        //spawning enemies in a loop
        if (time1 % spawnTime == 0 && spawnflag == 1) {
            spawnEnemies();
            spawnflag = 0;
            tempTime = time1 + spawnTime;
        }

        //rendering 
        window->clear();
        //updating entities before drawing
        player->update();
        updateEnemies();

        //drawing bckgrnd
        window->draw(spritebg);

        
        //handling key presses events
        handleKeys();

        //setting current time (int)
        time_t currTime = time(NULL);
        time1 = difftime(currTime, startTime);

        //there was a problem with time being an int, the loop spawned enemies for entire second every {spawntime} seconds.
        //this is a workaround using a spawntime cooldown of 1 second
        if (time1 >= tempTime) {
            spawnflag = 1;
        }

        //setting firing cd and bullet entity handling
        if (player->getFiringCD() == 1) {
            if( bulletflag == 0)
            fireTimer = time1;
            bullet->moveRight();
            window->draw(bullet->getEntity());
            bulletflag = 1;
        }
        if (player->getFiringCD() == 1 && time1 - fireTimer >= 1) {
            player->setFiringCD(0);
            delete(bullet);
            bulletflag = 0;
        }
        
        //setting invincibility status after taking a hit
        if (player->getStatus() == 1 && statusflag ==0) {
            statusTimer = time1;
            statusflag = 1;
        }
        if (player->getStatus()== 1&&time1 - statusTimer >= 1) {
            player->setStatus(0);
            statusflag = 0;
        }
       
        renderEnemies();
        
        string txt = to_string(score);
        // set the string to display
        text.setString(txt);
        window->draw(text);

        //render player
        window->draw(player->getEntity());

        //collision detection
        detectCollision();

        //check if player lost all lives
        if (player->getLives() <= 0) {
            gameover = 1;
        }

        window->display();
    }
}

//once again trying to save memory
World::~World() {
    delete(player);
        for (int i= 0; i < enemies.size(); i++) {
            delete(enemies[i]);
        }
}