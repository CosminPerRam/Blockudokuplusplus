#pragma once

#include "impl.h"

#include <vector>

class Block : Drawable
{
private:
	static std::vector<std::vector<std::vector<int>>>& allStructures();
	static int d;
	const std::vector<std::vector<int>>& structure;
	unsigned structureIndex;
	sf::Vector2u structureSize;

	sf::Vector2f position = { 10, 10 };
	float scale = 1;
	sf::Uint8 opacity = 255;

	const std::vector<std::vector<int>>& generateStructure(unsigned structureIndex);

public:
	Block();

	Block(unsigned structureIndex);
	
	void setScale(const float& scale);
	void setPosition(const sf::Vector2f& position);

	void setOpacity(const unsigned& opacity);

	const std::vector<std::vector<int>>& getStructure();
	const unsigned getStructureIndex();
	const sf::Vector2u getStructureSize();

	static unsigned getAllStructuresCount();

	const float getScale();

	sf::FloatRect getLocalBounds();

	void draw(sf::RenderWindow& window);
};
