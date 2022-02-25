
#include "block.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "spacing.h"
#include "colors.h"
#include "utilities.h"

#include <iostream>

const sf::Vector2f Block::getStructureSize() {
	return this->structureSize;
}

const std::vector<std::vector<int>>& Block::getStructure() {
	return this->structure;
}

void Block::setScale(float scale) {
	this->scale = scale;
}

void Block::setPosition(const sf::Vector2f& position) {
	this->position = position;
}

void Block::draw(sf::RenderWindow& window) {
	sf::RectangleShape cell;
	cell.setSize({ CELL_SPACING, CELL_SPACING });
	cell.setScale({ this->scale , this->scale });
	cell.setFillColor(COLOR_BLUE);

	sf::VertexArray borders(sf::Lines, 4 * 2);

	for (float l = 0; l < structure.size(); l++) {
		for (float c = 0; c < structure[l].size(); c++) {
			if (structure[l][c] == 1) {
				sf::Vector2f cellPosition = { position.x + CELL_SPACING * l * scale, position.y + CELL_SPACING * c * scale };
				cell.setPosition(cellPosition);

				window.draw(cell);

				for (unsigned i = 0; i < 2; i++) {
					float rowY = CELL_SPACING * i;
					borders[i * 2].position = { cellPosition.x, cellPosition.y + rowY * scale };
					borders[i * 2].color = COLOR_BLACK;
					borders[i * 2 + 1].position = { cellPosition.x + CELL_SPACING * scale, cellPosition.y + rowY * scale };
					borders[i * 2 + 1].color = COLOR_BLACK;
				}
				
				unsigned borderPositionOffset = 4;
				for (unsigned i = 0; i < 2; i++) {
					float rowX = CELL_SPACING * i;
					borders[borderPositionOffset + i * 2].position = { cellPosition.x + rowX * scale, cellPosition.y };
					borders[borderPositionOffset + i * 2].color = COLOR_BLACK;
					borders[borderPositionOffset + i * 2 + 1].position = { cellPosition.x + rowX * scale, cellPosition.y + CELL_SPACING * scale };
					borders[borderPositionOffset + i * 2 + 1].color = COLOR_BLACK;
				}

				window.draw(borders);
			}
		}
	}
}

Block getRandomBlock() {
	static std::vector < std::vector<std::vector<int>>> structures = {
		{{1}}, //dot
		{{1, 1}}, //hline-2
		{{1, 1, 1}}, //hline-3
		{{1, 1, 1, 1}}, //hline-4
		{{1, 1, 1, 1, 1}}, //hline-5
		{{1}, {1}}, //vline-2
		{{1}, {1}, {1}}, //vline-3
		{{1}, {1}, {1}, {1}}, //vline-4
		{{1}, {1}, {1}, {1}, {1}}, //vline-5
		{{0, 1}, {1, 0}}, //2-slash
		{{1, 0}, {0, 1}}, //2-backslash
		{{1, 0}, {1, 1}}, //small |_
		{{0, 1}, {1, 1}}, //small _|
		{{1, 1}, {1, 0}}, //small L clockwise 1
		{{1, 1}, {0, 1}}, //small L clockwise 2
		{{1, 1}, {1, 1}}, //square
		{{0, 0, 1}, {0, 1, 0}, {1, 0, 0}}, //3-slash
		{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},  //3-backslash
		{{1, 0, 0}, {1, 0, 0}, {1, 1, 1}}, //|_ half block
		{{0, 0, 1}, {0, 0, 1}, {1, 1, 1}}, //_| half block
		{{1, 1, 1}, {1, 0, 0}, {1, 0, 0}}, //half block clockwise 1
		{{1, 1, 1}, {0, 0, 1}, {0, 0, 1}}, //half block clockwise 2
		{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, //+
		{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, //|--
		{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, //--|
		{{1, 1, 1}, {0, 1, 0}, {0, 1, 0}}, //|-- up
		{{0, 1, 0}, {0, 1, 0}, {1, 1, 1}}, //--| down
		{{1, 1}, {1, 0}, {1, 1}}, //C
		{{1, 1}, {0, 1}, {1, 1}}, //C reverse
		{{1, 1, 1}, {1, 0, 0}}, //horizontal L
		{{1, 1, 1}, {0, 0, 1}}, //horizontal L reversed
		{{1, 0, 0}, {1, 1, 1}}, //horizontal L flipped
		{{0, 0, 1}, {1, 1, 1}}, //horizontal L reversed flipped
		{{1, 0}, {1, 0}, {1, 1}}, //vertical L
		{{0, 1}, {0, 1}, {1, 1}}, //vertical L reversed
		{{1, 1}, {1, 0}, {1, 0}}, //vertical L flipped
		{{1, 0}, {1, 0}, {1, 1}}, //vertical L reversed flipped
		{{1, 0}, {1, 1}, {1, 0}}, //|-
		{{0, 1}, {1, 1}, {0, 1}}, //-|
		{{0, 1, 0}, {1, 1, 1}}, //-| up
		{{1, 1, 1}, {0, 1, 0}}, //|- down
		{{1, 1, 0}, {0, 1, 1}}, //z
		{{0, 1, 1}, {1, 1, 0}}, //z reverse
		{{0, 1}, {1, 1}, {1, 0}}, //up z
		{{1, 0}, {1, 1}, {0, 1}}  //up z reverse
	};

	return Block(structures[random::getNumberInBetween(0, structures.size())]);
}