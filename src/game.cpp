
#include "game.h"
#include "spacing.h"
#include "audio.h"

#include <SFML/Graphics/RenderWindow.hpp>

Score *Game::theScore = nullptr;
Table *Game::theTable = nullptr;
PickupBoard *Game::pickupBoard = nullptr;
ImguiInterface *Game::imguiInterface = nullptr;
Bot Game::theBot;

sf::Clock Game::deltaClock;

void Game::restart() {
    theScore->reset(true);
    theTable->reset();
    pickupBoard->reset();
}

void Game::draw(sf::RenderWindow& window) {
    theScore->draw(window);

    if (!theScore->isGameLost()) { //if the game is not lost, draw everything
        theTable->draw(window);
        Audio::draw(window);
        pickupBoard->draw(window);
    }

    ImguiInterface::draw(window);
}

void Game::pollEvent(sf::RenderWindow& window, sf::Event &theEvent) {
    ImguiInterface::pollEvent(window, theEvent);

    theScore->pollEvent(window, theEvent);

    if (!theScore->isGameLost()) { //if the game is not lost, poll everything
        Audio::pollEvent(window, theEvent);
        pickupBoard->pollEvent(window, theEvent);
    }
}

void Game::update(sf::RenderWindow& window) {
    sf::Time dt = deltaClock.restart();

    ImguiInterface::update(window, dt);

    if (!theScore->isGameLost()) {
        if (Settings::Gameplay::autoplay)
            theBot.update(window, dt);
    }
}

int Game::start() {
    Audio::initialize();

    Settings::defaults();

    theScore = new Score(structures::grouped.size());
    theTable = new Table(*theScore);
    pickupBoard = new PickupBoard(*theTable, *theScore);

    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Blockudoku", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    ImguiInterface::initialize(window);

    while (window.isOpen())
    {   //while the window is open, the game processes and renders stuff
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            Game::pollEvent(window, event);
        }

        Game::update(window);

        window.clear(toColor(Settings::Aspect::appBackground));
        draw(window); //draws everything
        window.display();
    }

    ImguiInterface::shutdown();
    return 0;
}