#pragma once

#include <vector>

#include "impl.h"

class Block : Drawable
{
private:
	const std::vector<std::vector<int>>& structure;
	sf::Vector2f structureSize;

	sf::Vector2f position = { 10, 10 };
	float scale = 1;
	sf::Uint8 opacity = 255;

public:
	Block(std::vector<std::vector<int>>& structure) : structure(structure)
	{
		float h = structure.size(), w = 1;

		for (unsigned i = 0; i < structure.size(); i++) {
			if (structure[i].size() > w)
				w = structure[i].size();
		}

		structureSize = { h, w };
	}
	
	void setScale(float scale);
	void setPosition(const sf::Vector2f& position);

	void setOpacity(unsigned opacity);

	const std::vector<std::vector<int>>& getStructure();
	const sf::Vector2f getStructureSize();

	const float getScale();

	void draw(sf::RenderWindow& window);
};

Block getRandomBlock();