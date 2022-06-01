#pragma once

#include "block.h"
#include "settings.h"
#include "cellMatrix.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

/*
	The score has 2 faces, one while the game
	is running and one when the game is lost.
*/
class Score
{
private:
	sf::Color TEXT_COLOR;

	sf::Font theFont;
	sf::Text theText;
	sf::Clock theClock;
	sf::RectangleShape restartButton;

	std::vector<unsigned> pieceAddedCount;
	Block* mostPopularBlock = nullptr;

	float timePlayed = 0;
	bool gameLost = false;

	class Data
	{
	public:
		static const char* filePath;

		static unsigned localBest;

		static void writeLocalBest(unsigned score);
		static void loadLocalBest();
		static unsigned getLocalBest();
	};

	unsigned score = 0, placed = 0, completionSquares = 0, completionLines = 0;
	int combo = -1, bestCombo = 0;

	void addCompletionSquare();
	void addCompletionLine();

	void addToCombo(unsigned amount);
	void resetCombo();

public:
	Score(unsigned piecesCount);
	~Score();

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

	void updateColors();

	void processMarks(std::unique_ptr<std::vector<completetion>>& marks);

	void setGameLost();
	bool isGameLost();

	void addPiecePlaced(int index);

	void reset(bool restart = false);

	friend class ImguiInterface;
};
