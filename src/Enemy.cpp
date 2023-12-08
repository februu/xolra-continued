#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Constants.h"
#include "../include/Enemy.h"
#include "../include/Math.h"
#include "../include/Game.h"
#include "../include/Sprites.h"

Enemy::Enemy(sf::Vector2f position, Game *game)
{
    this->game = game;
    this->player = game->getPlayer();
    this->position = position;
    this->hitbox = sf::RectangleShape({40, 40});
}

Enemy::~Enemy()
{
}

void Enemy::update(double deltaTime)
{

    // Moves enemy by the same distance every frame in direction given by normalized vector.
    sf::Vector2f direction = player->getPosition() + sf::Vector2f(20, 20) + game->getCamera()->getOffset() - position;
    direction = normalize(direction);
    position += sf::Vector2f(direction.x * deltaTime * 50 * speed, direction.y * deltaTime * 50 * speed);
}

void Enemy::draw()
{
    // Draws Enemy.
    sf::CircleShape shapes(20);
    shapes.setFillColor(sf::Color(255, 255, 255));
    shapes.setPosition({position.x - 2 * game->getCamera()->getOffset().x - 20, position.y - 2 * game->getCamera()->getOffset().y - 20});
    game->getWindow()->draw(shapes);

    // Draws health bar.
    // float healthFactor = (float)health / max_health;
    // sf::RectangleShape healthBar(sf::Vector2f(30 * FLOAT_TILESCALE * healthFactor, 6 * FLOAT_TILESCALE));
    // healthBar.setPosition(position.x - FLOAT_TILESCALE * (16 - 1) - FLOAT_TILESCALE * game->getCamera()->getOffset().x, position.y - 20 - FLOAT_TILESCALE * (12 - 1) - FLOAT_TILESCALE * game->getCamera()->getOffset().y);
    // if (healthFactor > 0.66f)
    //     healthBar.setFillColor(sf::Color(100, 125, 52, 255));
    // else if (healthFactor > 0.33f)
    //     healthBar.setFillColor(sf::Color(228, 148, 58, 255));
    // else
    //     healthBar.setFillColor(sf::Color(157, 48, 59, 255));
    // game->getWindow()->draw(healthBar);
    // game->drawSprite(position.x, position.y - 20 - FLOAT_TILESCALE * 12, SPRITE_HUD_HEALTH_BAR, FLOAT_TILESCALE, false, true, true);

    // Draws hitbox.
    // sf::RectangleShape hitboxShape(hitbox.getSize());
    // hitboxShape.setPosition(position);
    // game->getWindow()->draw(hitboxShape);
}

sf::Vector2f Enemy::getPosition()
{
    return position;
}

sf::Vector2f Enemy::getHitboxPosition()
{
    return position - sf::Vector2f(20, 20);
}

sf::Vector2f Enemy::getHitboxSize()
{
    return hitbox.getSize();
}

bool Enemy::dealDamage(int damage)
{
    health -= damage;
    return health < 0;
}