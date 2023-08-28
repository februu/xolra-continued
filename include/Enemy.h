#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Game;

class Enemy
{
private:
    sf::Vector2f position;
    sf::RectangleShape hitbox;
    Game *game;
    Player *player;
    float speed = 3.f;
    int health = 30;

public:
    Enemy(sf::Vector2f position, Game *game);
    virtual ~Enemy();

    // Functions
    void update(double deltaTime);
    void draw();
    sf::Vector2f getPosition();
    sf::Vector2f getHitboxSize();
    sf::Vector2f getHitboxPosition();
    bool dealDamage(int damage);
};
