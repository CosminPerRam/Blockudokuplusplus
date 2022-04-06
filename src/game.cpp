
#include "game.h"
#include "spacing.h"
#include "audio.h"

#include <SFML/Graphics/RenderWindow.hpp>

Score *Game::theScore = new Score(Block::getAllStructuresCount());
Table *Game::theTable = new Table(*theScore);
PickupBoard *Game::pickupBoard = new PickupBoard(*theTable, *theScore);

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
}

void Game::pollEvent(sf::RenderWindow& window, sf::Event &theEvent) {
    theScore->pollEvent(window, theEvent);

    if (!theScore->isGameLost()) { //if the game is not lost, poll everything
        Audio::pollEvent(window, theEvent);
        pickupBoard->pollEvent(window, theEvent);
    }
}

int Game::start() {
    Audio::initialize();

    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Blockudoku", sf::Style::Close);

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {   //while the window is open, the game processes and renders stuff
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            pollEvent(window, event);
        }

        window.clear(sf::Color(255, 255, 255));
        draw(window); //draws everything
        window.display();
    }

    return 0;
}