
#include "score.h"
#include "spacing.h"
#include "colors.h"
#include "utilities.h"

Score::Score() {
	theFont.loadFromFile("resources/font.ttf");

	theText.setFillColor(COLOR_BLACK);
	theText.setFont(theFont);
}

void Score::draw(sf::RenderWindow& window) {
	if (!gameLost) {
		theText.setCharacterSize(20);

		theText.setPosition({ SCORE_START_POSITION_X, SCORE_START_POSITION_Y });
		theText.setString("Score: " + std::to_string(score) + "\tPlaced: " + std::to_string(placed));

		window.draw(theText);

		theText.setPosition({ SCORE_START_POSITION2_X, SCORE_START_POSITION2_Y });
		theText.setString("Squares: " + std::to_string(completionSquares) + "\tLines: " + std::to_string(completionLines));

		window.draw(theText);
	}
	else {
		std::string endGameStatsString = "Game lost, stats: \n Score: " + std::to_string(score) +
			"\n Local best: " + std::to_string(localBest) +
			"\n Network best: " +
			"\n Blocks used: " + std::to_string(placed) +
			"\n Squares: " + std::to_string(completionSquares) +
			"\n Lines: " + std::to_string(completionLines) +
			"\n Time: " + std::to_string((unsigned)timePlayed) + " seconds" +
			"\n APM: " + std::to_string(timePlayed / placed);

		if (score)
			endGameStatsString += "\n SPM: " + std::to_string(timePlayed / score);

		theText.setCharacterSize(20);
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