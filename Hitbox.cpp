#include <SFML/Graphics.hpp>
#include <cmath>
#include "include/Hitbox.h"

void HitBox::updatePosition(sf::Vector2f position)
{
    this->position = position;
}

bool HitBox::checkIfCollides(HitBox &hitbox)
{
    return this->position.x<hitbox.position.x + hitbox.size.x &&this->position.x + this->size.x> hitbox.position.x && this->position.y<hitbox.position.y + hitbox.size.y &&this->position.y + this->size.y> hitbox.position.y;
}
