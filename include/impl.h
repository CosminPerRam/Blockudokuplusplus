#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

/*
	These classes are simple templates declaring that a 
	component can be drawn or that it has polling processing
*/

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

class Updater
{
public:
	virtual void update(sf::RenderWindow& window, sf::Time& dt) = 0;
};

class Colored
{
public:
	virtual void updateColors() = 0;
};