#pragma once

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Item.h"
#include "Projectile.h"
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
    double projectileTimer = 0;
    std::vector<Projectile> projectiles;

    int loadMapFromFile();

public:
    World(Game *game);
    virtual ~World();

    int *getWorld();
    void update(double deltaTime);
    void draw(double timeFromStart);
    std::vector<Enemy> enemies;
};
