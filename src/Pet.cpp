#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "../include/Constants.h"
#include "../include/Pet.h"
#include "../include/Game.h"
#include "../include/Sprites.h"

Pet::Pet(Game *game)
{
    this->game = game;
    this->player = game->getPlayer();
    position.x = player->getPosition().x + 100.f;
    position.y = player->getPosition().y + 100.f;
}

Pet::~Pet()
{
}

void Pet::update(double deltaTime)
{

    // Moves the Pet.
    // Gets coordinates of a point between player and a pet that is FLOAT_MAX_PET_DISTANCE far from player.
    float distance = sqrt(pow(position.x - player->getPosition().x, 2) + pow(position.y - player->getPosition().y, 2));
    float destPositionX = player->getPosition().x + (FLOAT_MAX_PET_DISTANCE / distance) * (position.x - player->getPosition().x);
    float destPositionY = player->getPosition().y + (FLOAT_MAX_PET_DISTANCE / distance) * (position.y - player->getPosition().y);

    // Sets new Pet position.
    float x = (destPositionX - position.x) / FLOAT_MAX_PET_VELOCITY;
    float y = (destPositionY - position.y) / FLOAT_MAX_PET_VELOCITY;
    position.x = position.x + x * deltaTime * 100;
    position.y = position.y + y * deltaTime * 100;

    // FIXME! std::cout << "petpos = " << position.x << ", " << position.y << "\n";
}

void Pet::draw()
{
    game->drawSprite(position.x, position.y, SPRITE_PET, 1.f, player->getPosition().x < position.x, true, true, true);
}