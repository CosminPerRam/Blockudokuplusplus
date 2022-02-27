
#include "pickupBoard.h"

#include "colors.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

PickupBoard::PickupBoard(Table& theTable, Score& theScore) : theTable(theTable), theScore(theScore)
{
    generateBlocks();
}

void PickupBoard::generateBlocks() {
    for (int i = 0; i < 3; i++)
        pickupableBlocks[i] = new Block(getRandomBlock());
}

bool PickupBoard::anyBlocksLeft() {
	for (unsigned i = 0; i < 3; i++) {
		if (pickupableBlocks[i] != nullptr)
			return true;
	}

	return false;
}

bool PickupBoard::canAnyBlocksBePlaced() {
    bool canAnyBePlaced = false;

    for (unsigned i = 0; i < 3; i++) {
        if (pickupableBlocks[i] == nullptr)
            continue;

        if (theTable.canBlockBePlaced(*pickupableBlocks[i])) {
            canAnyBePlaced = true;
            pickupableBlocks[i]->setOpacity(255);
        }
        else
            pickupableBlocks[i]->setOpacity(128);
    }

    return canAnyBePlaced;
}

void PickupBoard::draw(sf::RenderWindow& window)
{
    sf::VertexArray borders(sf::Lines, 2 * 2 + 4 * 2);

    for (unsigned i = 0; i < 2; i++) {
        float rowY = BoardHeight * i * 1.f;
        borders[i * 2].position = { startPosition.y, rowY + startPosition.x };
        borders[i * 2].color = COLOR_GRAY;
        borders[i * 2 + 1].position = { BoardLength + startPosition.y, rowY + startPosition.x };
        borders[i * 2 + 1].color = COLOR_GRAY;
    }

    unsigned gridPositionOffset = 4;
    for (unsigned i = 0; i < 4; i++) {
        float rowX = BoardHeight * i * 1.f;
        borders[gridPositionOffset + i * 2].position = { rowX + startPosition.y, startPosition.x };
        borders[gridPositionOffset + i * 2].color = COLOR_GRAY;
        borders[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.y, BoardHeight + startPosition.x };
        borders[gridPositionOffset + i * 2 + 1].color = COLOR_GRAY;
    }

    window.draw(borders);

    for (unsigned i = 0; i < 3; i++) {
        if (pickupableBlocks[i] != nullptr) {
            if (pickedUpIndex == i) {
                pickupableBlocks[i]->setScale(0.9f);
                pickupableBlocks[i]->setPosition(pickedUpPosition);
            }
            else {
                auto bounds = pickupableBlocks[i]->getLocalBounds();

                pickupableBlocks[i]->setScale(0.85f + (3 - (int)std::max(pickupableBlocks[i]->getStructureSize().x, pickupableBlocks[i]->getStructureSize().y)) * 0.15f);
                pickupableBlocks[i]->setPosition({ PICKUP_START_POSITION_Y + BoardHeight * i + (BoardHeight - bounds.width) / 2.f,
                    PICKUP_START_POSITION_X + (BoardHeight - bounds.height) / 2.f });
            }

            pickupableBlocks[i]->draw(window);
        }
    }
}

void PickupBoard::pollEvent(sf::RenderWindow& window, sf::Event& theEvent)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f mousePositionWithOffset = { mousePosition.x - PICKUP_OFFSET, mousePosition.y - PICKUP_OFFSET };

    if (pickedUpIndex != -1) {
        pickedUpPosition = mousePositionWithOffset;
        pickedUpPreviewCoords = theTable.previewBlock(*pickupableBlocks[pickedUpIndex], mousePosition);
    }
    else {
        if (theEvent.type == sf::Event::MouseButtonPressed && theEvent.mouseButton.button == sf::Mouse::Left) {
            for (unsigned i = 0; i < 3 && pickedUpIndex == -1; i++) {
                if (pickupableBlocks[i] != nullptr) {
                    if (pickupableBlocks[i]->getLocalBounds().contains({ mousePosition.x, mousePosition.y }))
                    {
                        pickedUpPosition = mousePositionWithOffset; //if this werent to be here, the first frame would be rendered on the last position remembered
                        pickedUpIndex = i;
                    }
                }
            }
        }
    }
    
    if (theEvent.type == sf::Event::MouseButtonReleased && theEvent.mouseButton.button == sf::Mouse::Left) {
        if (pickedUpIndex != -1)
        {
            if (pickedUpPreviewCoords.x != -1 || pickedUpPreviewCoords.y != -1) {
                theTable.applyBlock(*pickupableBlocks[pickedUpIndex], pickedUpPreviewCoords);

                theScore.addPiecePlaced();

                delete pickupableBlocks[pickedUpIndex];
                pickupableBlocks[pickedUpIndex] = nullptr;

                if (!anyBlocksLeft())
                    generateBlocks();

                if (!canAnyBlocksBePlaced())
                    theScore.setGameLost();

                pickedUpPreviewCoords = { -1, -1 };
            }

            pickedUpIndex = -1;
        }
    }
}