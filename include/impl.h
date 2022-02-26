#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Drawable
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};

class Eventer
{
public:
	virtual void pollEvent(sf::RenderWindow& window, sf::Event& theEvent) = 0;
};