#pragma once

#include "impl.h"
#include "block.h"

#include <array>

class PickupBoard : Drawable, Eventer
{
private:
	std::array<Block*, 3> pickupableBlocks = { nullptr };
	int pickedUp = -1;

	bool anyBlocksLeft();

public:
	PickupBoard() {
		for (unsigned i = 0; i < 3; i++)
			pickupableBlocks[i] = new Block(getRandomBlock());
	}

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::Event& theEvent);
};