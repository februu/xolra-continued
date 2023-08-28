#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "include/Projectile.h"
#include "include/Enemy.h"
#include "include/Game.h"
#include "include/Constants.h"
#include "include/Math.h"
#include <iostream>

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, Game *game)
{
    this->game = game;
    this->position = position;

    // Applies random offset to bullet and normalizes direction vector.
    direction = normalize(direction);
    std::uniform_real_distribution<float>
        dis(-0.1f, 0.1f);
    this->direction = normalize(sf::Vector2f(direction.x + dis(game->gen), direction.y + dis(game->gen)));
}

Projectile::~Projectile()
{
}

bool Projectile::update(double deltaTime)
{

    // Deletes projectile if it travelled for too long without reaching the target.
    if (travelledDistance > maxDistance)
        return true;

    // Moves projectile by the same distance every frame in direction given by normalized vector.
    position += sf::Vector2f(direction.x * deltaTime * 1000, direction.y * deltaTime * 1000);
    travelledDistance += sqrt((direction.x * direction.x) + (direction.y * direction.y));
    return false;
}

void Projectile::draw()
{
    sf::CircleShape shapes(5);
    shapes.setFillColor(sf::Color(255, 255, 160));
    shapes.setPosition({position.x - 2 * game->getCamera()->getOffset().x - 5, position.y - 2 * game->getCamera()->getOffset().y - 5});
    game->getWindow()->draw(shapes);
}