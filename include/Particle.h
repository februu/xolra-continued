#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Game;

class Particle
{
protected:
    sf::Vector2f position;
    float lifetime = 0.f, maxLifetime;
    Game *game;

public:
    Particle(){};
    virtual ~Particle(){};

    // Functions
    virtual bool update(double deltaTime) { return false; };
    virtual void draw(){};
};

class TextParticle : public Particle
{
private:
    std::string text;
    sf::Color color;
    float scale;

public:
    TextParticle(sf::Vector2f position, std::string text, sf::Color, float scale, float maxLifetime, Game *game);
    virtual ~TextParticle();

    // Functions
    virtual bool update(double deltaTime);
    virtual void draw();
};