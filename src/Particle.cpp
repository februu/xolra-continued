#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "../include/Constants.h"
#include "../include/Particle.h"
#include "../include/Game.h"
#include "../include/Sprites.h"

TextParticle::TextParticle(sf::Vector2f position, std::string text, sf::Color color, float scale, float maxLifetime, Game *game)
{
    this->position = position;
    this->text = text;
    this->color = color;
    this->scale = scale;
    this->game = game;
    this->maxLifetime = maxLifetime;
}

TextParticle::~TextParticle()
{
}

bool TextParticle::update(double deltaTime)
{
    if (lifetime > maxLifetime)
        return true;

    // Moves text upwards.
    position -= sf::Vector2f(0, deltaTime * 25);
    lifetime += deltaTime;
    return false;
}

void TextParticle::draw()
{
    game->drawText(position.x, position.y, text, DEFAULT_FONT, scale, true, true, color);
}