#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "include/Constants.h"
#include "include/Math.h"
#include "include/Game.h"
#include "include/Player.h"
#include "include/Camera.h"

Player::Player(Game *game)
{
    this->game = game;
    rawPosition.x = 600.f;
    rawPosition.y = 400.f;
    position.x = 600.f;
    position.y = 400.f;
    hitbox = sf::RectangleShape(sf::Vector2f(50, 50));
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

    // Collision check.

    // Example hitbox.
    // sf::FloatRect squareBox(200.f, 200.f, 200.f, 200.f);

    // sf::FloatRect currentHitbox(rawPosition.x + game->getCamera()->getOffset().x, rawPosition.y + game->getCamera()->getOffset().y, hitbox.getSize().x, hitbox.getSize().y);
    // if (squareBox.intersects(currentHitbox))
    // {
    //     // Check side
    //     const float TOLERANCE = 20.f;

    //     // X-axis collision check.
    //     if ((currentHitbox.left + currentHitbox.width - squareBox.left) < TOLERANCE)
    //     {
    //         float penetration = currentHitbox.left + currentHitbox.width - squareBox.left;
    //         rawPosition.x -= penetration;
    //     }
    //     else if ((squareBox.left + squareBox.width - currentHitbox.left) < TOLERANCE)
    //     {
    //         float penetration = squareBox.left + squareBox.width - currentHitbox.left;
    //         rawPosition.x += penetration;
    //     }

    //     // Y-axis collision check.
    //     if ((currentHitbox.top + currentHitbox.height - squareBox.top) < TOLERANCE)
    //     {
    //         float penetration = currentHitbox.top + currentHitbox.height - squareBox.top;
    //         rawPosition.y -= penetration;
    //     }
    //     else if ((squareBox.top + squareBox.height - currentHitbox.top) < TOLERANCE)
    //     {
    //         float penetration = squareBox.top + squareBox.height - currentHitbox.top;
    //         rawPosition.y += penetration;
    //     }
    // }

    // Normalizes vector (prevents diagonal movement from being faster).
    float normalizeVector = 1.f;
    if (resultant.x != 0 && resultant.y != 0)
        normalizeVector = 0.70f;

    // Calculates amount of pixels player should move.
    float _changeX = FLOAT_MAX_VELOCITY * resultant.x * deltaTime * 100;
    float _changeY = FLOAT_MAX_VELOCITY * resultant.y * deltaTime * 100;

    // Calculates new positions for player.
    rawPosition.x = clamp(rawPosition.x + _changeX * normalizeVector, 0, 2560 - 50);
    rawPosition.y = clamp(rawPosition.y + _changeY * normalizeVector, 0, 2140 - 50);

    float x = (rawPosition.x - position.x) / 5;
    float y = (rawPosition.y - position.y) / 5;
    position.x = position.x + x * deltaTime * 100;
    position.y = position.y + y * deltaTime * 100;
}

void Player::draw()
{

    // FIXME: Add assets/remove circles.
    //  Radius = 25.

    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition({position.x - game->getCamera()->getOffset().x, position.y - game->getCamera()->getOffset().y});
    game->getWindow()->draw(shape);

    sf::CircleShape shapes(5);
    shapes.setFillColor(sf::Color(255, 255, 255));
    shapes.setPosition({rawPosition.x - game->getCamera()->getOffset().x + 20, rawPosition.y - game->getCamera()->getOffset().y + 20});
    game->getWindow()->draw(shapes);
}

sf::Vector2f Player::getPosition()
{
    return position;
}
