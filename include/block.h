#pragma once

#include "impl.h"

#include <vector>

class Block : Drawable
{
private:
	static const std::vector<std::vector<std::vector<int>>> allStructures;

	unsigned structureIndex;
	sf::Vector2u structureSize;
	const std::vector<std::vector<int>>& structure;

	sf::Vector2f position = { 10, 10 };
	float scale = 1;
	sf::Uint8 opacity = 255;

	const std::vector<std::vector<int>>& getStructure(unsigned structureIndex);

public:
	Block();

	Block(unsigned structureIndex);
	
	void setScale(const float& scale);
	void setPosition(const sf::Vector2f& position);

	void setOpacity(const unsigned& opacity);

	const float getScale();

	const std::vector<std::vector<int>>& getStructure();
	const unsigned getStructureIndex();
	const sf::Vector2u getStructureSize();

	sf::FloatRect getLocalBounds();

	static unsigned getAllStructuresCount();

	void draw(sf::RenderWindow& window);
};
