#pragma once

#include "impl.h"
#include "block.h"
#include "score.h"
#include "spacing.h"

#include <SFML/Graphics/VertexArray.hpp>

#include <memory>

/*
	The cells table, it does not memorize where which block
	has been placed, it has a cell matrix.
*/
class Table : Drawable
{
public:
	enum cell { empty = 0, occupied, preview, occupiedPreview };
	enum class mark { square, vline, hline };

private:
	/*
		These variables store the margins of the table, they can be calculated and run
		at rendertime but calculating them only one time and reusing them is much better performance-wise
	*/
	sf::VertexArray minorGrid = sf::VertexArray(sf::Lines, 2 * (TABLE_SIZE * 2 - 2));
	sf::VertexArray majorGrid = sf::VertexArray(sf::Lines, 4 * 2 * 2);

	struct completetion { //a simple class to remember if a completition is a square, line or vertical line
		mark type;
		unsigned x = 0, y = 0; //vline uses only x, hline only y and square both

		completetion(mark theType, unsigned a, unsigned b = 0);
	};

	cell cellTable[9][9] = { cell::empty };

	Score& theScore;

	sf::Vector2i previewApplyCoords = {-1, -1};
	void clearPreviews();

	sf::Vector2i mousePositionToCellPosition(const sf::Vector2f& mousePosition);

	std::unique_ptr<std::vector<completetion>> checkCompletetion();
	void executeCompletetionsWith(std::unique_ptr<std::vector<completetion>>& completetions, cell withCell);

public:
	Table(Score& theScore);

	void draw(sf::RenderWindow& window);

	void applyBlock(Block& theBlock, const sf::Vector2i& tableCellCoords);
	sf::Vector2i previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition);
	bool canBlockBePlaced(Block& theBlock);
};
