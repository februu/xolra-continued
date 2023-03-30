#pragma once
#include <SFML/Graphics.hpp>

class HitBox
{
public:
    // FIXME: Create getters for variables listed below.
    sf::Vector2f position;
    sf::Vector2f size;

    HitBox() {}
    HitBox(sf::Vector2f position, sf::Vector2f size) : position(position), size(size) {}
    ~HitBox() {}
    void updatePosition(sf::Vector2f position);
    bool checkIfCollides(HitBox &hitbox);
};
