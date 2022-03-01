#pragma once

#include "impl.h"
#include "block.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Score : Drawable, Eventer
{
private:
	sf::Font theFont;
	sf::Text theText;
	sf::Clock theClock;
	sf::RectangleShape restartButton;

	std::vector<unsigned> pieceAddedCount;
	Block* mostPopularBlock = nullptr;

	float timePlayed = 0;
	bool gameLost = false;

	unsigned localBest = 0;

	unsigned score = 0, placed = 0, completionSquares = 0, completionLines = 0;
	int combo = -1, bestCombo = 0;

public:
	Score(unsigned piecesCount);

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

	void setGameLost();
	bool isGameLost();

	void addCompletionSquare();
	void addCompletionLine();

	void addPiecePlaced(unsigned index);

	void addToCombo();
	void resetCombo();
};