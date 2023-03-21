#include <iostream>
#include <SFML/Graphics.hpp>

#include "include/Hud.h"
#include "include/Game.h"
#include "include/Sprites.h"
#include "include/Inventory.h"

Hud::Hud(Game *game)
{
    this->game = game;
}

Hud::~Hud()
{
}

void Hud::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        game->getPlayer()->getInventory()->setCurrentSlot(0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        game->getPlayer()->getInventory()->setCurrentSlot(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        game->getPlayer()->getInventory()->setCurrentSlot(2);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        game->getPlayer()->getInventory()->setCurrentSlot(3);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        game->getPlayer()->getInventory()->setCurrentSlot(4);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        game->getPlayer()->getInventory()->setCurrentSlot(5);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        game->getPlayer()->getInventory()->setCurrentSlot(6);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        game->getPlayer()->getInventory()->setCurrentSlot(7);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        game->getPlayer()->getInventory()->setCurrentSlot(8);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        game->getPlayer()->getInventory()->setCurrentSlot(9);
}

void Hud::draw(double deltaTime)
{
    drawDebugInfo();
    drawEventLog(deltaTime);
    drawItemHotbar();
}

void Hud::drawItemHotbar()
{

    game->drawSprite(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT - 16 - 21 * 2, SPRITE_HOTBAR, 2.f, false, false, true, false);
    game->drawSprite(INT_SCREEN_WIDTH / 2 + 2.f * 21 * (game->getPlayer()->getInventory()->getCurrentSlot() - 5), INT_SCREEN_HEIGHT - 16 - 21 * 2, SPRITE_HOTBAR_ACTIVE, 2.f, false, false, false, false);
    int i = 0;
    std::vector<InventoryItem> items = game->getPlayer()->getInventory()->getItems();
    for (auto item = begin(items); item != end(items); ++item)
    {
        if (i > 9)
            break;
        if (item->getSpriteId() > 0)
        {
            float x = INT_SCREEN_WIDTH / 2 + 2.f * 21 * (i - 5) + 10 * 2.f;
            float y = INT_SCREEN_HEIGHT - 16 - 21 * 2 + 10 * 2.f;
            game->drawSprite(x, y, item->getSpriteId(), 2.f, false, false, true, true);
            game->drawText(x, y + 12 * 2.f, std::to_string(item->getAmount()), DEFAULT_FONT, 8, true);
        }
        i++;
    }
}

void Hud::drawDebugInfo()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        game->drawText(16, 16, "playerpos=" + std::to_string(game->getPlayer()->getPosition().x) + "," + std::to_string(game->getPlayer()->getPosition().y), DEFAULT_FONT, 8);
        game->drawText(16, 16 + (8 + 4) * 1, "camerapos=" + std::to_string(game->getCamera()->getPosition().x) + "," + std::to_string(game->getCamera()->getPosition().y), DEFAULT_FONT, 8);
        game->drawText(16, 16 + (8 + 4) * 2, "cameraoffset=" + std::to_string(game->getCamera()->getOffset().x) + "," + std::to_string(game->getCamera()->getOffset().y), DEFAULT_FONT, 8);
    }
}

void Hud::drawEventLog(double deltaTime)
{
    int count = 0;
    for (auto event = begin(eventLog); event != end(eventLog); ++event)
        if (event->first < 5 && count < 10)
        {
            game->drawText(16, INT_SCREEN_HEIGHT - 32 - count * 20, event->second, DEFAULT_FONT, 16);
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