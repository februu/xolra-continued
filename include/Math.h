#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

inline float clamp(float value, float min, float max)
{
    if (value > min)
        if (value < max)
            return value;
        else
            return max;
    else
        return min;
}

inline int clampInt(float value, float min, float max)
{
    if (value > min)
        if (value < max)
            return int(value);
        else
            return int(max);
    else
        return int(min);
}

inline int max(int x, int y)
{

    if (x >= y)
        return x;
    else
        return y;
}

inline int min(int x, int y)
{

    if (x <= y)
        return x;
    else
        return y;
}

inline sf::Vector2f normalize(const sf::Vector2f &source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}