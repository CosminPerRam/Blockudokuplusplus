
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "table.h"
#include "pickupBoard.h"
#include "score.h"

class Game
{
private:
	Score theScore;
	Table theTable = (theScore);
	PickupBoard pickupBoard = PickupBoard(theTable, theScore);

private:
	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

public:
	void start();
};