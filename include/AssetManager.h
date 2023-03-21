#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class AssetManager
{
private:
    sf::Texture txt;
    std::map<int, sf::Texture> textures;
    std::map<int, sf::Sprite> sprites;
    std::map<int, sf::Font> fonts;

public:
    AssetManager();
    virtual ~AssetManager();

    // Functions
    void addSprite(std::string path, int spriteInt, bool full = true, std::string variant = "", int x = 0, int y = 0, int width = 0, int height = 0);
    void addParticleTexture();
    sf::Sprite *getSprite(int id);
    sf::Font *getFont(int id);
};
