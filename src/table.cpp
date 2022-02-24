
#include "table.h"

#include "colors.h"

void Table::draw(sf::RenderWindow& window)
{
    sf::Vector2f startPosition = { 25, 25 };
    float spacing = 32;
    float lineLength = spacing * TABLE_SIZE;

    for (unsigned l = 0; l < 9; l++) {
        for (unsigned c = 0; c < 9; c++) {
            sf::RectangleShape cell;
            cell.setSize({ spacing, spacing });
            cell.setPosition({ startPosition.x + spacing * l, startPosition.y + spacing * c });
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

    sf::VertexArray grid(sf::Lines, 4 * (TABLE_SIZE + 1)); //without borders, it would be: 2 * (TABLE_SIZE * 2 - 2)

	for (unsigned i = 0; i < TABLE_SIZE + 1; i++) {
        float rowY = spacing * i;
        grid[i * 2].position = { startPosition.y, rowY + startPosition.y };
        grid[i * 2].color = { 0, 0, 0 };
        grid[i * 2 + 1].position = {lineLength + startPosition.y, rowY + startPosition.y };
        grid[i * 2 + 1].color = { 0, 0, 0 };
    }

    unsigned gridPositionOffset = (TABLE_SIZE + 1) * 2;
	for (unsigned i = 0; i < TABLE_SIZE + 1; i++) {
        float rowX = spacing * i;
        grid[gridPositionOffset + i * 2].position = { rowX + startPosition.x, startPosition.x };
        grid[gridPositionOffset + i * 2].color = { 0, 0, 0 };
        grid[gridPositionOffset + i * 2 + 1].position = { rowX + startPosition.x, lineLength + startPosition.x };
        grid[gridPositionOffset + i * 2 + 1].color = { 0, 0, 0 };
	}

    window.draw(grid);

    //DRAW GRID END
}
