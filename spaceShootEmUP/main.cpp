#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "World.h"

#define WIDTH 660
#define HEIGHT 380

int main()
{
    //init game
    World world;
    world.game();
    return 0;
}