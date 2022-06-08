
#include "table.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "spacing.h"
#include "audio.h"
#include "settings.h"
#include "game.h"

Table::Table() {
    Table::updateColors();
    Table::calculateVertexes();
}

const cellMatrix& Table::getMatrix() {
    return theMatrix;
}

void Table::reset() {
    theMatrix.reset();
}

void Table::calculateVertexes() {
    sf::Vector2f startPosition = { TABLE_POSITION_X, TABLE_POSITION_Y };
    float lineLength = CELL_SPACING * TABLE_SIZE;

    for (unsigned i = 0; i < TABLE_SIZE - 1; i++) {
        float rowY = CELL_SPACING * (i + 1.f);
        minorGrid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        minorGrid[i * 2].color = MINOR_COLOR;
        minorGrid[i * 2 + 1].position = { lineLength + startPosition.y, rowY + startPosition.y };
        minorGrid[i * 2 + 1].color = MINOR_COLOR;
    }

    unsigned gridPositionOffset = (TABLE_SIZE - 1) * 2;
    for (unsigned i = 0; i < TABLE_SIZE - 1; i++) {
        float rowX = CELL_SPACING * (i + 1.f);
        minorGrid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        minorGrid[gridPositionOffset + i * 2].color = MINOR_COLOR;
        minorGrid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        minorGrid[gridPositionOffset + i * 2 + 1].color = MINOR_COLOR;
    }

    for (unsigned i = 0; i < 4; i++) {
        float rowY = (CELL_SPACING * 3.f) * i;
        majorGrid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        majorGrid[i * 2].color = MAJOR_COLOR;
        majorGrid[i * 2 + 1].position = { lineLength + startPosition.y, rowY + startPosition.y };
        majorGrid[i * 2 + 1].color = MAJOR_COLOR;
    }

    gridPositionOffset = 4 * 2;
    for (unsigned i = 0; i < 4; i++) {
        float rowX = (CELL_SPACING * 3.f) * i;
        majorGrid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        majorGrid[gridPositionOffset + i * 2].color = MAJOR_COLOR;
        majorGrid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        majorGrid[gridPositionOffset + i * 2 + 1].color = MAJOR_COLOR;
    }
}

sf::Vector2i Table::mousePositionToCellPosition(const sf::Vector2f& mousePosition) {
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

cell Table::getCellState(const sf::Vector2u& tableCellCoords) {
    return theMatrix.getCellState(tableCellCoords);
}

void Table::applyBlock(Block& theBlock, const sf::Vector2u& tableCellCoords, cell cellType) {
    //wont do any verifications for the tableCellCords or the block compatibility
    //because this function is SUPPOSED to be used ONLY with the RIGHT stuff.

    theMatrix.applyBlock(theBlock, tableCellCoords, cellType);

    Game::theScore->addPiecePlaced(theBlock.getStructureIndex());

    if (cellType != cell::occupied)
        Audio::play(Audio::effect::GoodPlacement);
    else {
        auto completedMarks = theMatrix.checkCompletetion();

        Game::theScore->processMarks(completedMarks);
        if (completedMarks->empty())
            Audio::play(Audio::effect::GoodPlacement);
        else
            Audio::play(Audio::effect::Completetion);

        theMatrix.executeCompletetions(completedMarks, cell::empty);
    }
}

sf::Vector2i Table::previewBlock(Block& theHoldingBlock, const sf::Vector2f& mousePosition) {
    auto cellCoords = mousePositionToCellPosition(mousePosition);
    auto previewApplyCoords = theMatrix.previewApplyCoords;

    if (previewApplyCoords.x != -1 && previewApplyCoords.y != -1 && previewApplyCoords != cellCoords)
        theMatrix.processPreviews();

    if (cellCoords.x == -1 || cellCoords.y == -1)
        return { -1, -1 }; //check mouse is in a cell

    return theMatrix.previewBlock(theHoldingBlock, cellCoords);
}

bool Table::canBlockBePlaced(Block& theBlock) {
    return theMatrix.canBlockBePlaced(theBlock);
}

void Table::draw(sf::RenderWindow& window) {
    sf::RectangleShape cellShape;
    cellShape.setSize({ CELL_SPACING - 2, CELL_SPACING - 2 });

    const std::array<std::array<cell, 9>, 9>& cellTable = theMatrix.getCells();

    for (unsigned l = 0; l < 9; l++) {
        for (unsigned c = 0; c < 9; c++) {
            cellShape.setPosition({ TABLE_POSITION_X + CELL_SPACING * l + 1.f, TABLE_POSITION_Y + CELL_SPACING * c + 1.f });

            switch (cellTable[l][c]) {
            case cell::empty:
                if ((l < 3 && c < 3) || (c > 5 && l < 3) || (l > 5 && c < 3) || (l > 5 && c > 5) || (l > 2 && l < 6 && c > 2 && c < 6))
                    cellShape.setFillColor(TABLE_ODD);
                else
                    cellShape.setFillColor(TABLE_EVEN);
                break;
            case cell::occupied:
                cellShape.setFillColor(CELL_SOLID);
                break;
            case cell::preview:
                cellShape.setFillColor(CELL_PREVIEW);
                break;
            case cell::occupiedPreview:
                cellShape.setFillColor(CELL_COMPLETION);
                break;
            }

            window.draw(cellShape);
        }
    } //DRAW CELLS END

    window.draw(minorGrid);
    window.draw(majorGrid); //DRAW GRID END
}

void Table::updateColors() {
    MINOR_COLOR = toColor(Settings::Aspect::tableMinor);
    MAJOR_COLOR = toColor(Settings::Aspect::tableMajor);

    Table::calculateVertexes();

    TABLE_ODD = toColor(Settings::Aspect::tableOdd);
    TABLE_EVEN = toColor(Settings::Aspect::tableEven);
    CELL_SOLID = toColor(Settings::Aspect::cellSolid);
    CELL_COMPLETION = toColor(Settings::Aspect::cellCompletion);
    CELL_PREVIEW = toColor(Settings::Aspect::cellPreview);
}
