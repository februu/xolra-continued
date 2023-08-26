#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "include/Constants.h"
#include "include/Math.h"
#include "include/Game.h"
#include "include/Player.h"
#include "include/Camera.h"
#include "include/Hitbox.h"

Player::Player(Game *game)
{
    this->game = game;
    rawPosition.x = 600.f;
    rawPosition.y = 400.f;
    position.x = 600.f;
    position.y = 400.f;
    hitbox = HitBox(position, sf::Vector2f(50, 50));
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

    // TODO: Clamp this value between 0 - 1600 px.
    sf::Vector2f oldRawPosition = rawPosition;

    // Calculates amount of pixels player should move.
    float _changeX = FLOAT_MAX_VELOCITY * resultant.x * deltaTime * 100;
    float _changeY = FLOAT_MAX_VELOCITY * resultant.y * deltaTime * 100;

    // Calculates new (future) positions for player.
    rawUnnormalizedPosition.x = rawPosition.x + _changeX;
    rawUnnormalizedPosition.y = rawPosition.y + _changeY;
    rawPosition.x = rawPosition.x + _changeX * normalizeVector;
    rawPosition.y = rawPosition.y + _changeY * normalizeVector;

    // Sets actual player position.
    float x = (rawPosition.x - position.x) / 5;
    float y = (rawPosition.y - position.y) / 5;
    position.x = position.x + x * deltaTime * 100;
    position.y = position.y + y * deltaTime * 100;

    // Collision check.
    for (auto hb = begin(*game->getWorld()->getHitBoxes()); hb != end(*game->getWorld()->getHitBoxes()); ++hb)
    {

        // Horizontal collision;
        hitbox.updatePosition({rawPosition.x, oldRawPosition.y});
        if (hb->checkIfCollides(hitbox))
        {
            rawPosition = {oldRawPosition.x, rawUnnormalizedPosition.y};
            hitbox.updatePosition({oldRawPosition.x, rawUnnormalizedPosition.y});
            continue;
        }

        // Vertical collision.
        hitbox.updatePosition({oldRawPosition.x, rawPosition.y});
        if (hb->checkIfCollides(hitbox))
        {
            rawPosition = {rawUnnormalizedPosition.x, oldRawPosition.y};
            hitbox.updatePosition({rawUnnormalizedPosition.x, oldRawPosition.y});
            continue;
        }
    }
}

void Player::draw()
{

    // FIXME: Add assets/remove circles.
    //  Radius = 25.
    sf::CircleShape shape(25);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition({position.x - game->getCamera()->getOffset().x, position.y - game->getCamera()->getOffset().y});
    game->getWindow()->draw(shape);
}

sf::Vector2f Player::getPosition()
{
    return position;
}

HitBox *Player::getHitbox()
{
    return &hitbox;
}