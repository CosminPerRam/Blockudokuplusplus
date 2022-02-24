#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

class Block
{
private:
	std::vector<std::vector<int>> structure;

public:
	Block(std::vector<std::vector<int>>& structure) {
		this->structure = structure;
	}

	void draw(sf::RenderWindow& window);
};

static std::vector<std::vector<int>> getRandomStructure();
static Block getRandomBlock();