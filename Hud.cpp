#include <iostream>
#include <SFML/Graphics.hpp>

#include "include/Hud.h"
#include "include/Game.h"
#include "include/Sprites.h"

Hud::Hud(Game *game)
{
    this->game = game;
}

Hud::~Hud()
{
}

void Hud::update()
{
}

void Hud::draw(double deltaTime)
{
    drawDebugInfo();
    drawEventLog(deltaTime);
}

void Hud::drawDebugInfo()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        game->drawText(16, 16, "playerpos=" + std::to_string(game->getPlayer()->getPosition().x) + "," + std::to_string(game->getPlayer()->getPosition().y), DEFAULT_FONT_BOLD, 16);
        game->drawText(16, 32 + (8 + 4) * 1, "camerapos=" + std::to_string(game->getCamera()->getPosition().x) + "," + std::to_string(game->getCamera()->getPosition().y), DEFAULT_FONT_BOLD, 16);
        game->drawText(16, 48 + (8 + 4) * 2, "cameraoffset=" + std::to_string(game->getCamera()->getOffset().x) + "," + std::to_string(game->getCamera()->getOffset().y), DEFAULT_FONT_BOLD, 16);
    }
}

void Hud::drawEventLog(double deltaTime)
{
    int count = 0;
    for (auto event = begin(eventLog); event != end(eventLog); ++event)
        if (event->first < 5 && count < 10)
        {
            game->drawText(16, INT_SCREEN_HEIGHT - 32 - count * 20, event->second, DEFAULT_FONT_BOLD, 20);
            event->first = event->first + deltaTime;
            count++;
        }
        else
            eventLog.erase(event--);
}

void Hud::addToEventLog(std::string event)
{
    eventLog.insert(eventLog.begin(), std::make_pair(0, event));
}