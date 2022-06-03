#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <vector>

#define FILENAME_LENGTH 64
#define IMGUI_REFRESHRATE 60

class ImguiInterface
{
private:
	static char fileName[FILENAME_LENGTH];

	static ImGuiWindowFlags window_flags;
	static ImGuiStyle* style;

	static sf::Time lastTime, lastUpdateTime;
	static bool updateFrame;

	struct Custom
	{
		static void HelpMarker(const char* desc);
	};

	struct Data
	{
		std::vector<float> historyFps;
		unsigned averageFps = 0;

		static void update();
	} static data;

public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time& dt);
};