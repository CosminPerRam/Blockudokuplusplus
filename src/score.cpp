
#include "score.h"
#include "spacing.h"
#include "colors.h"
#include "utilities.h"

Score::Score() {
	theFont.loadFromFile("resources/courierNewFont.ttf");

	theText.setFillColor(COLOR_BLACK);
	theText.setFont(theFont);
}

void Score::draw(sf::RenderWindow& window) {
	if (!gameLost) {
		theText.setCharacterSize(16);

		theText.setPosition({ SCORE_START_POSITION_X, SCORE_START_POSITION_Y });
		theText.setString("Score: " + std::to_string(score) + "\tPlaced: " + std::to_string(placed));

		window.draw(theText);

		theText.setPosition({ SCORE_START_POSITION2_X, SCORE_START_POSITION2_Y });
		theText.setString("Squares: " + std::to_string(completionSquares) + "\tCombo: " + std::to_string(combo > -1 ? combo : 0) + "\nLines: " + std::to_string(completionLines));

		window.draw(theText);
	}
	else {
		std::string endGameStatsString = "Game lost, stats: \n         Score: " + std::to_string(score) +
			"\n    Local best: " + std::to_string(localBest) +
			"\n  Squares made: " + std::to_string(completionSquares) +
			"\n    Lines made: " + std::to_string(completionLines) +
			"\n    Best combo: " + std::to_string(bestCombo) +
			"\n   Blocks used: " + std::to_string(placed) +
			"\n          Time: " + std::to_string((unsigned)timePlayed) + " seconds" +
			"\n           APM: " + std::to_string(timePlayed / placed);

		if (score)
			endGameStatsString += "\n           SPM: " + std::to_string(timePlayed / score);

		theText.setCharacterSize(16);
		theText.setPosition({ SCORE_START_POSITION_X, SCORE_START_POSITION_Y });
		theText.setString(endGameStatsString);

		window.draw(theText);
	}
}

void Score::setGameLost() {
	gameLost = true;
	timePlayed = theClock.getElapsedTime().asSeconds();

	auto stream = files::getFileContents("resources/userData.txt");
	stream >> localBest;

	if (score > localBest)
		files::writeToFile(std::to_string(score), "resources/userData.txt");
}

bool Score::getGameState() {
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

void Score::addPiecePlaced() {
	placed++;
}

void Score::addToCombo() {	//How combo works:
	combo++;				//If you continously complete lines/blocks, its a combo
}

void Score::resetCombo() {
	if (combo > bestCombo)
		bestCombo = combo;

	combo = -1;
}