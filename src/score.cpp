
#include "score.h"
#include "spacing.h"
#include "colors.h"
#include "utilities.h"
#include "game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

Score::Score(unsigned piecesCount) 
{
	pieceAddedCount.resize(piecesCount, 0);

	theFont.loadFromFile("resources/courierNewFont.ttf");

	theText.setFillColor(COLOR_BLACK);
	theText.setFont(theFont);

	restartButton.setFillColor(COLOR_WHITE);
	restartButton.setOutlineColor(COLOR_BLACK);
	restartButton.setOutlineThickness(2);
	restartButton.setSize({ RESTART_SIZE_WIDTH, RESTART_SIZE_HEIGHT });
	restartButton.setPosition({ RESTART_POSITION_X - RESTART_SIZE_WIDTH / 2.f, RESTART_POSITION_Y - RESTART_SIZE_HEIGHT / 4.f });
}

Score::~Score()
{
	delete mostPopularBlock;
}

void Score::draw(sf::RenderWindow& window) {
	if (!gameLost) {
		theText.setCharacterSize(16);

		theText.setPosition({ SCORE_POSITION_X, SCORE_POSITION_Y });
		theText.setString("Score: " + std::to_string(score) + "\tPlaced: " + std::to_string(placed));

		window.draw(theText);

		theText.setPosition({ SCORE_POSITION2_X, SCORE_POSITION2_Y });
		theText.setString("Squares: " + std::to_string(completionSquares) + "\tCombo: " + std::to_string(combo > -1 ? combo : 0) + "\nLines: " + std::to_string(completionLines));

		window.draw(theText);
	}
	else {
		std::string endGameStatsString = "Game lost, stats: \n        Score: " + std::to_string(score) + (score > localBest ? " (highscore)" : "") +
			"\n   Local best: " + std::to_string(localBest) +
			"\n Squares made: " + std::to_string(completionSquares) +
			"\n   Lines made: " + std::to_string(completionLines) +
			"\n   Best combo: " + std::to_string(bestCombo) +
			"\n  Blocks used: " + std::to_string(placed) +
			"\n         Time: " + std::to_string((unsigned)timePlayed) + " seconds" +
			"\n          APM: " + std::to_string(timePlayed / placed) +
			"\n          SPM: " + std::to_string(timePlayed / score) +
			"\nThe most popular block: ";

		theText.setString(endGameStatsString);
		theText.setCharacterSize(16);
		theText.setPosition({ SCORE_POSITION_X, SCORE_POSITION_Y });

		window.draw(theText);
		
		mostPopularBlock->draw(window);

		window.draw(restartButton);

		theText.setString("Restart");
		theText.setCharacterSize(24);
		theText.setPosition({ RESTART_POSITION_X - theText.getLocalBounds().width / 2.f, RESTART_POSITION_Y - theText.getLocalBounds().height / 2.f });

		window.draw(theText);
	}
}

void Score::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	if (!gameLost)
		return;
	
	if (theEvent.type == sf::Event::MouseButtonPressed && theEvent.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if (restartButton.getGlobalBounds().contains({ mousePosition.x, mousePosition.y })) 
			Game::restart();
	}
}

void Score::setGameLost() {
	gameLost = true;
	timePlayed = theClock.getElapsedTime().asSeconds();

	unsigned mostPopularBlockIndex = 0, mostPopularBlockValue = 0;	//its also the most generated one, shhh
	for (unsigned i = 0; i < pieceAddedCount.size(); i++) {
		if (pieceAddedCount[i] > mostPopularBlockValue)
		{
			mostPopularBlockIndex = i;
			mostPopularBlockValue = pieceAddedCount[i];
		}
	}

	mostPopularBlock = new Block(mostPopularBlockIndex);
	mostPopularBlock->setScale(0.24);
	mostPopularBlock->setPosition({ SCORE_POPULAR_PIECE_POSITION_X - mostPopularBlock->getLocalBounds().width / 2.f,
		SCORE_POPULAR_PIECE_POSITION_Y - mostPopularBlock->getLocalBounds().height / 2.f });

	auto stream = files::getFileContents("resources/userData.txt");
	stream >> localBest;

	if (score > localBest)
		files::writeToFile(std::to_string(score), "resources/userData.txt");
}

bool Score::isGameLost() {
	return gameLost;
}

void Score::addCompletionSquare() {
	score += 8;
	completionSquares++;
}

void Score::addCompletionLine() {
	score += 4;
	completionLines++;
}

void Score::addPiecePlaced(unsigned index) {
	if (index > pieceAddedCount.size() - 1)
		throw "Bad addPiecePlaced index value!";

	pieceAddedCount[index]++;

	placed++;
}

void Score::addToCombo(unsigned amount) {	//How combo works:
	combo += amount;						//If you continously complete lines/blocks (or more at one time), its a combo
}

void Score::resetCombo() {
	if (combo > bestCombo)
		bestCombo = combo;

	combo = -1;
}