#pragma once

#include "impl.h"
#include "block.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class Score : Drawable
{
private:
	sf::Font theFont;
	sf::Text theText;
	sf::Clock theClock;

	std::vector<unsigned> pieceAddedCount;
	Block* mostPopularBlock;

	float timePlayed = 0;
	bool gameLost = false;

	unsigned localBest = 0;

	unsigned score = 0, placed = 0, completionSquares = 0, completionLines = 0;
	int combo = -1, bestCombo = 0;

public:
	Score(unsigned piecesCount);

	void draw(sf::RenderWindow& window);

	void setGameLost();
	bool getGameState();

	void addCompletionSquare();
	void addCompletionLine();

	void addPiecePlaced(unsigned index);

	void addToCombo();
	void resetCombo();
};