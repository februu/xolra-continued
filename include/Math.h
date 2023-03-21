#pragma once

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