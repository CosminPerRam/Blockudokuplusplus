
#pragma once

#include <vector>

#include "imgui.h"
#include <SFML/Graphics/RenderWindow.hpp> 

#include "settings.h"

#define FILENAME_LENGTH 32
#define HISTORYFPS_COUNT 60

class ImguiInterface
{
private:
	inline static char fileName[FILENAME_LENGTH] = { SETTINGS_FILENAME_DEFAULT };

	inline static ImGuiWindowFlags window_flags = 0;
	static ImGuiStyle* style;

	static sf::Time lastTime, lastUpdateTime;

	struct Custom
	{
		static void HelpMarker(const char* desc);
	};

	struct Data
	{
		std::vector<float> historyFps = std::vector<float>(HISTORYFPS_COUNT, 0);
		unsigned averageFps = 0;

		float latestFrametime = 0.f;

		static void update();
	} static data;

public:
	static void initialize(sf::RenderWindow& window);
	static void shutdown();

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	static void update(sf::RenderWindow& window, sf::Time& dt);
};
