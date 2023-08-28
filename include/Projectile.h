#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Game;

class Projectile
{
private:
    sf::Vector2f position, direction;
    Game *game;
    float travelledDistance = 0;
    float maxDistance = 500;

public:
    Projectile(sf::Vector2f position, sf::Vector2f direction, Game *game);
    virtual ~Projectile();

    // Functions
    bool update(double deltaTime);
    void draw();
};
