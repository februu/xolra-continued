#include <SFML/Graphics.hpp>

#include "include/Item.h"
#include "include/Sprites.h"

Item::Item(int spriteId, int amount, sf::Vector2f position)
{
    this->spriteId = spriteId;
    this->amount = amount;
    this->position = position;
}

Item::~Item()
{
}

void Item::update(double deltaTime)
{
}

int Item::getAmount()
{
    return amount;
}
int Item::getSprite()
{
    return spriteId;
}
sf::Vector2f Item::getPosition()
{
    return position;
}
void Item::setPosition(sf::Vector2f position)
{
    this->position = position;
}