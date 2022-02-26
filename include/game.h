
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "table.h"
#include "pickupBoard.h"

class Game
{
private:
	Table theTable;
	PickupBoard pickupBoard;

private:
	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);

public:
	void start();
};