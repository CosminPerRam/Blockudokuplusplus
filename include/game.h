
#include "table.h"
#include "pickupBoard.h"
#include "score.h"
#include "block.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/*
	Like the Audio class, this is a static class as its not possible
	to have multiple instances of the game running at the same time.
*/
class Game
{
private:
	static Score *theScore;
	static Table *theTable;
	static PickupBoard *pickupBoard;

	static void draw(sf::RenderWindow& window);
	static void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

public:
	static int start();

	static void restart();
};