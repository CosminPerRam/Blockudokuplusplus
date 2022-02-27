
#include "score.h"

#include "spacing.h"
#include "colors.h"

Score::Score() {
	theFont.loadFromFile("resources/font.ttf");

	theText.setFillColor(COLOR_BLACK);
	theText.setFont(theFont);
}

void Score::draw(sf::RenderWindow& window) {
	if (!gameLost) {
		theText.setPosition({ SCORE_START_POSITION_X, SCORE_START_POSITION_Y });
		theText.setString("Score: " + std::to_string(score) + "\tPlaced: " + std::to_string(placed));
		theText.setCharacterSize(18);

		window.draw(theText);

		theText.setPosition({ SCORE_START_POSITION2_X, SCORE_START_POSITION2_Y });
		theText.setString("Squares: " + std::to_string(completionSquares) + "\tLines: " + std::to_string(completionLines));
		theText.setCharacterSize(18);

		window.draw(theText);
	}
	else {
		theText.setPosition({ SCORE_START_POSITION_X, SCORE_START_POSITION_Y });
		theText.setString("Game lost, score: " + std::to_string(score) + 
						"\nPlaced: " + std::to_string(placed) +
						"\nSquares: " + std::to_string(completionSquares) +
						"\nLines: " + std::to_string(completionLines));
		theText.setCharacterSize(18);

		window.draw(theText);
	}
}

void Score::setGameLost() {
	gameLost = true;
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