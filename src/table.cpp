
#include "table.h"
#include "colors.h"
#include "spacing.h"
#include "audio.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>

Table::completetion::completetion(mark theType, unsigned a, unsigned b) {
    type = theType;

    switch (theType) {
    case mark::square:
        x = a;
        y = b;
        break;
    case mark::hline:
        x = a;
        break;
    case mark::vline:
        y = a;
        break;
    }
}

Table::Table(Score& theScore) : theScore(theScore)
{
    sf::Vector2f startPosition = { TABLE_POSITION_X, TABLE_POSITION_Y };
    float lineLength = CELL_SPACING * TABLE_SIZE;

    for (unsigned i = 0; i < TABLE_SIZE - 1; i++) {
        float rowY = CELL_SPACING * (i + 1.f);
        minorGrid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        minorGrid[i * 2].color = COLOR_LIGHT_BLUE;
        minorGrid[i * 2 + 1].position = { lineLength + startPosition.y, rowY + startPosition.y };
        minorGrid[i * 2 + 1].color = COLOR_LIGHT_BLUE;
    }

    unsigned gridPositionOffset = (TABLE_SIZE - 1) * 2;
    for (unsigned i = 0; i < TABLE_SIZE - 1; i++) {
        float rowX = CELL_SPACING * (i + 1.f);
        minorGrid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        minorGrid[gridPositionOffset + i * 2].color = COLOR_LIGHT_BLUE;
        minorGrid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        minorGrid[gridPositionOffset + i * 2 + 1].color = COLOR_LIGHT_BLUE;
    }

    for (unsigned i = 0; i < 4; i++) {
        float rowY = (CELL_SPACING * 3.f) * i;
        majorGrid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        majorGrid[i * 2].color = COLOR_BLACK;
        majorGrid[i * 2 + 1].position = { lineLength + startPosition.y, rowY + startPosition.y };
        majorGrid[i * 2 + 1].color = COLOR_BLACK;
    }

    gridPositionOffset = 4 * 2;
    for (unsigned i = 0; i < 4; i++) {
        float rowX = (CELL_SPACING * 3.f) * i;
        majorGrid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        majorGrid[gridPositionOffset + i * 2].color = COLOR_BLACK;
        majorGrid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        majorGrid[gridPositionOffset + i * 2 + 1].color = COLOR_BLACK;
    }
}

sf::Vector2i Table::mousePositionToCellPosition(const sf::Vector2f& mousePosition)
{
    sf::Vector2f startPosition = { TABLE_POSITION_X, TABLE_POSITION_Y };

    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            sf::FloatRect cell = {startPosition.x + CELL_SPACING * l, startPosition.y + CELL_SPACING * c, CELL_SPACING, CELL_SPACING };

            if (cell.contains(mousePosition))
                return { l, c };
        }
    }

    return { -1, -1 };
}

std::unique_ptr<std::vector<Table::completetion>> Table::checkCompletetion() {
    auto completions = std::make_unique<std::vector<completetion>>();

    //blocks
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            bool isBlockFull = true;
            for (unsigned m = 0; m < 3; m++) {
                for (unsigned n = 0; n < 3; n++) {
                    if (cellTable[i * 3 + m][j * 3 + n] == cell::empty)
                        isBlockFull = false;
                }
            }

            if (isBlockFull)
                completions->emplace_back(mark::square, i * 3, j * 3);
        }
    }
    
    //vertical lines
    for (unsigned i = 0; i < 9; i++) {
        bool isVerticalLineFull = true;
        for (unsigned m = 0; m < 9; m++) {
            if (cellTable[m][i] == cell::empty)
            {
                isVerticalLineFull = false;
                break;
            }
        }

        if(isVerticalLineFull)
            completions->emplace_back(mark::vline, i);
    }

    //horizontal lines
    for (unsigned j = 0; j < 9; j++) {
        bool isHorizontalLineFull = true;
        for (unsigned m = 0; m < 9; m++) {
            if (cellTable[j][m] == cell::empty)
            {
                isHorizontalLineFull = false;
                break;
            }
        }

        if (isHorizontalLineFull)
            completions->emplace_back(mark::hline, j);
    }

    return completions;
}

void Table::executeCompletetionsWith(std::unique_ptr<std::vector<completetion>>& completetions, cell withCell) {
    std::vector<sf::Vector2u> coords;
    coords.reserve(completetions->size() * 9);

    for (const auto& mark : *completetions) {
        switch (mark.type) {
        case mark::square:
            for (unsigned i = 0; i < 3; i++) {
                for (unsigned j = 0; j < 3; j++)
                    coords.emplace_back(mark.x + i, mark.y + j);
            }
            break;
        case mark::vline:
            for (unsigned m = 0; m < 9; m++)
                coords.emplace_back(m, mark.y);
            break;
        case mark::hline:
            for (unsigned m = 0; m < 9; m++) 
                coords.emplace_back(mark.x, m);
            break;
        }
    }

    for (unsigned i = 0; i < coords.size(); i++) {
        auto& coord = coords[i];

        if (withCell == cell::occupiedPreview) {
            if(cellTable[coord.x][coord.y] == cell::occupied)
                cellTable[coord.x][coord.y] = cell::occupiedPreview;
        }
        else
            cellTable[coord.x][coord.y] = withCell;
    }
}

void Table::applyBlock(Block& theBlock, const sf::Vector2i& tableCellCoords) {
    //wont do any verifications for the tableCellCords or the block compatibility
    //because this function is SUPPOSED to be used ONLY with the RIGHT stuff.

    auto structure = theBlock.getStructure();
    for (unsigned x = 0; x < theBlock.getStructureSize().x; x++) {
        for (unsigned y = 0; y < theBlock.getStructureSize().y; y++) {
            if (structure[x][y] == cell::occupied)
                cellTable[tableCellCoords.x + x][tableCellCoords.y + y] = cell::occupied;
        }
    }

    auto completedMarks = checkCompletetion();
    if (completedMarks->empty())
    {
        Audio::play(Audio::effect::GoodPlacement);
        theScore.resetCombo();
    }
    else {
        Audio::play(Audio::effect::Completetion);

        theScore.addToCombo(completedMarks->size());
        if(completedMarks->size() > 1) //give one point for getting more marks at one time
            theScore.addToCombo(1);

        for (const auto& mark : *completedMarks) {
            if(mark.type == mark::square)
                theScore.addCompletionSquare();
            else
                theScore.addCompletionLine();
        }

        executeCompletetionsWith(completedMarks, cell::empty);
    }
}

void Table::clearPreviews() {
    for (unsigned i = 0; i < 9; i++) {
        for (unsigned j = 0; j < 9; j++) {
            if (cellTable[i][j] == cell::occupiedPreview)
                cellTable[i][j] = cell::occupied;
            else if (cellTable[i][j] == cell::preview)
                cellTable[i][j] = cell::empty;
        }
    }
}

sf::Vector2i Table::previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition)
{
    auto cellCoords = mousePositionToCellPosition(mousePosition);

    if (previewApplyCoords.x != -1 && previewApplyCoords.y != -1 && previewApplyCoords != cellCoords)
        clearPreviews();

    if (cellCoords.x == -1 || cellCoords.y == -1)
        return { -1, -1 }; //first check mouse is in a cell

    sf::Vector2u blockStructureSize = theHoldingBlock.getStructureSize();

    if (cellCoords.x + blockStructureSize.x > 9 || cellCoords.y + blockStructureSize.y > 9)
        return { -1, -1 }; //secondly, check if the holding block is not out of bounds from the cell coords

    const auto& blockStructure = theHoldingBlock.getStructure();

    for (unsigned x = 0; x < blockStructureSize.x; x++) {
        for (unsigned y = 0; y < blockStructureSize.y; y++) {
            if (cellTable[cellCoords.x + x][cellCoords.y + y] == cell::occupied && blockStructure[x][y] == cell::occupied)
                return { -1, -1 };
        }
    }

    previewApplyCoords = cellCoords;

    for (unsigned x = 0; x < blockStructureSize.x; x++) {
        for (unsigned y = 0; y < blockStructureSize.y; y++) {
            if (blockStructure[x][y] == cell::occupied && cellTable[cellCoords.x + x][cellCoords.y + y] != cell::occupied)
                cellTable[cellCoords.x + x][cellCoords.y + y] = cell::preview;
        }
    }

    auto completetionMarks = checkCompletetion();
    executeCompletetionsWith(completetionMarks, cell::occupiedPreview);

    return cellCoords;
}

bool Table::canBlockBePlaced(Block& theBlock)
{
    auto blockStructure = theBlock.getStructure();
    auto blockStructureSize = theBlock.getStructureSize();

    for (unsigned pX = 0; pX < (9 - blockStructureSize.x) + 1; pX++) {
        for (unsigned pY = 0; pY < (9 - blockStructureSize.y) + 1; pY++) {
            bool canBePlaced = true;

            for (unsigned bX = 0; bX < blockStructureSize.x; bX++) {
                for (unsigned bY = 0; bY < blockStructureSize.y; bY++) {
                    if (cellTable[pX + bX][pY + bY] == cell::occupied && blockStructure[bX][bY] == cell::occupied)
                        canBePlaced = false;
                }
            }

            if (canBePlaced)
                return true;
        }
    }

    return false;
}

void Table::draw(sf::RenderWindow& window)
{
    sf::RectangleShape cell;
    cell.setSize({ CELL_SPACING - 2, CELL_SPACING - 2 });

    for (unsigned l = 0; l < 9; l++) {
        for (unsigned c = 0; c < 9; c++) {
            cell.setPosition({ TABLE_POSITION_X + CELL_SPACING * l + 1.f, TABLE_POSITION_Y + CELL_SPACING * c + 1.f });

            switch (cellTable[l][c]) {
            case cell::empty:
                if ((l < 3 && c < 3) || (c > 5 && l < 3) || (l > 5 && c < 3) || (l > 5 && c > 5) || (l > 2 && l < 6 && c > 2 && c < 6))
                    cell.setFillColor(COLOR_GRAY);
                else
                    cell.setFillColor(COLOR_WHITE);
                break;
            case cell::occupied:
                cell.setFillColor(COLOR_BLUE);
                break;
            case cell::preview:
                cell.setFillColor(COLOR_LIGHT_BLUE);
                break;
            case cell::occupiedPreview:
                cell.setFillColor(COLOR_DARKER_BLUE);
                break;
            }

            window.draw(cell);
        }
    } //DRAW CELLS END

    window.draw(minorGrid);
    window.draw(majorGrid); //DRAW GRID END
}
