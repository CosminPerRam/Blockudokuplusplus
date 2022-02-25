
#include "game.h"

#include <SFML/Graphics/RenderWindow.hpp>

void Game::draw(sf::RenderWindow& window) {
    theTable.draw(window);
}

void Game::pollEvent(sf::Event &theEvent) {

}

void Game::start() {
    sf::RenderWindow window(sf::VideoMode(340, 600), "Blockudoku");

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            this->pollEvent(event);
        }

        window.clear(sf::Color(255, 255, 255));
        this->draw(window);
        window.display();
    }
}