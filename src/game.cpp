
#include "game.h"
#include "spacing.h"
#include "audio.h"

#include <SFML/Graphics/RenderWindow.hpp>

Score *Game::theScore = new Score(Block::getAllStructuresCount());
Table *Game::theTable = new Table(*theScore);
PickupBoard *Game::pickupBoard = new PickupBoard(*theTable, *theScore);

Game::Game() {
    Audio::initialize();
}

void Game::restart() {
    delete theScore;
    delete theTable;
    delete pickupBoard;

    theScore = new Score(Block::getAllStructuresCount());
    theTable = new Table(*theScore);
    pickupBoard = new PickupBoard(*theTable, *theScore);
}

void Game::draw(sf::RenderWindow& window) {
    theScore->draw(window);

    if (!theScore->isGameLost()) {
        theTable->draw(window);
        pickupBoard->draw(window);
    }
}

void Game::pollEvent(sf::RenderWindow& window, sf::Event &theEvent) {
    theScore->pollEvent(window, theEvent);
    pickupBoard->pollEvent(window, theEvent);
}

void Game::start() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Blockudoku", sf::Style::Close);

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            this->pollEvent(window, event);
        }

        window.clear(sf::Color(255, 255, 255));
        this->draw(window);
        window.display();
    }
}