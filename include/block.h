#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

class Block
{
private:
	std::vector<std::vector<int>> structure;

	sf::Vector2f position = { 10, 10 };

public:
	Block(std::vector<std::vector<int>>& structure) {
		this->structure = structure;
	}

	void draw(sf::RenderWindow& window);
};

Block getRandomBlock();