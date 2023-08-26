#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Game;

class Player
{
private:
    sf::Vector2f position;
    sf::Vector2f rawPosition, rawUnnormalizedPosition;
    Game *game;
    sf::RectangleShape hitbox;

public:
    Player(Game *game);
    virtual ~Player();

    // Functions
    void update(double deltaTime);
    void draw();
    sf::Vector2f getPosition();
};
