#pragma once

#include "impl.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class Score : Drawable
{
private:
	sf::Font theFont;
	sf::Text theText;
	sf::Clock theClock;

	float timePlayed = 0;

	unsigned localBest = 0;

	unsigned score = 0, placed = 0, completionSquares = 0, completionLines = 0;
	bool gameLost = false;

public:
	Score();

	void draw(sf::RenderWindow& window);

	void setGameLost();
	bool getGameState();

	void addCompletionSquare();
	void addCompletionLine();

	void addPiecePlaced();
};