
#include "block.h"
#include "spacing.h"
#include "settings.h"
#include "utilities.h"

structure::structure(const std::vector<std::vector<bool>>& definition, const char* name)
	: definition(definition), name(name) {}

//defines the existing blocks structures
namespace structures
{
	structure dot = { { {1} }, "Dot" },
		square = { { {1, 1}, {1, 1} }, "Square" },
		plus = { { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} }, "Plus" },

		hLine_2 = { { {1}, {1} }, "Horizontal Line-2" },
		hLine_3 = { { {1}, {1}, {1} }, "Horizontal Line-3" },
		hLine_4 = { { {1}, {1}, {1}, {1} }, "Horizontal Line-4" },
		hLine_5 = { { {1}, {1}, {1}, {1}, {1} }, "Horizontal Line-5" },
		vLine_2 = { { {1, 1} }, "Vertical Line-2" },
		vLine_3 = { { {1, 1, 1} }, "Vertical Line-3" },
		vLine_4 = { { {1, 1, 1, 1} }, "Vertical Line-4" },
		vLine_5 = { { {1, 1, 1, 1, 1} }, "Vertical Line-5" },

		slash_2 = { { {0, 1}, {1, 0} }, "Slash-2" },
		slash_3 = { { {0, 0, 1}, {0, 1, 0}, {1, 0, 0} }, "Slash-3" },
		backslash_2 = { { {1, 0}, {0, 1} }, "BackSlash-2" },
		backslash_3 = { { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }, "BackSlash-3" },

		z = { { {0, 1}, {1, 1}, {1, 0} }, "Z" },
		z_reversed = { { {1, 0}, {1, 1}, {0, 1} }, "Z reversed" },
		z_up = { { {1, 1, 0}, {0, 1, 1} }, "Z up" },
		z_down = { { {0, 1, 1}, {1, 1, 0} }, "Z down" },

		hb_small = { { {1, 0}, {1, 1} }, "HB small" },
		hb_small_reversed = { { {1, 1}, {1, 0} }, "HB small reversed" },
		hb_small_flipped = { { {0, 1}, {1, 1} }, "HB small flipped" },
		hb_small_reversed_flipped = { { {1, 1}, {0, 1} }, "HB small reversed flipped" },
		hb_big = { { {1, 0, 0}, {1, 0, 0}, {1, 1, 1} }, "HB big" },
		hb_big_reversed = { { {1, 1, 1}, {1, 0, 0}, {1, 0, 0} }, "HB big reversed" },
		hb_big_flipped = { { {0, 0, 1}, {0, 0, 1}, {1, 1, 1} }, "HB big flipped" },
		hb_big_reversed_flipped = { { {1, 1, 1}, {0, 0, 1}, {0, 0, 1} }, "HB big reversed flipped" },

		l_horizontal = { { {1, 0}, {1, 0}, {1, 1} }, "L horizontal" },
		l_horizontal_reversed = { { {0, 1}, {0, 1}, {1, 1} }, "L horizontal reversed" },
		l_horizontal_flipped = { { {1, 1}, {1, 0}, {1, 0} }, "L horizontal flipped" },
		l_horizontal_reversed_flipped = { { {1, 0}, {1, 0}, {1, 1} }, "L horizontal reversed flipped" },
		l_vertical = { { {1, 1, 1}, {1, 0, 0} }, "L vertical" },
		l_vertical_reversed = { { {1, 1, 1}, {0, 0, 1} }, "L vertical reversed" },
		l_vertical_flipped = { { {1, 0, 0}, {1, 1, 1} }, "L vertical flipped" },
		l_vertical_reversed_flipped = { { {0, 0, 1}, {1, 1, 1} }, "L vertical reversed flipped" },

		t_small = { { {1, 0}, {1, 1}, {1, 0} }, "T small" },
		t_small_flipped = { { {0, 1}, {1, 1}, {0, 1} }, "T small flipped" },
		t_small_left = { { {0, 1, 0}, {1, 1, 1} }, "T small left" },
		t_small_right = { { {1, 1, 1}, {0, 1, 0} }, "T small right" },
		t_big = { { {1, 0, 0}, {1, 1, 1}, {1, 0, 0} }, "T big" },
		t_big_flipped = { { {0, 0, 1}, {1, 1, 1}, {0, 0, 1} }, "T big flipped" },
		t_big_left = { { {0, 1, 0}, {0, 1, 0}, {1, 1, 1} }, "T big left" },
		t_big_right = { { {1, 1, 1}, {0, 1, 0}, {0, 1, 0} }, "T big right" },

		c_down = { { {1, 1}, {1, 0}, {1, 1} }, "C down" },
		c_up = { { {1, 1}, {0, 1}, {1, 1} }, "C up" };

	const std::vector<structure*> grouped = {
		&dot, &square, &plus,
		&hLine_2,& hLine_3,& hLine_4,& hLine_5,& vLine_2,& vLine_3,& vLine_4,& vLine_5,
		&slash_2, &slash_3,& backslash_2,& backslash_3,
		&z, &z_reversed,& z_up,& z_down,
		&hb_small, &hb_small_reversed,& hb_small_flipped,& hb_small_reversed_flipped,
		&hb_big, &hb_big_reversed,& hb_big_flipped,& hb_big_reversed_flipped,
		&l_horizontal, &l_horizontal_reversed,& l_horizontal_flipped,& l_horizontal_reversed_flipped,
		&l_vertical, &l_vertical_reversed,& l_vertical_flipped,& l_vertical_reversed_flipped,
		&t_small, &t_small_flipped,& t_small_left,& t_small_right,
		&t_big, &t_big_flipped,& t_big_left,& t_big_right,
		&c_down, &c_up
	};
}

Block::Block(int structureIndex)
	: structure(this->getStructure(structureIndex))
{

}

const std::vector<std::vector<bool>> Block::getStructure(unsigned structureIndex) {
	if(structureIndex == -1)
		structureIndex = Random::getNumberInBetween(0, structures::grouped.size() - 1);
	else if (structureIndex == -2) {
		std::vector<std::vector<bool>> structure;

		for (unsigned i = 0; i < Settings::Gameplay::customBlockSizeWidth; i++) {
			std::vector<bool> row;
			for (unsigned j = 0; j < Settings::Gameplay::customBlockSizeHeight; j++)
				row.emplace_back(Settings::Gameplay::customBlockStructure[j][i]);
			
			structure.emplace_back(row);
		}
		
		this->structureIndex = -2;
		this->structureSize = { Settings::Gameplay::customBlockSizeWidth, Settings::Gameplay::customBlockSizeHeight };

		cell.setSize({ CELL_SPACING, CELL_SPACING });
		cell.setScale({ this->scale , this->scale });

		return structure;
	}

	this->structureIndex = structureIndex;
	const std::vector<std::vector<bool>>& structure = structures::grouped[structureIndex]->definition;
	unsigned h = structure.size(), w = 1;

	for (unsigned i = 0; i < structure.size(); i++) {
		if (structure[i].size() > w)
			w = structure[i].size();
	}

	this->structureSize = { h, w };

	cell.setSize({ CELL_SPACING, CELL_SPACING });
	cell.setScale({ this->scale , this->scale });

	return structure;
}

const std::vector<std::vector<bool>>& Block::getStructure() {
	return this->structure;
}

const unsigned Block::getStructureIndex() {
	return this->structureIndex;
}

const sf::Vector2u Block::getStructureSize() {
	return this->structureSize;
}

const float Block::getScale() {
	return this->scale;
}

sf::FloatRect Block::getGlobalBounds() {
	return { position.x, position.y, structureSize.x * CELL_SPACING * scale, structureSize.y * CELL_SPACING * scale };
}

void Block::setScale(const float& scale) {
	this->scale = scale;

	cell.setScale({ this->scale , this->scale });
}

void Block::setPosition(const sf::Vector2f& position) {
	this->position = position;
}

void Block::setOpacity(const unsigned& opacity) {
	this->opacity = opacity;

	cell.setFillColor({ cell.getFillColor().r, cell.getFillColor().g, cell.getFillColor().b, this->opacity });
}

void Block::setFloating(bool isFloating) {
	this->floating = isFloating;
}

void Block::draw(sf::RenderWindow& window) {
	sf::VertexArray borders(sf::Lines, 4 * 2);
	sf::Vector2f cellPosition;

	for (unsigned l = 0; l < structure.size(); l++) {
		for (unsigned c = 0; c < structure[l].size(); c++) {
			if (structure[l][c] == 1) {
				if(floating)
					cellPosition = { position.x + (4 + CELL_SPACING) * l * scale, position.y + (4 + CELL_SPACING) * c * scale };
				else
					cellPosition = { position.x + CELL_SPACING * l * scale, position.y + CELL_SPACING * c * scale };

				cell.setFillColor(toColor(Settings::Aspect::cellSolid));
				cell.setFillColor({ cell.getFillColor().r, cell.getFillColor().g, cell.getFillColor().b, opacity });
				cell.setPosition(cellPosition);

				window.draw(cell);

				auto blockMarginsColor = toColor(Settings::Aspect::cellMargins);

				//always recalculates the margins because a block can be moved graphically
				for (unsigned i = 0; i < 2; i++) {
					float rowY = CELL_SPACING * i * 1.f;
					borders[i * 2].position = { cellPosition.x, cellPosition.y + rowY * scale };
					borders[i * 2].color = blockMarginsColor;
					borders[i * 2 + 1].position = { cellPosition.x + CELL_SPACING * scale, cellPosition.y + rowY * scale };
					borders[i * 2 + 1].color = blockMarginsColor;
				}
				
				unsigned borderPositionOffset = 4;
				for (unsigned i = 0; i < 2; i++) {
					float rowX = CELL_SPACING * i * 1.f;
					borders[borderPositionOffset + i * 2].position = { cellPosition.x + rowX * scale, cellPosition.y };
					borders[borderPositionOffset + i * 2].color = blockMarginsColor;
					borders[borderPositionOffset + i * 2 + 1].position = { cellPosition.x + rowX * scale, cellPosition.y + CELL_SPACING * scale };
					borders[borderPositionOffset + i * 2 + 1].color = blockMarginsColor;
				}

				window.draw(borders);
			}
		}
	}
}
