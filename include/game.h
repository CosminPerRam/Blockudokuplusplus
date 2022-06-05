
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
	inline static unsigned latestFps = 0;
	inline static float latestFrameTimeMs = 0.f;

	inline static bool reinitializeWindow = false;

	static void draw();
	static void pollEvent(sf::Event& theEvent);
	static void update();

protected:
	static Score *theScore;
	static Table *theTable;
	static PickupBoard *pickupBoard;
	inline static ImguiInterface imguiInterface;
	inline static Bot theBot;

	static unsigned fetchFps();
	static float fetchFrametime();

	static void updateVsyncSetting();
	static void updateAntialiasingSetting();

	static void destroyWindow();
	static void initializeWindow();

	static void free();

public:
	static int start();

	static void restart();

	friend class ImguiInterface;
	friend class Bot;
	friend class Table;
	friend class PickupBoard;

	friend struct Settings::General; 
	friend struct Settings::Gameplay;
	friend struct Settings::Aspect;
};
