#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "include/Constants.h"
#include "include/Game.h"
#include "include/Player.h"
#include "include/World.h"
#include "include/Hud.h"
#include "include/Camera.h"
#include "include/AssetManager.h"
#include "include/Sprites.h"

#include "libs/include/discord/discord.h"

using std::cout;

Game::Game()
{
    // Creates window.
    this->createWindow();

    // Initializes random number generator.
    std::random_device rd;
    gen = std::mt19937(rd());

    // Initializes Discord core.
    // TODO: Change discord client token.
    auto result = discord::Core::Create(1092102719805853746, DiscordCreateFlags_Default, &core);
    discord::Activity activity{};
    activity.SetState("febru.me");
    activity.SetDetails("Coding & Testing...");
    activity.GetAssets().SetLargeImage("logo");
    activity.GetAssets().SetLargeText("Xolra");
    activity.GetTimestamps().SetStart(discord::Timestamp(std::time(0)));
    core->ActivityManager()
        .UpdateActivity(activity, [](discord::Result result) {});
}

Game::~Game()
{
    delete window;
}

void Game::handleEvents()
{
    while (window->pollEvent(sfEvent))
    {
        // Handle windows events like closing, moving or alt+tabbing.
        if (sfEvent.type == sf::Event::Closed)
            window->close();
    }
}

void Game::update()
{
    // Updates delta time.
    deltaTime = clock.restart().asSeconds();
    timeFromStart += deltaTime;

    // Updates the game.
    hud.update();
    world.update(deltaTime);
    camera.update(deltaTime);
    player.update(deltaTime);
    pet.update(deltaTime);
}

void Game::draw()
{
    window->clear(sf::Color(27, 27, 27, 255));

    // RENDERING
    world.draw(timeFromStart);
    player.draw();
    pet.draw();
    hud.draw(deltaTime);

    // Draws cursor.
    drawSprite(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y, SPRITE_CURSOR, 1.f, false, false);
    window->display();
}

// Game loop.
void Game::run()
{
    while (window->isOpen())
    {
        if (gameState == 2)
        {
            handleEvents();
            update();
            draw();
        }
        else if (gameState == 0)
        {
            handleEvents();
            drawSplashScreen();
        }

        // Runs Discord Callbacks.
        core->RunCallbacks();
    }
}

// ================= Game Functions =================

void Game::createWindow()
{
    // if (fullscreenMode)
    //  window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "XXX", sf::Style::Fullscreen);
    // else
    window = new sf::RenderWindow(sf::VideoMode(INT_SCREEN_WIDTH, INT_SCREEN_HEIGHT), "Xolra", sf::Style::Fullscreen);
    window->setMouseCursorVisible(false);
    window->setFramerateLimit(300);
    // sf::Image icon = sf::Image();
    // icon.loadFromFile("assets/icon.png");
    // window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Draws Splash Screen
void Game::drawSplashScreen()
{
    // Skips splashscreen.
    if (!BOOL_ENABLE_SPLASHSCREEN)
        gameState = 2;

    // Checks duration.
    if (timeFromStart > 9)
    {
        gameState = 2;
        return;
    }

    window->clear(sf::Color(34, 32, 34, 255));
    if (timeFromStart > 1)
    {
        if (timeFromStart < 2)
            drawText(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT / 2, "made by @febru", DEFAULT_FONT_BOLD, 32, true, false, sf::Color(255, 255, 255, int(255 * (timeFromStart - 1))));
        else if (timeFromStart < 3)
            drawText(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT / 2, "made by @febru", DEFAULT_FONT_BOLD, 32, true, false, sf::Color(255, 255, 255, 255));
        else if (timeFromStart < 4)
            drawText(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT / 2, "made by @febru", DEFAULT_FONT_BOLD, 32, true, false, sf::Color(255, 255, 255, int(255 - (255 * (timeFromStart - 3)))));
        if (timeFromStart > 5)
            drawSprite(INT_SCREEN_WIDTH / 2, INT_SCREEN_HEIGHT / 2, SPRITE_LOGO, 2.f, false, false, true, true);
    }

    window->display();
    timeFromStart += clock.restart().asSeconds();
}

void Game::drawSprite(float x, float y, int id, float scale, bool flipped, bool cameraOffset, bool centeredX, bool centeredY, float xCropFactor)
{
    sf::Sprite sprite = *am.getSprite(id);
    sprite.setScale(scale, scale);
    if (cameraOffset)
    {
        x -= scale * camera.getOffset().x;
        y -= scale * camera.getOffset().y;
    }
    if (centeredX)
        x -= scale * sprite.getTexture()->getSize().x / 2;
    if (centeredY)
        y -= scale * sprite.getTexture()->getSize().y / 2;
    if (xCropFactor > 0)
    {
        sf::IntRect textureRect(0, 0, int(sprite.getTexture()->getSize().x * xCropFactor), sprite.getTexture()->getSize().y);
        sprite.setTextureRect(textureRect);
    }
    sprite.setPosition(x, y);
    window->draw(sprite);
}

void Game::drawText(float x, float y, std::string content, int fontId, float scale, bool centered, bool shadow, sf::Color color)
{
    sf::Text text(content, *am.getFont(fontId));
    text.setCharacterSize(scale);
    if (centered)
    {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top);
    }
    if (shadow)
    {
        text.setPosition(sf::Vector2f(x + 2.f, y + 2.f));
        text.setFillColor(sf::Color(0, 0, 0));
        window->draw(text);
    }
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(color);
    window->draw(text);
}

Hud *Game::getHud()
{
    return &hud;
}

Camera *Game::getCamera()
{
    return &camera;
}

Player *Game::getPlayer()
{
    return &player;
}

World *Game::getWorld()
{
    return &world;
}

sf::RenderWindow *Game::getWindow()
{
    return window;
}