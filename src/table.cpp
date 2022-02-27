
#include "table.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "colors.h"
#include "spacing.h"

sf::Vector2i Table::mousePositionToCellPosition(const sf::Vector2f& mousePosition)
{
    sf::Vector2f startPosition = { TABLE_START_POSITION_X, TABLE_START_POSITION_Y };

    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            sf::FloatRect cell = {startPosition.x + CELL_SPACING * l, startPosition.y + CELL_SPACING * c, CELL_SPACING, CELL_SPACING };

            if (cell.contains(mousePosition))
                return { l, c };
        }
    }

    return { -1, -1 };
}

bool Table::verifyCompletetion() {

    return false;
}

void Table::applyBlock(Block& theBlock, const sf::Vector2i& tableCellCoords)
{
    //wont do any verifications for the tableCellCords or the block compatibility
    //because this function is SUPPOSED to be used ONLY with the RIGHT stuff.

    auto structure = theBlock.getStructure();
    for (unsigned x = 0; x < theBlock.getStructureSize().x; x++) {
        for (unsigned y = 0; y < theBlock.getStructureSize().y; y++) {
            if (structure[x][y] == cell::occupied)
                cellTable[tableCellCoords.x + x][tableCellCoords.y + y] = cell::occupied;
        }
    }
}

sf::Vector2i Table::previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition)
{
    auto cellCoords = mousePositionToCellPosition(mousePosition);

    auto blockStructureSize = theHoldingBlock.getStructureSize();

    if (previewApplyCoords.x != -1 && previewApplyCoords.y != -1 && previewApplyCoords != cellCoords) {
        for (unsigned x = 0; x < blockStructureSize.x; x++) {
            for (unsigned y = 0; y < blockStructureSize.y; y++) {
                if (cellTable[previewApplyCoords.x + x][previewApplyCoords.y + y] == cell::preview)
                    cellTable[previewApplyCoords.x + x][previewApplyCoords.y + y] = cell::empty;
            }
        }
    }

    previewApplyCoords = cellCoords;

    if (cellCoords.x == -1 || cellCoords.y == -1)
        return { -1, -1 }; //first check mouse is in a cell

    if (cellCoords.x + blockStructureSize.x > 9 || cellCoords.y + blockStructureSize.y > 9)
        return { -1, -1 }; //secondly, check if the holding block is not out of bounds from the cell coords

    auto blockStructure = theHoldingBlock.getStructure();

    bool placeable = true;
    for (unsigned x = 0; x < blockStructureSize.x; x++) {
        for (unsigned y = 0; y < blockStructureSize.y; y++) {
            if (blockStructure[x][y] == cell::occupied) {
                if (cellTable[cellCoords.x + x][cellCoords.y + y] == cell::occupied) {
                    placeable = false;
                    break;
                }
            }
        }

        if (!placeable)
            break;
    }

    if (placeable) {
        for (unsigned x = 0; x < blockStructureSize.x; x++) {
            for (unsigned y = 0; y < blockStructureSize.y; y++) {
                if (blockStructure[x][y] == cell::occupied && cellTable[cellCoords.x + x][cellCoords.y + y] != cell::occupied)
                    cellTable[cellCoords.x + x][cellCoords.y + y] = cell::preview;
            }
        }
    }

    return cellCoords;
}

void Table::draw(sf::RenderWindow& window)
{
    sf::Vector2f startPosition = { TABLE_START_POSITION_X, TABLE_START_POSITION_Y };
    float lineLength = CELL_SPACING * TABLE_SIZE;

    for (unsigned l = 0; l < 9; l++) {
        for (unsigned c = 0; c < 9; c++) {
            sf::RectangleShape cell;
            cell.setPosition({ startPosition.x + CELL_SPACING * l, startPosition.y + CELL_SPACING * c });
            cell.setSize({ CELL_SPACING, CELL_SPACING });

            switch (cellTable[l][c]) {
            case cell::empty:
            {
                if ((l < 3 && c < 3) || (c > 5 && l < 3) || (l > 5 && c < 3) || (l > 5 && c > 5) || (l > 2 && l < 6 && c > 2 && c < 6))
                    cell.setFillColor(COLOR_GRAY);
                else
                    cell.setFillColor(COLOR_WHITE);
            } break;
            case cell::occupied:
            {
                cell.setFillColor(COLOR_BLUE);
            } break;
            case cell::preview:
            {
                cell.setFillColor(COLOR_LIGHT_BLUE);
            } break;
            }

            window.draw(cell);
        }
    }

    //DRAW CELLS END

    sf::VertexArray minorGrid(sf::Lines, 2 * (TABLE_SIZE * 2 - 2));

    for (unsigned i = 0; i < TABLE_SIZE - 1; i++) {
        float rowY = CELL_SPACING * (i + 1);
        minorGrid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        minorGrid[i * 2].color = COLOR_LIGHT_BLUE;
        minorGrid[i * 2 + 1].position = { lineLength + startPosition.y, rowY + startPosition.y };
        minorGrid[i * 2 + 1].color = COLOR_LIGHT_BLUE;
    }

    unsigned gridPositionOffset = (TABLE_SIZE - 1) * 2;
    for (unsigned i = 0; i < TABLE_SIZE - 1; i++) {
        float rowX = CELL_SPACING * (i + 1);
        minorGrid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        minorGrid[gridPositionOffset + i * 2].color = COLOR_LIGHT_BLUE;
        minorGrid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        minorGrid[gridPositionOffset + i * 2 + 1].color = COLOR_LIGHT_BLUE;
    }

    window.draw(minorGrid);

    sf::VertexArray majorGrid(sf::Lines, 4 * 2 * 2);

    for (unsigned i = 0; i < 4; i++) {
        float rowY = (CELL_SPACING * 3) * i;
        majorGrid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        majorGrid[i * 2].color = COLOR_BLACK;
        majorGrid[i * 2 + 1].position = { lineLength + startPosition.y, rowY + startPosition.y };
        majorGrid[i * 2 + 1].color = COLOR_BLACK;
    }

    gridPositionOffset = 4 * 2;
    for (unsigned i = 0; i < 4; i++) {
        float rowX = (CELL_SPACING * 3) * i;
        majorGrid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        majorGrid[gridPositionOffset + i * 2].color = COLOR_BLACK;
        majorGrid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        majorGrid[gridPositionOffset + i * 2 + 1].color = COLOR_BLACK;
    }

    window.draw(majorGrid);

    //DRAW GRID END
}
