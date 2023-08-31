#pragma once

#include <map>
#include <random>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Item.h"
#include "Projectile.h"
#include "Particle.h"
#include "Enemy.h"

class Game;

class World
{
private:
    Game *game;
    const int WORLDSIZE = INT_WORLDSIZE;
    int tilemap[INT_WORLDSIZE][INT_WORLDSIZE];
    std::vector<Item> items;

    // Projectiles
    float projectileTimer = 0;

    // Enemies
    float enemyTimer = 0;

    // Random Distributions
    std::uniform_int_distribution<int> intDistribution;
    std::uniform_real_distribution<float> widthDistribution;
    std::uniform_real_distribution<float> heightDistribution;

    int loadMapFromFile();

public:
    World(Game *game);
    virtual ~World();

    int *getWorld();
    void update(double deltaTime);
    void draw(double timeFromStart);
    std::vector<Enemy> enemies;
    std::vector<TextParticle> textParticles;
    std::vector<Projectile> projectiles;
};
