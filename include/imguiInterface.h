#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "impl.h"

class ImguiInterface// : Drawable, Eventer
{
public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time dt);
};