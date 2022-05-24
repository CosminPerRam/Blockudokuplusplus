
#include "game.h"
#include "spacing.h"
#include "audio.h"

#include <SFML/Graphics/RenderWindow.hpp>

Score *Game::theScore = new Score(Block::getAllStructuresCount());
Table *Game::theTable = new Table(*theScore);
PickupBoard *Game::pickupBoard = new PickupBoard(*theTable, *theScore);
ImguiInterface* Game::imguiInterface = new ImguiInterface();

sf::Clock Game::deltaClock;

void Game::restart() {
    delete theScore;    //restarting the game just deletes the pointers
    delete theTable;    //and re-initializes them, this is easier to do
    delete pickupBoard; //but not that intuitive

    theScore = new Score(Block::getAllStructuresCount());
    theTable = new Table(*theScore);
    pickupBoard = new PickupBoard(*theTable, *theScore);
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
}

int Game::start() {
    Audio::initialize();

    Settings::load("test.txt");

    Game::theTable->updateColors();
    Game::theScore->updateColors();
    Game::pickupBoard->updateColors();

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