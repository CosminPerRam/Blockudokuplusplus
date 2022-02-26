#pragma once

#include "impl.h"
#include "block.h"

class Table : Drawable
{
private:
	enum cell { empty = 0, occupied, preview};

	cell cellTable[9][9] = { empty };

	sf::Vector2i previewApplyCoords;

	sf::Vector2i mousePositionToCellPosition(const sf::Vector2f& mousePosition);

	bool verifyCompletetion();

public:
	void draw(sf::RenderWindow& window);

	void applyBlock(Block& theBlock, const sf::Vector2i& tableCellCoords);
	sf::Vector2i previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition);
};
