
#include "table.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "colors.h"
#include "spacing.h"

bool Table::applyBlock(Block& theBlock)
{

    return false;
}

bool Table::previewBlock(Block& theHoldingBlock)
{

    return false;
}

void Table::draw(sf::RenderWindow& window)
{
    sf::Vector2f startPosition = { TABLE_START_POSITION_X, TABLE_START_POSITION_Y };
    float lineLength = CELL_SPACING * TABLE_SIZE;

    for (unsigned l = 0; l < 9; l++) {
        for (unsigned c = 0; c < 9; c++) {
            sf::RectangleShape cell;
            cell.setSize({ CELL_SPACING, CELL_SPACING });
            cell.setPosition({ startPosition.x + CELL_SPACING * l, startPosition.y + CELL_SPACING * c });
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
