#pragma once
#include <SFML/Graphics.hpp>

class Item
{
private:
    int amount;
    int spriteId;
    sf::Vector2f position;

public:
    Item(int spriteId, int amount, sf::Vector2f position);
    virtual ~Item();

    // Functions
    void update(double deltaTime);
    int getAmount();
    int getSprite();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
};
