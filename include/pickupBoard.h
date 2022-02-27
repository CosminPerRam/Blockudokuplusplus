#pragma once

#include "impl.h"
#include "block.h"
#include "spacing.h"
#include "table.h"
#include "score.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <iostream>

class PickupBoard : Drawable, Eventer
{
private:
	std::array<Block*, 3> pickupableBlocks = { nullptr };
	std::array<sf::IntRect, 3> pickupableAreas;

	int pickedUpIndex = -1;
	sf::Vector2f pickedUpPosition;
	sf::Vector2i pickedUpPreviewCoords;

	const sf::Vector2f startPosition = { PICKUP_START_POSITION_X, PICKUP_START_POSITION_Y };
	const int BoardLength = CELL_SPACING * 9, BoardHeight = CELL_SPACING * 3;

	Table& theTable;
	Score& theScore;

	void generateBlocks();

	bool anyBlocksLeft();
	bool canAnyBlocksBePlaced();

public:
	PickupBoard(Table& theTable, Score& theScore);

	void draw(sf::RenderWindow& window);
	void pollEvent(sf::RenderWindow& window, sf::Event& theEvent);
};