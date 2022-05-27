
#include "cellMatrix.h"

completetion::completetion(mark theType, unsigned a, unsigned b) {
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

const std::array<std::array<cell, 9>, 9>& cellMatrix::getCells() {
    return cellTable;
}

void cellMatrix::clearPreviews() {
    for (unsigned i = 0; i < 9; i++) {
        for (unsigned j = 0; j < 9; j++) {
            if (cellTable[i][j] == cell::occupiedPreview)
                cellTable[i][j] = cell::occupied;
            else if (cellTable[i][j] == cell::preview)
                cellTable[i][j] = cell::empty;
        }
    }
}

void cellMatrix::reset() {
    for (unsigned i = 0; i < 9; i++) {
        for (unsigned j = 0; j < 9; j++)
            cellTable[i][j] = cell::empty;
    }
}

unsigned cellMatrix::getEmptyCellsAmount() const {
    unsigned amount = 0;

    for (unsigned i = 0; i < 9; i++) {
        for (unsigned j = 0; j < 9; j++) {
            if (cellTable[i][j] == cell::empty)
                amount++;
        }
    }

    return amount;
}

sf::Vector2i cellMatrix::previewBlock(Block& theHoldingBlock, const sf::Vector2i& matrixPosition)
{
    const auto& blockStructure = theHoldingBlock.getStructure();
    sf::Vector2i cellCoords = matrixPosition;

    sf::Vector2u blockStructureSize = theHoldingBlock.getStructureSize();

    if (cellCoords.x + blockStructureSize.x > 9 || cellCoords.y + blockStructureSize.y > 9)
        return { -1, -1 }; //check if the holding block is not out of bounds from the cell coords

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
    executeCompletetions(completetionMarks, cell::occupiedPreview);

    return cellCoords;
}

bool cellMatrix::canBlockBePlaced(Block& theBlock)
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

std::vector<sf::Vector2u> cellMatrix::getBlockPlacingPositions(Block& theBlock)
{
    std::vector<sf::Vector2u> positions;

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
                positions.push_back({ pX, pY });
        }
    }

    return positions;
}

std::unique_ptr<std::vector<completetion>> cellMatrix::checkCompletetion() {
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

        if (isVerticalLineFull)
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

void cellMatrix::executeCompletetions(std::unique_ptr<std::vector<completetion>>& completetions, cell withCell) {
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
            if (cellTable[coord.x][coord.y] == cell::occupied)
                cellTable[coord.x][coord.y] = cell::occupiedPreview;
        }
        else
            cellTable[coord.x][coord.y] = withCell;
    }
}

void cellMatrix::applyBlock(Block& theBlock, const sf::Vector2u& tableCellCoords, cell cellType) {
    auto structure = theBlock.getStructure();
    for (unsigned x = 0; x < theBlock.getStructureSize().x; x++) {
        for (unsigned y = 0; y < theBlock.getStructureSize().y; y++) {
            if (structure[x][y] == cell::occupied)
                cellTable[tableCellCoords.x + x][tableCellCoords.y + y] = cell::occupied;
        }
    }
}