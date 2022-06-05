
#pragma once

#include <vector>
#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "table.h"
#include "pickupBoard.h"
#include "score.h"
#include "block.h"
#include "imguiInterface.h"
#include "bot.h"

/*
	Like the Audio class, this is a static class as its not possible
	to have multiple instances of the game running at the same time.
*/
class Game
{
private:
	static sf::Clock deltaClock;
	static sf::Time lastTime;
	static sf::RenderWindow* window;
	static unsigned latestFps;
	static float latestFrameTimeMs;

	static bool reinitializeWindow;

	static void draw();
	static void pollEvent(sf::Event& theEvent);
	static void update();

protected:
	static std::unique_ptr<Score> theScore;
	static std::unique_ptr<Table> theTable;
	static std::unique_ptr<PickupBoard> pickupBoard;
	static std::unique_ptr<ImguiInterface> imguiInterface;
	static Bot theBot;

	static unsigned fetchFps();
	static float fetchFrametime();

	static void updateVsyncSetting();
	static void updateAntialiasingSetting();

	static void destroyWindow();
	static void initializeWindow();

public:
	static int start();

	static void restart();

	friend class ImguiInterface;
	friend class Bot;
	friend class Table;
	friend class PickupBoard;
};
