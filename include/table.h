#pragma once

#include "impl.h"
#include "block.h"
#include "score.h"

#include <memory>

class Table : Drawable
{
public:
	enum cell { empty = 0, occupied, preview, occupiedPreview };
	enum class mark { square, vline, hline };

private:
	struct completetion {
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
