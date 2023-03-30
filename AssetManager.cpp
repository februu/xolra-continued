#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "include\AssetManager.h"
#include "include\Sprites.h"

AssetManager::AssetManager()
{
    // Loads hud sprites.
    // addSprite("bg", true);

    addSprite("bat", SPRITE_PET, true);
    addSprite("eqhotbar", SPRITE_HOTBAR, true);
    addSprite("eqhotbar_active", SPRITE_HOTBAR_ACTIVE, true);
    addSprite("wood", SPRITE_ITEM_WOOD, true);
    addSprite("stone", SPRITE_ITEM_STONE, true);
    addSprite("cursor", SPRITE_CURSOR, true);
    addSprite("logo", SPRITE_LOGO, true);

    // Loads tile sprites.
    addSprite("tile", SPRITE_TILE_PLAIN, false, "", 0, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_GRASS, false, "grass", 16, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_GRASS2, false, "grass2", 32, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_MARK, false, "mark", 48, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_MARK2, false, "mark2", 64, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_POND, false, "pond", 80, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_LAND, false, "land", 96, 0, 16, 16);
    addSprite("tile", SPRITE_TILE_ROCKS, false, "rocks", 112, 0, 16, 16);

    // Loads all fonts.
    sf::Font font;
    font.loadFromFile("res/fonts/abaddon.ttf");
    this->fonts.insert({DEFAULT_FONT, font});
    font.loadFromFile("res/fonts/abaddon-bold.ttf");
    this->fonts.insert({DEFAULT_FONT_BOLD, font});

    // TODO: Load sounds.
}

AssetManager::~AssetManager()
{
}

void AssetManager::addSprite(std::string path, int spriteInt, bool full, std::string variant, int x, int y, int width, int height)
{
    sf::Texture texture;
    if (!full)
        texture.loadFromFile("res/textures/" + path + ".png", sf::IntRect(x, y, width, height));
    else
        texture.loadFromFile("res/textures/" + path + ".png");
    this->textures.insert({spriteInt, texture});
    sf::Sprite sprite;
    sprite.setTexture(textures.at(spriteInt));
    this->sprites.insert({spriteInt, sprite});
}

sf::Sprite *AssetManager::getSprite(int id)
{
    return &this->sprites[id];
}

sf::Font *AssetManager::getFont(int fontName)
{
    return &this->fonts[fontName];
}
