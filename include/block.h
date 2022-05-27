
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

struct structure
{
	structure(const std::vector<std::vector<int>>& definition, const char* name);

	const std::vector<std::vector<int>> definition;
	const char* name;
};

namespace structures
{
	extern structure dot, square, plus,
		hLine_2, hLine_3, hLine_4, hLine_5, vLine_2, vLine_3, vLine_4, vLine_5,
		slash_2, slash_3, backslash_2, backslash_3,
		z, z_reversed, z_up, z_down,
		hb_small, hb_small_reversed, hb_small_flipped, hb_small_reversed_flipped, //hb means half block
		hb_big, hb_big_reversed, hb_big_flipped, hb_big_reversed_flipped,
		l_horizontal, l_horizontal_reversed, l_horizontal_flipped, l_horizontal_reversed_flipped,
		l_vertical, l_vertical_reversed, l_vertical_flipped, l_vertical_reversed_flipped,
		t_small, t_small_flipped, t_small_left, t_small_right,
		t_big, t_big_flipped, t_big_left, t_big_right,
		c_down, c_up;

	extern const std::vector<structure*> grouped;
}

/*
	A block is a certain formation of cells.
*/
class Block
{
private:
	sf::RectangleShape cell;

	sf::Vector2f position = { 10, 10 };
	float scale = 1;
	sf::Uint8 opacity = 255;
	bool floating = false;

	unsigned structureIndex;
	sf::Vector2u structureSize;
	const std::vector<std::vector<int>>& structure;

	const std::vector<std::vector<int>>& getStructure(unsigned structureIndex);

public:
	Block(int structureIndex);
	
	void setScale(const float& scale);
	void setPosition(const sf::Vector2f& position);
	void setOpacity(const unsigned& opacity);
	void setFloating(bool isFloating);

	const float getScale();

	const std::vector<std::vector<int>>& getStructure();
	const sf::Vector2u getStructureSize();
	const unsigned getStructureIndex();

	sf::FloatRect getGlobalBounds();

	void draw(sf::RenderWindow& window);
};
