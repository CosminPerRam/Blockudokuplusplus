
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "table.h"

class Game
{
private:
	Table theTable;

private:
	void draw(sf::RenderWindow& window);
	void pollEvent(sf::Event& theEvent);

public:
	void start();
};