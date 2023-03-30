#pragma once

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Hitbox.h"
#include "Item.h"

class Game;

class World
{
private:
    Game *game;
    const int WORLDSIZE = INT_WORLDSIZE;
    int tilemap[INT_WORLDSIZE][INT_WORLDSIZE];
    std::vector<Item> items;

    // FIXME: Add list of entities.
    std::vector<HitBox> hitboxes;

    int loadMapFromFile();

public:
    World(Game *game);
    virtual ~World();

    int *getWorld();
    void update(double deltaTime);
    void draw(double timeFromStart);
    std::vector<HitBox> *getHitBoxes();
};
