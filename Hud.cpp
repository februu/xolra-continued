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
    drawGameHud(deltaTime);
    drawStats();
    drawEventLog(deltaTime);
    drawDebugInfo();
}

void Hud::drawDebugInfo()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        game->drawText(16, 16, "playerpos=" + std::to_string(game->getPlayer()->getPosition().x) + "," + std::to_string(game->getPlayer()->getPosition().y), DEFAULT_FONT_BOLD, 16);
        game->drawText(16, 32 + (8 + 4) * 1, "camerapos=" + std::to_string(game->getCamera()->getPosition().x) + "," + std::to_string(game->getCamera()->getPosition().y), DEFAULT_FONT_BOLD, 16);
        game->drawText(16, 48 + (8 + 4) * 2, "cameraoffset=" + std::to_string(game->getCamera()->getOffset().x) + "," + std::to_string(game->getCamera()->getOffset().y), DEFAULT_FONT_BOLD, 16);
        game->drawText(16, 64 + (8 + 4) * 2, "mousepos=" + std::to_string(sf::Mouse::getPosition(*game->getWindow()).x) + "," + std::to_string(sf::Mouse::getPosition(*game->getWindow()).y), DEFAULT_FONT_BOLD, 16);
    }
}

void Hud::drawEventLog(double deltaTime)
{
    int count = 0;
    for (auto event = begin(eventLog); event != end(eventLog); ++event)
        if (event->first < 5 && count < 10)
        {
            game->drawText(16, INT_SCREEN_HEIGHT - 32 - count * 16, event->second, DEFAULT_FONT_BOLD, 16);
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

void Hud::drawGameHud(double deltaTime)
{
    // game->drawSprite(INT_SCREEN_WIDTH - 16 * (INT_HUDSCALE * 2 + 1), 16, SPRITE_HUD_PAUSE, INT_HUDSCALE * 2, false, false);
    game->drawText(16, 16, "fps=" + std::to_string(1.f / deltaTime), DEFAULT_FONT_BOLD, 16);
    game->drawSprite(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT - 16 * INT_HUDSCALE * 2, SPRITE_HUD_PROGRESS, INT_HUDSCALE, false, false, true, false, 0.5);
    game->drawSprite(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT - 16 * INT_HUDSCALE * 2, SPRITE_HUD_BAR, INT_HUDSCALE, false, false, true);
    game->drawSprite(INT_SCREEN_WIDTH / 2 + 64 * INT_HUDSCALE + 4 * INT_HUDSCALE, INT_SCREEN_HEIGHT - 16 * INT_HUDSCALE * 2, SPRITE_HUD_SLOT, INT_HUDSCALE, false, false);
    for (int i = 0; i < 5; i++) // FIXME
        if (i < 3)
            game->drawSprite(INT_SCREEN_WIDTH / 2 - 64 * INT_HUDSCALE + i * (12 * INT_HUDSCALE), INT_SCREEN_HEIGHT - 16 * INT_HUDSCALE * 2 - 12 * INT_HUDSCALE, SPRITE_HUD_HEART, INT_HUDSCALE, false, false);
        else
            game->drawSprite(INT_SCREEN_WIDTH / 2 - 64 * INT_HUDSCALE + i * (12 * INT_HUDSCALE), INT_SCREEN_HEIGHT - 16 * INT_HUDSCALE * 2 - 12 * INT_HUDSCALE, SPRITE_HUD_EMPTY_HEART, INT_HUDSCALE, false, false);
}

void Hud::drawStats()
{
    game->drawSprite(32, INT_SCREEN_HEIGHT / 20 * 8, SPRITE_HUD_SWORD, 2, false, false, true, true);
    game->drawSprite(32, INT_SCREEN_HEIGHT / 20 * 9, SPRITE_HUD_SHIELD, 2, false, false, true, true);
    game->drawSprite(32, INT_SCREEN_HEIGHT / 20 * 10, SPRITE_HUD_POTION, 2, false, false, true, true);
    game->drawSprite(32, INT_SCREEN_HEIGHT / 20 * 11, SPRITE_HUD_ARROW, 2, false, false, true, true);
    game->drawSprite(32, INT_SCREEN_HEIGHT / 20 * 12, SPRITE_HUD_LUCK, 2, false, false, true, true);

    game->drawText(64, INT_SCREEN_HEIGHT / 20 * 8 - 12, "0.00", DEFAULT_FONT, 16);
    game->drawText(64, INT_SCREEN_HEIGHT / 20 * 9 - 12, "0.00", DEFAULT_FONT, 16);
    game->drawText(64, INT_SCREEN_HEIGHT / 20 * 10 - 12, "0.00", DEFAULT_FONT, 16);
    game->drawText(64, INT_SCREEN_HEIGHT / 20 * 11 - 12, "0.00", DEFAULT_FONT, 16);
    game->drawText(64, INT_SCREEN_HEIGHT / 20 * 12 - 12, "0.00", DEFAULT_FONT, 16);
}