#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#define FILENAME_LENGTH 64

class ImguiInterface
{
private:
	static char fileName[FILENAME_LENGTH];

	static ImGuiWindowFlags window_flags;

	struct Custom
	{
		static void HelpMarker(const char* desc);
	};

public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time& dt);
};