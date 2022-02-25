
#include "pickupBoard.h"

#include "spacing.h"
#include "colors.h"

#include <SFML/Graphics/VertexArray.hpp>

bool PickupBoard::anyBlocksLeft() {
	for (unsigned i = 0; i < 3; i++) {
		if (pickupableBlocks[i] != nullptr)
			return true;
	}

	return false;
}

void PickupBoard::draw(sf::RenderWindow& window)
{
	sf::Vector2f startPosition = { PICKUP_START_POSITION_X, PICKUP_START_POSITION_Y };

	unsigned BoardLength = CELL_SPACING * 9, BoardHeight = CELL_SPACING * 3;

    sf::VertexArray borders(sf::Lines, 2 * 2 + 4 * 2);

    for (unsigned i = 0; i < 2; i++) {
        float rowY = BoardHeight * i;
        borders[i * 2].position = { startPosition.y, rowY + startPosition.x };
        borders[i * 2].color = COLOR_GRAY;
        borders[i * 2 + 1].position = { BoardLength + startPosition.y, rowY + startPosition.x };
        borders[i * 2 + 1].color = COLOR_GRAY;
    }

    unsigned gridPositionOffset = 4;
    for (unsigned i = 0; i < 4; i++) {
        float rowX = BoardHeight * i;
        borders[gridPositionOffset + i * 2].position = { rowX + startPosition.y, startPosition.x };
        borders[gridPositionOffset + i * 2].color = COLOR_GRAY;
        borders[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.y, BoardHeight + startPosition.x };
        borders[gridPositionOffset + i * 2 + 1].color = COLOR_GRAY;
    }

    window.draw(borders);

    for (float i = 0; i < 3; i++) {
        if (pickupableBlocks[i] != nullptr) {
            if (pickedUp == i) {

            }
            else {
                pickupableBlocks[i]->setScale(0.8);
                pickupableBlocks[i]->setPosition({ PICKUP_START_POSITION_Y + BoardHeight * i, PICKUP_START_POSITION_X });
                pickupableBlocks[i]->draw(window);
            }
        }
    }
}

void PickupBoard::pollEvent(sf::Event& theEvent)
{

}