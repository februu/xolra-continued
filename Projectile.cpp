#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "include/Projectile.h"
#include "include/Enemy.h"
#include "include/Game.h"
#include "include/Constants.h"
#include "include/Math.h"
#include "include/Sprites.h"
#include "include/Particle.h"
#include <iostream>

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, Game *game)
{
    this->game = game;
    this->position = position;

    // Applies random offset to bullet and normalizes direction vector.
    direction = normalize(direction);
    std::uniform_real_distribution<float>
        dis(-0.07f, 0.07f);
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

    sf::FloatRect selfHitbox({position.x - (8 * FLOAT_TILESCALE / 2), position.y - (8 * FLOAT_TILESCALE / 2), 8 * FLOAT_TILESCALE, 8 * FLOAT_TILESCALE});
    for (auto enemy = begin(game->getWorld()->enemies); enemy != end(game->getWorld()->enemies); ++enemy)
    {
        sf::FloatRect enemyHitbox({enemy->getHitboxPosition().x, enemy->getHitboxPosition().y, enemy->getHitboxSize().x, enemy->getHitboxSize().y});
        if (selfHitbox.intersects(enemyHitbox))
        {
            TextParticle particle(position - game->getCamera()->getOffset() - game->getCamera()->getOffset(), "10.7", sf::Color::Yellow, 24.f, 0.2f, game);
            game->getWorld()->textParticles.push_back(particle);
            if (enemy->dealDamage(10.7))
                game->getWorld()->enemies.erase(enemy--);
            return true;
        }
    }

    // Moves projectile by the same distance every frame in direction given by normalized vector.
    position += sf::Vector2f(direction.x * deltaTime * 1000, direction.y * deltaTime * 1000);
    travelledDistance += sqrt((direction.x * direction.x) + (direction.y * direction.y));
    return false;
}

void Projectile::draw()
{
    game->drawSprite(position.x - 2, position.y, SPRITE_BULLET, 2, false, true, true, true);
}