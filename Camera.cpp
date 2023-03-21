#include <SFML/Graphics.hpp>
#include "include/Constants.h"
#include "include/Math.h"
#include "include/Camera.h"
#include "include/Player.h"

Camera::Camera(Player *player)
{
    this->player = player;
    position.x = player->getPosition().x;
    position.y = player->getPosition().y;
}
Camera::~Camera()
{
}

void Camera::update(double deltaTime)
{
    float x = (player->getPosition().x - position.x) / FLOAT_MAX_CAMERA_VELOCITY;
    float y = (player->getPosition().y - position.y) / FLOAT_MAX_CAMERA_VELOCITY;
    position.x = clamp(position.x + x * deltaTime * 100, INT_SCREEN_WIDTH / 2, 1600); // FIXME! Change 1600 to more flexible value.
    position.y = clamp(position.y + y * deltaTime * 100, INT_SCREEN_HEIGHT / 2, 1600);
}

float Camera::getZoom()
{
    return zoom;
}

sf::Vector2f Camera::getPosition()
{
    return position;
}

sf::Vector2f Camera::getOffset()
{

    return sf::Vector2f(position.x - (INT_SCREEN_WIDTH / 2), position.y - (INT_SCREEN_HEIGHT / 2));
}
