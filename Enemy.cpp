#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Constants.h"
#include "include/Enemy.h"
#include "include/Game.h"

Enemy::Enemy(sf::Vector2f position, Game *game)
{
    this->game = game;
    this->player = game->getPlayer();
    this->position = position;
}

Enemy::~Enemy()
{
}

void Enemy::update(double deltaTime)
{
}

void Enemy::draw()
{
    sf::CircleShape shapes(40);
    shapes.setFillColor(sf::Color(255, 255, 255));
    shapes.setPosition({position.x - 2 * game->getCamera()->getOffset().x - 40, position.y - 2 * game->getCamera()->getOffset().y - 40});
    game->getWindow()->draw(shapes);
}

sf::Vector2f Enemy::getPosition()
{
    return position;
}