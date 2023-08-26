#include <SFML/Graphics.hpp>
#include "include/Projectile.h"
#include "include/Enemy.h"
#include "include/Game.h"
#include "include/Constants.h"
#include "include/Math.h"
#include <iostream>

Projectile::Projectile(sf::Vector2f position, Game *game)
{
    this->game = game;
    this->position = position;
}

Projectile::~Projectile()
{
}

bool Projectile::update(double deltaTime)
{
    // Search for target.
    target == nullptr;
    float smallestDistance = -1.f;
    for (auto enemy : game->getWorld()->enemies)
    {
        // Searches for nearby enemies. Only targets enemies within 400 units of range.
        sf::Vector2f direction = enemy.getPosition() + game->getCamera()->getOffset() - position;
        if ((smallestDistance < 0 || smallestDistance > (direction.x * direction.x) + (direction.y * direction.y)) && (direction.x * direction.x) + (direction.y * direction.y) < 400 * 400)
            target = &enemy;
    };

    // Deletes projectile if it travelled for too long without reaching the target.
    if (travelledDistance > maxDistance || target == nullptr || game->getWorld()->enemies.size() == 0)
        return true;

    // Moves projectile by the same distance every frame in direction given by normalized vector.
    sf::Vector2f direction = target->getPosition() - position;
    direction = normalize(direction);
    position += sf::Vector2f(direction.x * deltaTime * 600, direction.y * deltaTime * 600);
    travelledDistance++;
    return false;
}

void Projectile::draw()
{
    sf::CircleShape shapes(5);
    shapes.setFillColor(sf::Color(255, 255, 160));
    shapes.setPosition({position.x - 2 * game->getCamera()->getOffset().x - 5, position.y - 2 * game->getCamera()->getOffset().y - 5});
    game->getWindow()->draw(shapes);
}