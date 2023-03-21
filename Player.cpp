#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "include/Constants.h"
#include "include/Math.h"
#include "include/Game.h"
#include "include/Player.h"
#include "include/Camera.h"
#include "include/Inventory.h"

Player::Player(Game *game)
{
    this->game = game;
    rawPosition.x = 600.f;
    rawPosition.y = 400.f;
    position.x = 600.f;
    position.y = 400.f;
}

Player::~Player()
{
}

void Player::update(double deltaTime)
{

    // Moves the player.
    sf::Vector2i resultant = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        resultant.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        resultant.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        resultant.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        resultant.y += 1;

    // Normalizes vector (prevents diagonal movement from being faster).
    float normalizeVector = 1.f;
    if (resultant.x != 0 && resultant.y != 0)
        normalizeVector = 0.71f;

    // Sets new player'rawPosition.

    rawPosition.x = rawPosition.x + FLOAT_MAX_VELOCITY * resultant.x * normalizeVector * deltaTime * 100;
    rawPosition.y = rawPosition.y + FLOAT_MAX_VELOCITY * resultant.y * normalizeVector * deltaTime * 100;

    // Sets actual player position.
    float x = (rawPosition.x - position.x) / 5;
    float y = (rawPosition.y - position.y) / 5;
    position.x = position.x + x * deltaTime * 100;
    position.y = position.y + y * deltaTime * 100;
}

void Player::draw()
{

    // Radius = 25.
    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition({position.x - 25 - game->getCamera()->getOffset().x, position.y - 25 - game->getCamera()->getOffset().y});
    game->getWindow()->draw(shape);

    // Radius = 5.
    shape.setRadius(5);
    shape.setFillColor(sf::Color(255, 255, 255));
    shape.setPosition({rawPosition.x - 5 - game->getCamera()->getOffset().x, rawPosition.y - 5 - game->getCamera()->getOffset().y});
    game->getWindow()->draw(shape);
}

sf::Vector2f Player::getPosition()
{
    return position;
}

Inventory *Player::getInventory()
{
    return &inventory;
}