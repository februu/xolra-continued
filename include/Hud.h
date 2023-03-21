#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Game;

class Hud
{
private:
    Game *game;
    std::vector<std::pair<double, std::string>> eventLog;

    void drawDebugInfo();
    void drawEventLog(double deltaTime);
    void drawItemHotbar();

public:
    Hud(Game *game);
    virtual ~Hud();

    // Functions
    void update();
    void draw(double deltaTime);
    void addToEventLog(std::string event);
};
