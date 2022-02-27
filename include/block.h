#pragma once

#include <vector>

#include "impl.h"

class Block : Drawable
{
private:
	const std::vector<std::vector<int>>& structure;
	sf::Vector2u structureSize;

	sf::Vector2f position = { 10, 10 };
	float scale = 1;
	sf::Uint8 opacity = 255;

public:
	Block(std::vector<std::vector<int>>& structure) : structure(structure)
	{
		unsigned h = structure.size(), w = 1;

		for (unsigned i = 0; i < structure.size(); i++) {
			if (structure[i].size() > w)
				w = structure[i].size();
		}

		structureSize = { h, w };
	}
	
	void setScale(const float& scale);
	void setPosition(const sf::Vector2f& position);

	void setOpacity(const unsigned& opacity);

	const std::vector<std::vector<int>>& getStructure();
	const sf::Vector2u getStructureSize();

	const float getScale();

	sf::FloatRect getLocalBounds();

	void draw(sf::RenderWindow& window);
};

Block getRandomBlock();