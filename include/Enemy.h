#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Game;

class Enemy
{
private:
    sf::Vector2f position;
    Game *game;
    Player *player;
    float speed = 2.f;

public:
    Enemy(sf::Vector2f position, Game *game);
    virtual ~Enemy();

    // Functions
    void update(double deltaTime);
    void draw();
    sf::Vector2f getPosition();
};
