#pragma once

#include <map>

enum SpriteIds
{
    SPRITE_TILE_PLAIN = 0,
    SPRITE_TILE_GRASS = 1,
    SPRITE_TILE_GRASS2 = 2,
    SPRITE_TILE_MARK = 3,
    SPRITE_TILE_MARK2 = 4,
    SPRITE_TILE_POND = 5,
    SPRITE_TILE_LAND = 6,
    SPRITE_TILE_ROCKS = 7,
    SPRITE_ITEM_WOOD = 100,
    SPRITE_ITEM_STONE = 101,
    SPRITE_HUD_ARROW = 8000,
    SPRITE_HUD_BAR = 8001,
    SPRITE_HUD_HEART = 8002,
    SPRITE_HUD_LUCK = 8003,
    SPRITE_HUD_PAUSE = 8004,
    SPRITE_HUD_POTION = 8005,
    SPRITE_HUD_SHIELD = 8006,
    SPRITE_HUD_SLOT = 8007,
    SPRITE_HUD_SWORD = 8008,
    SPRITE_PET = 9000,
    SPRITE_CURSOR = 9999,
    SPRITE_LOGO = 9996
};

enum FontIds
{
    DEFAULT_FONT = 99999,
    DEFAULT_FONT_BOLD = 99998
};

const std::map<int, std::string> itemNames = {std::make_pair(SPRITE_ITEM_WOOD, "Wood"),
                                              std::make_pair(SPRITE_ITEM_STONE, "Stone")};