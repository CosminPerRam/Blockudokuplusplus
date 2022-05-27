#pragma once

#include "block.h"

#include <SFML/System/Vector2.hpp>

#include <array>
#include <memory>

enum cell { empty = 0, occupied, preview, occupiedPreview };
enum class mark { square, vline, hline };

struct completetion { //a simple class to remember if a completition is a square, line or vertical line
	mark type;
	unsigned x = 0, y = 0; //vline uses only x, hline only y and square both

	completetion(mark theType, unsigned a, unsigned b = 0);
};

class cellMatrix
{
private:
	std::array<std::array<cell, 9>, 9> cellTable = { cell::empty };

public:
	const std::array<std::array<cell, 9>, 9>& getCells();

	sf::Vector2i previewApplyCoords = { -1, -1 };
	void clearPreviews();

	sf::Vector2i previewBlock(Block& theHoldingBlock, const sf::Vector2i& matrixPosition);

	std::unique_ptr<std::vector<completetion>> checkCompletetion();
	void executeCompletetions(std::unique_ptr<std::vector<completetion>>& completetions, cell withCell);

	void applyBlock(Block& theBlock, const sf::Vector2u& tableCellCoords, cell cellType = cell::occupied);
	bool canBlockBePlaced(Block& theBlock);

	std::vector<sf::Vector2u> getBlockPlacingPositions(Block& theBlock);

	void reset();
	unsigned getEmptyCellsAmount() const;
};