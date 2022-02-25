#pragma once

#include "impl.h"
#include "block.h"

class Table : Drawable
{
private:
	enum cell { empty = 0, occupied, preview};

	cell cellTable[9][9] = { empty };

public:
	void draw(sf::RenderWindow& window);

	bool applyBlock(Block& theBlock);
	bool previewBlock(Block& theHoldingBlock);
};
