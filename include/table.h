#pragma once

#include <SFML/Graphics.hpp>

#include "block.h"

class Table
{
private:
	enum cell { empty = 0, occupied, preview};

	cell cellTable[9][9] = { empty };

	Block aBlock = getRandomBlock();

public:
	void draw(sf::RenderWindow& window);

	bool applyBlock(Block& theBlock);
	bool previewBlock(Block& theHoldingBlock);
};
