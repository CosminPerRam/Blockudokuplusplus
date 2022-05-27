#pragma once

#include "block.h"
#include "score.h"
#include "spacing.h"
#include "cellMatrix.h"

#include <SFML/Graphics/VertexArray.hpp>

#include <memory>
#include <array>

/*
	The cells table, it does not memorize where which block
	has been placed, it has a cell matrix.
*/
class Table
{
private:
	sf::Color MINOR_COLOR, MAJOR_COLOR;
	sf::Color TABLE_ODD, TABLE_EVEN;
	sf::Color CELL_SOLID, CELL_COMPLETION, CELL_PREVIEW;

	/*
		These variables store the margins of the table, they can be calculated and run
		at rendertime but calculating them only one time and reusing them is much better performance-wise
	*/
	sf::VertexArray minorGrid = sf::VertexArray(sf::Lines, 2 * (TABLE_SIZE * 2 - 2));
	sf::VertexArray majorGrid = sf::VertexArray(sf::Lines, 4 * 2 * 2);

	cellMatrix theMatrix;

	Score& theScore;

	sf::Vector2i mousePositionToCellPosition(const sf::Vector2f& mousePosition);

	void calculateVertexes();

public:
	Table(Score& theScore);

	void draw(sf::RenderWindow& window);
	void updateColors();

	void applyBlock(Block& theBlock, const sf::Vector2u& tableCellCoords);
	bool canBlockBePlaced(Block& theBlock);

	sf::Vector2i previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition);

	const cellMatrix& getMatrix();
	void reset();

	friend class ImguiInterface;
	friend class Bot;
};
