
#include "game.h"

#include "spacing.h"

#include <SFML/Graphics/RenderWindow.hpp>

void Game::draw(sf::RenderWindow& window) {
    theScore.draw(window);

    if (!theScore.getGameState()) {
        theTable.draw(window);
        pickupBoard.draw(window);
    }
}

void Game::pollEvent(sf::RenderWindow& window, sf::Event &theEvent) {
    if(!theScore.getGameState())
        pickupBoard.pollEvent(window, theEvent);
}

void Game::start() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Blockudoku");

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