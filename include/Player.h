#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Inventory.h"
#include "Hitbox.h"

class Game;

class Player
{
private:
    sf::Vector2f position;
    sf::Vector2f rawPosition, rawUnnormalizedPosition;
    Game *game;
    Inventory inventory;
    HitBox hitbox;

public:
    Player(Game *game);
    virtual ~Player();

    // Functions
    void update(double deltaTime);
    void draw();
    sf::Vector2f getPosition();
    Inventory *getInventory();
    HitBox *getHitbox();
};
