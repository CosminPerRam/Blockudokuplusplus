#pragma once

#include "impl.h"
#include "block.h"
#include "spacing.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <iostream>

class PickupBoard : Drawable, Eventer
{
private:
	std::array<Block*, 3> pickupableBlocks = { nullptr };
	std::array<sf::IntRect, 3> pickupableAreas;

	int pickedUp = -1;
	sf::Vector2f pickedUpPosition;

	const sf::Vector2f startPosition = { PICKUP_START_POSITION_X, PICKUP_START_POSITION_Y };
	const int BoardLength = CELL_SPACING * 9, BoardHeight = CELL_SPACING * 3;

	bool anyBlocksLeft();

public:
	PickupBoard() {
		for (int i = 0; i < 3; i++)
		{
			pickupableBlocks[i] = new Block(getRandomBlock());

			std::cout << PICKUP_START_POSITION_Y << " " << PICKUP_START_POSITION_X + BoardHeight * i << " " << BoardHeight << " " << BoardHeight << std::endl;
			pickupableAreas[i] = { PICKUP_START_POSITION_Y + BoardHeight * i, PICKUP_START_POSITION_X, BoardHeight, BoardHeight };
		}
	}

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
};