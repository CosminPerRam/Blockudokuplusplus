
#include "pickupBoard.h"

#include "colors.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

PickupBoard::PickupBoard(Table& theTable, Score& theScore) : theTable(theTable), theScore(theScore)
{
    for (int i = 0; i < 3; i++)
        pickupableAreas[i] = { PICKUP_START_POSITION_Y + BoardHeight * i, PICKUP_START_POSITION_X, BoardHeight, BoardHeight };

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

bool PickupBoard::canBlocksBePlaced() {

    return false;
}

void PickupBoard::draw(sf::RenderWindow& window)
{
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
            if (pickedUpIndex == i) {
                pickupableBlocks[i]->setScale(0.9);
                pickupableBlocks[i]->setPosition(pickedUpPosition);
            }
            else {
                pickupableBlocks[i]->setScale(0.85 + (3 - std::max(pickupableBlocks[i]->getStructureSize().x, pickupableBlocks[i]->getStructureSize().y)) * 0.15);
                pickupableBlocks[i]->setPosition({ PICKUP_START_POSITION_Y + BoardHeight * i,
                    PICKUP_START_POSITION_X});
            }

            pickupableBlocks[i]->draw(window);
        }
    }

    /*
    for (unsigned i = 0; i < 3; i++) {
        sf::RectangleShape s;
        s.setPosition({(float)pickupableAreas[i].left, (float)pickupableAreas[i].top});
        s.setSize({ (float)pickupableAreas[i].width, (float)pickupableAreas[i].height});
        s.setFillColor({255,0,0,100});

        window.draw(s);
    }*/
}

void PickupBoard::pollEvent(sf::RenderWindow& window, sf::Event& theEvent)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (pickedUpIndex != -1) {
        pickedUpPosition = mousePosition;
        pickedUpPreviewCoords = theTable.previewBlock(*pickupableBlocks[pickedUpIndex], mousePosition);
    }
    else {
        if (theEvent.type == sf::Event::MouseButtonPressed && theEvent.mouseButton.button == sf::Mouse::Left) {
            for (unsigned i = 0; i < 3; i++) {
                if (pickupableAreas[i].contains({ (int)mousePosition.x, (int)mousePosition.y }) && pickupableBlocks[i] != nullptr)
                {
                    pickedUpPosition = mousePosition; //if this werent to be here, the first frame would be rendered on the last position remembered
                    pickedUpIndex = i;
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

                pickedUpPreviewCoords = { -1, -1 };
            }

            pickedUpIndex = -1;
        }
    }
}