#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <random>
#include "../include/Constants.h"
#include "../include/Math.h"
#include "../include/World.h"
#include "../include/Game.h"
#include "../include/Enemy.h"
#include "../include/Camera.h"
#include "../include/Item.h"
#include "../include/Sprites.h"
#include "../include/Projectile.h"

World::World(Game *game)
{
    loadMapFromFile();
    this->game = game;

    // FIXME: Just for debugging!!!
    // FIXME: =====================
    Item item = Item(SPRITE_ITEM_WOOD, 888, sf::Vector2f({600.f, 800.f}));
    items.push_back(item);
    item = Item(SPRITE_ITEM_WOOD, 222, sf::Vector2f({600.f, 900.f}));
    items.push_back(item);
    item = Item(SPRITE_ITEM_STONE, 30, sf::Vector2f({600.f, 1000.f}));
    items.push_back(item);
    item = Item(SPRITE_ITEM_STONE, 204, sf::Vector2f({640.f, 950.f}));
    items.push_back(item);

    intDistribution = std::uniform_int_distribution<int>(0, 1);
    widthDistribution = std::uniform_real_distribution<float>(0.f, float(INT_SCREEN_WIDTH * 2));
    heightDistribution = std::uniform_real_distribution<float>(0.f, float(INT_SCREEN_HEIGHT * 2));

    // FIXME: =====================
}
World::~World()
{
}

int *World::getWorld()
{
    return &(this->tilemap[0][0]);
}

void World::update(double deltaTime)
{
    // Updates projectiles.
    for (auto projectile = begin(projectiles); projectile != end(projectiles); ++projectile)
        if (projectile->update(deltaTime))
            projectiles.erase(projectile--);

    // Updates textParticles.
    for (auto particle = begin(textParticles); particle != end(textParticles); ++particle)
    {
        if (particle->update(deltaTime))
            textParticles.erase(particle--);
    }

    // Updates enemies.
    bool isEnemyNearby = false;
    for (auto enemy = begin(enemies); enemy != end(enemies); ++enemy)
    {
        enemy->update(deltaTime);

        // Searches for nearby enemies. Only targets enemies within 500 units of range.
        sf::Vector2f playerEnemyVector = game->getPlayer()->getPosition() + game->getCamera()->getOffset() - enemy->getPosition();
        if (!isEnemyNearby)
            isEnemyNearby = sqrt((playerEnemyVector.x * playerEnemyVector.x) + (playerEnemyVector.y * playerEnemyVector.y)) < INT_SCREEN_WIDTH / 2;
    };

    // Creates new projectiles.
    if (projectileTimer > 0.05f && isEnemyNearby)
    {
        sf::Vector2f position = game->getPlayer()->getPosition() + game->getCamera()->getOffset();
        Projectile projectile({position.x + 25, position.y + 25}, sf::Vector2f(sf::Mouse::getPosition(*game->getWindow())) - sf::Vector2f(position.x + 25, position.y + 25) + sf::Vector2f(FLOAT_TILESCALE * game->getCamera()->getOffset().x, FLOAT_TILESCALE * game->getCamera()->getOffset().y), game);
        projectiles.push_back(projectile);
        projectileTimer = 0.f;
    }
    else
    {
        projectileTimer += deltaTime;
    }

    // Spawns new enemies
    if (enemyTimer > 3.f && enemies.size() < INT_ENTITY_LIMIT)
    {
        for (int i = 0; i < 50; i++)
        {
            Enemy enemy({widthDistribution(game->gen), heightDistribution(game->gen)}, game);
            enemies.push_back(enemy);
        }
        enemyTimer = 0.f;
    }
    else
    {
        enemyTimer += deltaTime;
    }
}

void World::draw(double timeFromStart)
{
    // Draws map. Variables below make sure only visible tiles are rendered.
    int lowXrange = clampInt(game->getCamera()->getOffset().x / (16 * FLOAT_TILESCALE / 2), 0, INT_WORLDSIZE);
    int maxXrange = clampInt((game->getCamera()->getOffset().x + INT_SCREEN_WIDTH / 2) / (16 * FLOAT_TILESCALE / 2), 0, INT_WORLDSIZE);
    int lowYrange = clampInt(game->getCamera()->getOffset().y / (16 * FLOAT_TILESCALE / 2), 0, INT_WORLDSIZE);
    int maxYrange = clampInt((game->getCamera()->getOffset().y + INT_SCREEN_HEIGHT / 2) / (16 * FLOAT_TILESCALE / 2), 0, INT_WORLDSIZE);

    for (int x = max(lowXrange - 1, 0); x < min(maxXrange + 1, INT_WORLDSIZE); x++)
        for (int y = max(lowYrange - 1, 0); y < min(maxYrange + 1, INT_WORLDSIZE); y++)
            if (tilemap[x][y] != 0)
                game->drawSprite(x * 16 * FLOAT_TILESCALE, y * 16 * FLOAT_TILESCALE, tilemap[x][y], FLOAT_TILESCALE);

    // Draws items on ground.
    for (auto item = begin(items); item != end(items); ++item)
    {
        float distanceFromPlayer = pow(item->getPosition().x - game->getCamera()->getOffset().x - game->getPlayer()->getPosition().x, 2) + pow(item->getPosition().y - game->getCamera()->getOffset().y - game->getPlayer()->getPosition().y, 2);

        // Draws text when player is near the item (is closer than 200 pixels (200^2 = 40000)).
        if (distanceFromPlayer < 40000)
        {
            // For optimisation reasons item pickups are done here (I didnt want to make two vector loops - one in update and one in draw)
            if (distanceFromPlayer < 4000)
            {
                // TODO: Item merging.
                game->getHud()->addToEventLog("Picked up " + std::to_string(item->getAmount()) + "x " + itemNames.at(item->getSprite()) + ".");
                items.erase(item--);
                continue;
            }
            else
                game->drawText(item->getPosition().x - FLOAT_TILESCALE * game->getCamera()->getOffset().x, item->getPosition().y - FLOAT_TILESCALE * game->getCamera()->getOffset().y - 20, std::to_string(item->getAmount()) + "x " + itemNames.at(item->getSprite()), DEFAULT_FONT_BOLD, 16, true); // FIXME: Add item name description.
        }
        game->drawSprite(item->getPosition().x, item->getPosition().y + 2 * (sin(3 * timeFromStart) - 1), item->getSprite(), FLOAT_TILESCALE, false, true, true, false);
    }

    // Draws enemies.
    for (auto enemy = begin(enemies); enemy != end(enemies); ++enemy)
    {
        enemy->draw();
    }

    // Draws projectiles.
    for (auto projectile = begin(projectiles); projectile != end(projectiles); ++projectile)
    {
        projectile->draw();
    }

    // Draws textParticles.
    for (auto particle = begin(textParticles); particle != end(textParticles); ++particle)
    {
        particle->draw();
    }
}

// Loads map from file.
int World::loadMapFromFile()
{

    std::string text;
    std::ifstream file("levels/map.csv");

    // Check if file exists.
    if (file.fail())
    {
        return -1;
    }

    // Loops through all lines of the file.
    int x = 0, y = 0;

    while (getline(file, text))
    {
        std::string currentId = "";

        // Ignores blank lines and comments starting with '#' symbol.
        if (text[0] != '#' && text != "")

            for (int i = 0; i < text.size(); i++)
            {

                // Exits app when map file is corrupted.
                // TODO: Add error message.
                if (y >= INT_WORLDSIZE || x >= INT_WORLDSIZE)
                    exit(-1);

                // Checks if character is not a ',' (is a number). If yes, adds it to temporary variable.
                if (text[i] != ',')
                    currentId = currentId + text[i];

                // Checks if character is a ',' or if character is the last one in line. Then checks if currentId is not empty.
                if (text[i] == ',' || i == text.size() - 1)
                    if (currentId.size() > 0)
                    {

                        tilemap[x][y] = std::stoi(currentId);
                        currentId = "";
                        y++;
                    }
            }
        x++;
        y = 0;
    }
    file.close();

    return 0;
}