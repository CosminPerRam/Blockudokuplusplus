
#include "score.h"
#include "spacing.h"
#include "settings.h"
#include "utilities.h"
#include "game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

const char* Score::Data::filePath = "resources/userData.txt";
unsigned Score::Data::localBest = 0;

void Score::Data::writeLocalBest(unsigned score)
{
	localBest = score;
	Files::writeToFile(std::to_string(score), "resources/userData.txt");
}
void Score::Data::loadLocalBest()
{
	auto stream = Files::getFileContents("resources/userData.txt");
	stream >> localBest;
}
unsigned Score::Data::getLocalBest()
{
	return localBest;
}

Score::Score(unsigned piecesCount) 
{
	pieceAddedCount.resize(piecesCount + 1, 0); //+1 because the last element represents the use of the custom block

	if(!theFont.loadFromFile("resources/courierNewFont.ttf"))
		throw "Couldn't load the font";

	Data::loadLocalBest();

	Score::updateColors();

	theText.setFont(theFont);

	restartButton.setFillColor({ 255,255,255 });
	restartButton.setOutlineColor({ 0,0,0 });
	restartButton.setOutlineThickness(2);
	restartButton.setSize({ RESTART_SIZE_WIDTH, RESTART_SIZE_HEIGHT });
	restartButton.setPosition({ RESTART_POSITION_X - RESTART_SIZE_WIDTH / 2.f, RESTART_POSITION_Y - RESTART_SIZE_HEIGHT / 4.f });
}

Score::~Score()
{
	delete mostPopularBlock;
}

void Score::reset(bool restart) {
	std::fill(pieceAddedCount.begin(), pieceAddedCount.end(), 0);

	timePlayedSeconds = 0;
	score = 0, placed = 0, completionSquares = 0, completionLines = 0;
	combo = -1, bestCombo = 0;

	if(restart)
		gameLost = false;
}

void Score::draw(sf::RenderWindow& window) {
	if (!gameLost) {
		theText.setCharacterSize(16);

		theText.setPosition({ SCORE_POSITION_X, SCORE_POSITION_Y });
		theText.setString("Score: " + std::to_string(score) + "\tPlaced: " + std::to_string(placed));

		window.draw(theText);

		theText.setPosition({ SCORE_POSITION2_X, SCORE_POSITION2_Y });
		theText.setString("Squares: " + std::to_string(completionSquares) +
			"\tCombo: " + std::to_string(combo > -1 ? combo : 0) +
			"\nLines: " + std::to_string(completionLines) +
			(Settings::Gameplay::autoplay ? "\tAutoplay." : ""));

		window.draw(theText);
	}
	else {
		std::string endGameStatsString = "Game lost, stats: \n        Score: " + std::to_string(score) + (score > Data::localBest ? " (highscore)" : "") +
			"\n   Local best: " + std::to_string(Data::localBest) +
			"\n Squares made: " + std::to_string(completionSquares) +
			"\n   Lines made: " + std::to_string(completionLines) +
			"\n   Best combo: " + std::to_string(bestCombo) +
			"\n  Blocks used: " + std::to_string(placed) +
			"\n         Time: " + std::to_string((unsigned)timePlayedSeconds) + " seconds" +
			"\n          APM: " + std::to_string(apm) +
			"\n          SPM: " + std::to_string(spm) +
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

void Score::update(sf::RenderWindow& window, sf::Time& dt) {
	if (gameLost)
		return;
	
	timePlayedSeconds += dt.asSeconds();

	apm = placed > 0 ? placed / (timePlayedSeconds / 60) : 0;
	spm = score > 0 ? score / (timePlayedSeconds / 60) : 0;
}

void Score::updateColors() {
	TEXT_COLOR = toColor(Settings::Aspect::textColor);

	theText.setFillColor(TEXT_COLOR);
}

void Score::processMarks(std::unique_ptr<std::vector<completetion>>& marks) {
	if (marks->empty())
		resetCombo();
	else {
		addToCombo(marks->size());
		if (marks->size() > 1) //give one point for getting more marks at one time
			addToCombo(1);

		for (const auto& m : *marks) {
			if (m.type == mark::square)
				addCompletionSquare();
			else
				addCompletionLine();
		}
	}
}

void Score::setGameLost() {
	gameLost = true;

	unsigned mostPopularBlockIndex = 0, mostPopularBlockValue = 0;	//the most popular block is the most generated one
	for (unsigned i = 0; i < pieceAddedCount.size(); i++) {
		if (pieceAddedCount[i] > mostPopularBlockValue)
		{
			mostPopularBlockIndex = i;
			mostPopularBlockValue = pieceAddedCount[i];
		}
	}

	if(mostPopularBlockIndex == pieceAddedCount.size() - 1)
		mostPopularBlock = new Block(-2);
	else
		mostPopularBlock = new Block(mostPopularBlockIndex);

	mostPopularBlock->setScale(0.24f);
	mostPopularBlock->setPosition({ SCORE_POPULAR_PIECE_POSITION_X - mostPopularBlock->getGlobalBounds().width / 2.f,
		SCORE_POPULAR_PIECE_POSITION_Y - mostPopularBlock->getGlobalBounds().height / 2.f });

	if (score > Data::localBest)
		Data::writeLocalBest(score);
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

void Score::addPiecePlaced(int index) {
	if (index == -2) //-2 is the custom block
		pieceAddedCount.back()++;
	else
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
