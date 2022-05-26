#pragma once

#include "impl.h"
#include "block.h"
#include "spacing.h"
#include "table.h"
#include "score.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>

/*
	Manages picking up, regenerating the blocks and checking if the game is lost.
	The rest of the classes have nothing to do with its components.
*/
class PickupBoard : Drawable, Eventer, Colored
{
private:
	sf::Color MARGINS;

	sf::VertexArray borders = sf::VertexArray(sf::Lines, 2 * 2 + 4 * 2);

	std::array<Block*, 3> pickupableBlocks = { nullptr };

	int pickedUpIndex = -1;
	sf::Vector2f pickedUpPosition;
	sf::Vector2i pickedUpPreviewCoords;

	const sf::Vector2f startPosition = { PICKUP_POSITION_X, PICKUP_POSITION_Y };
	const int BoardLength = CELL_SPACING * 9, BoardHeight = CELL_SPACING * 3;

	Table& theTable;
	Score& theScore;

	void generateMissingBlocks();
	void generateBlocks();
	void placeIndexInDefaultPosition(unsigned i);

	bool anyBlocksLeft();
	bool canAnyBlocksBePlaced();
	bool recursiveCanAnyBlocksBePlaced(int firstIndex = -1, int secondIndex = -1);

	void calculateVertexes();

public:
	PickupBoard(Table& theTable, Score& theScore);
	~PickupBoard();

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
	void updateColors();

	bool isBoardLost();

	void reset();

	friend class ImguiInterface;
};