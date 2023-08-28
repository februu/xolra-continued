#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "AssetManager.h"
#include "Player.h"
#include "Hud.h"
#include "Pet.h"
#include "Camera.h"
#include "World.h"
#include "../libs/include/discord/discord.h"

class Game
{
private:
    // Const Variables & Enums
    sf::Clock clock;
    sf::Event sfEvent;
    AssetManager am;
    sf::RenderWindow *window;
    discord::Core *core{};

    // Gameplay Variables
    int gameState = 0;
    double deltaTime = 0;
    double timeFromStart = 0;
    Player player = Player(this);
    Pet pet = Pet(this);
    Camera camera = Camera(&player);
    World world = World(this);
    Hud hud = Hud(this);

    // Game Functions
    void createWindow();
    void drawSplashScreen();

public:
    Game();
    virtual ~Game();

    // Random Generator
    std::mt19937 gen;

    // Main Functions
    void handleEvents();
    void update();
    void draw();
    void run();

    // Public functions
    Hud *getHud();
    Camera *getCamera();
    Player *getPlayer();
    World *getWorld();
    sf::RenderWindow *getWindow();

    // Public draw functions
    void drawSprite(float x, float y, int id, float scale, bool flipped = false, bool cameraOffset = true, bool centeredX = false, bool centeredY = false, float xCropFactor = -1.f);
    void drawText(float x, float y, std::string content, int fontId, float scale, bool centered = false, bool shadow = true, sf::Color color = sf::Color(255, 255, 255, 255));
};
