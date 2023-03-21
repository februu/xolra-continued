#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

class Player;

class Camera
{
private:
    sf::Vector2f position;
    float zoom = 1.f;
    Player *player;

public:
    Camera(Player *player);
    virtual ~Camera();

    void update(double deltaTime);
    float getZoom();
    sf::Vector2f getPosition();
    sf::Vector2f getOffset();
};
