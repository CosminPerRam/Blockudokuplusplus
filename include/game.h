
#include "table.h"
#include "pickupBoard.h"
#include "score.h"
#include "block.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
private:
	Score theScore = (Block::getAllStructuresCount());
	Table theTable = (theScore);
	PickupBoard pickupBoard = PickupBoard(theTable, theScore);

private:
	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

public:
	Game();

	void start();
};