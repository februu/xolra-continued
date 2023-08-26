#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Game;

class Projectile
{
private:
    sf::Vector2f position;
    Enemy *target = nullptr;
    Game *game;

    int travelledDistance = 0;
    int maxDistance = 300;

public:
    Projectile(sf::Vector2f position, Game *game);
    virtual ~Projectile();

    // Functions
    bool update(double deltaTime);
    void draw();
};
