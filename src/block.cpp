
#include "block.h"

void Block::draw(sf::RenderWindow& window) {

}

std::vector<std::vector<int>> getRandomStructure() {
	static std::vector<std::vector<int>> structures[] = {
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
}

Block getRandomBlock() {

}