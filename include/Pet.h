#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Game;

class Pet
{
private:
    sf::Vector2f position;
    Game *game;
    Player *player;

public:
    Pet(Game *game);
    virtual ~Pet();

    // Functions
    void update(double deltaTime);
    void draw();
};
