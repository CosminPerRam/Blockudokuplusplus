#pragma once

#include "impl.h"
#include "block.h"
#include "score.h"

class Table : Drawable
{
public:
	enum cell { empty = 0, occupied, preview };

private:
	cell cellTable[9][9] = { empty };

	Score& theScore;

	sf::Vector2i previewApplyCoords = {-1, -1};

	sf::Vector2i mousePositionToCellPosition(const sf::Vector2f& mousePosition);

	bool checkCompletetion();

public:
	Table(Score& theScore);

	void draw(sf::RenderWindow& window);

	void applyBlock(Block& theBlock, const sf::Vector2i& tableCellCoords);
	sf::Vector2i previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition);
	bool canBlockBePlaced(Block& theBlock);
};
