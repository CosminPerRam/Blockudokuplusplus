
#include "game.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "spacing.h"
#include "audio.h"
#include "utilities.h"

Score *Game::theScore = nullptr;
Table *Game::theTable = nullptr;
PickupBoard *Game::pickupBoard = nullptr;

sf::Clock Game::deltaClock;
sf::Time Game::lastTime = Game::deltaClock.getElapsedTime();
sf::RenderWindow* Game::window = nullptr;

void Game::restart() {
    theScore->reset(true);
    theTable->reset();
    pickupBoard->reset();
}

void Game::draw() {
    theScore->draw(*window);

    if (!theScore->isGameLost()) { //if the game is not lost, draw everything
        theTable->draw(*window);
        Audio::draw(*window);
        pickupBoard->draw(*window);
    }

    ImguiInterface::draw(*window);
}

void Game::pollEvent(sf::Event &theEvent) {
    ImguiInterface::pollEvent(*window, theEvent);

    theScore->pollEvent(*window, theEvent);

    if (!theScore->isGameLost()) { //if the game is not lost, poll everything
        Audio::pollEvent(*window, theEvent);
        pickupBoard->pollEvent(*window, theEvent);
    }
}

void Game::update() {
    sf::Time dt = deltaClock.getElapsedTime();

    theScore->update(*window, dt);
    ImguiInterface::update(*window, dt);

    if (Settings::Gameplay::autoplay)
        theBot.update(*window, dt);

    pickupBoard->update(*window, dt);

    latestFrameTimeMs = (dt.asSeconds() - lastTime.asSeconds()) * 1000;
    latestFps = unsigned(1000 / latestFrameTimeMs);

    lastTime = dt;
}

unsigned Game::fetchFps() {
    return latestFps;
}

float Game::fetchFrametime() {
    return latestFrameTimeMs;
}

void Game::updateVsyncSetting() {
    window->setVerticalSyncEnabled(Settings::General::vsync);
}

void Game::updateAntialiasingSetting() {
    reinitializeWindow = true;
}

void Game::destroyWindow() {
    ImguiInterface::shutdown();
    window->close();
    delete window;
}

void Game::initializeWindow() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = Settings::General::aalevel == 0 ? 0 : Math::pow(2u, Settings::General::aalevel);

    window = new sf::RenderWindow(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Blockudoku", sf::Style::Close, settings);

    ImguiInterface::initialize(*window);

    Game::updateVsyncSetting();
}

void Game::free() {
    delete theScore;
    delete theTable;
    delete pickupBoard;
}

int Game::start() {
    Audio::initialize();

    theScore = new Score(structures::grouped.size());
    theTable = new Table();
    pickupBoard = new PickupBoard();

    Game::initializeWindow();

    if (Settings::load(SETTINGS_FILENAME_DEFAULT) != 1)
        Settings::defaults();

    while (window->isOpen())
    {   //while the window is open, the game processes and renders stuff
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                Game::destroyWindow();
                Game::free();
                return 1;
            }

            Game::pollEvent(event);
        }

        Game::update();

        window->clear(toColor(Settings::Aspect::appBackground));
        Game::draw(); //draws everything
        window->display();

        if (reinitializeWindow) {
            Game::destroyWindow();
            Game::initializeWindow();
            reinitializeWindow = false;
        }
    }

    Game::free();

    return 0;
}
